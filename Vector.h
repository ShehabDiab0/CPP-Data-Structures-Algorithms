#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H
#include <iostream>
#include <memory>
#include <string_view>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

template<typename ElemType>
class Vector
{
public:
	using iterator = ElemType*;

private:
	int dataCapacity = 0;
	int dataSize = 0;
	ElemType* data = nullptr;
	std::allocator<ElemType> memoryManager;

private:
	using trait = std::allocator_traits<decltype(memoryManager)>;

private:
	void reAllocate(int newCapacity);
	int doubleCapacity();
	void moveFromOther(ElemType* dest, ElemType* src, int size);
	void copyFromOther(ElemType* dest, ElemType* src, int size);
	void defaultConstruct(iterator start, iterator end); // when size grows
	void destruct(iterator start, iterator end); // when size shrinks
	void shiftLeft(iterator dest, iterator src);

public:
	Vector();
	Vector(int cap);

	Vector(ElemType* arr, int n);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	Vector(Vector&& other);
	Vector& operator=(Vector&& other);

	~Vector();

	ElemType& operator[](int index);
	bool operator==(const Vector& other) const;
	bool operator<(const Vector& other) const;
	bool operator>(const Vector& other) const;

	int pushBack(ElemType&& element);
	int pushBack(const ElemType& element);
	ElemType popBack();
	void erase(iterator place);
	void erase(iterator start, iterator end);
	void insert(iterator place, ElemType element);

	iterator begin() const;
	iterator end() const;

	int size() const noexcept;
	int capacity() const noexcept;
	bool isEmpty() const noexcept;

	int resize(int newSize); // returns 1 if size increases, 0 if nothing happens, -1 if size decreases
	void reserve(int newCapacity);
	void clear() noexcept;

	template<typename VecType>
	friend std::ostream& operator<<(std::ostream& out, const Vector<VecType>& vec);
};


template<typename ElemType>
void Vector<ElemType>::reAllocate(int newCapacity)
{
	ElemType* newData = trait::allocate(memoryManager, newCapacity);

	if (newCapacity < dataSize)
		dataSize = newCapacity;

	for (int i = 0; i < dataSize; i++)
		trait::construct(memoryManager, &newData[i], std::move(data[i]));


	for (int i = 0; i < dataSize; i++)
		trait::destroy(memoryManager, &data[i]);
	trait::deallocate(memoryManager, data, dataCapacity);

	data = newData;
	dataCapacity = newCapacity;
}

template<typename ElemType>
void Vector<ElemType>::moveFromOther(ElemType* dest, ElemType* src, int size)
{
	dataSize = size;
	for (int i = 0; i < dataSize; i++)
		trait::construct(memoryManager, &dest[i], std::move(src[i]));
}

template<typename ElemType>
void Vector<ElemType>::copyFromOther(ElemType* dest, ElemType* src, int size)
{
	dataSize = size;
	for (int i = 0; i < dataSize; i++)
		trait::construct(memoryManager, &dest[i], src[i]);
}


template<typename ElemType>
void Vector<ElemType>::defaultConstruct(iterator start, iterator end) // when size grows
{
	int prevSize = dataSize;

	for (iterator i = start; i < end; i++)
	{
		trait::construct(memoryManager, i);
	}

	dataSize = prevSize + static_cast<int>(end - start);
}


template<typename ElemType>
void Vector<ElemType>::destruct(iterator start, iterator end) // when size shrinks
{
	int prevSize = dataSize;

	for (iterator i = start; i < end; i++)
	{
		trait::destroy(memoryManager, i);
	}

	dataSize = prevSize - static_cast<int>(end - start);
}


template<typename ElemType>
void Vector<ElemType>::shiftLeft(iterator dest, iterator src)
{
	int nShifts = static_cast<int>(end() - src);
	for (int i = 0; i < nShifts; i++)
	{
		dest[i] = std::move(src[i]);
	}
	int nRemovals = static_cast<int>(src - dest);

	destruct(begin() + dataSize - nRemovals, end());

}

template<typename ElemType>
int Vector<ElemType>::doubleCapacity()
{
	return dataCapacity * 2;
}

template<typename ElemType>
Vector<ElemType>::Vector()
{
	reAllocate(2);
}

template<typename ElemType>
Vector<ElemType>::Vector(int cap)
{
	reAllocate(cap);
	dataSize = 0;
}


template<typename ElemType>
Vector<ElemType>::Vector(ElemType* arr, int n)
{
	reAllocate(n + 1); // capacity = size of arr + 1
	copyFromOther(data, arr, n);
}

template<typename ElemType>
Vector<ElemType>::Vector(const Vector<ElemType>& other)
{
	reAllocate(other.dataCapacity);
	moveFromOther(data, other.data, other.dataSize);
}

template<typename ElemType>
Vector<ElemType>& Vector<ElemType>::operator=(const Vector<ElemType>& other)
{
	destruct(begin(), end());
	trait::deallocate(memoryManager, begin(), dataCapacity);

	Vector<ElemType> copy(other);
	*this = std::move(copy);

	return *this;
}

template<typename ElemType>
Vector<ElemType>::Vector(Vector<ElemType>&& other)
{
	dataCapacity = other.dataCapacity;
	dataSize = other.dataSize;
	data = other.data;

	other.data = nullptr;
	other.dataSize = 0;
	other.dataCapacity = 0;
}

template<typename ElemType>
Vector<ElemType>& Vector<ElemType>::operator=(Vector<ElemType>&& other)
{
	if (this == &other)
		return *this;

	dataCapacity = other.dataCapacity;
	dataSize = other.dataSize;
	data = other.data;

	other.data = nullptr;
	other.dataSize = 0;
	other.dataCapacity = 0;

	return *this;

}

template<typename ElemType>
Vector<ElemType>::~Vector()
{
	clear();
	trait::deallocate(memoryManager, data, dataCapacity);
}

template<typename ElemType>
ElemType& Vector<ElemType>::operator[](int index)
{
	if (index >= dataSize || index < 0)
		throw std::out_of_range("OUT OF VECTOR RANGE, MEMORY ACCESSED IS NOT OURS");

	return data[index];
}

template<typename ElemType>
bool Vector<ElemType>::operator==(const Vector& other) const
{
	if (dataSize != other.dataSize)
		return false;

	for (int i = 0; i < dataSize; i++)
	{
		if (data[i] != other.data[i])
			return false;
	}

	return true;
}

template<typename ElemType>
bool Vector<ElemType>::operator<(const Vector& other) const
{
	return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
}

template<typename ElemType>
bool Vector<ElemType>::operator>(const Vector& other) const
{
	return (other < *this);
}

template<typename ElemType>
int Vector<ElemType>::pushBack(const ElemType& element)
{
	if (dataSize >= dataCapacity)
		reAllocate(doubleCapacity());

	trait::construct(&data[dataSize], element);
	dataSize++;

	return dataSize;
}

template<typename ElemType>
int Vector<ElemType>::pushBack(ElemType&& element)
{
	if (dataSize >= dataCapacity)
	{
		reAllocate(doubleCapacity());
	}

	trait::construct(memoryManager, &data[dataSize], std::move(element));
	dataSize++;

	return dataSize;
}

template<typename ElemType>
ElemType Vector<ElemType>::popBack()
{
	if (isEmpty())
		throw std::out_of_range("VECTOR IS ALREADY EMPTY");

	dataSize--;
	ElemType deletedElement = std::move(data[dataSize]);
	trait::destroy(memoryManager, &data[dataSize]);

	return deletedElement;
}

template<typename ElemType>
void Vector<ElemType>::erase(iterator place)
{
	if (place - 1 >= end())
		throw std::out_of_range("OUT OF VECTOR RANGE");

	shiftLeft(place, place + 1);
}

template<typename ElemType>
void Vector<ElemType>::erase(iterator start, iterator end)
{
	if (start >= end)
		return;
	
	// end - 1 >= end()
	if (end - 1 >= data + dataSize)
		throw std::out_of_range("OUT OF VECTOR RANGE, PASSED THE VECTOR END");
	if (start < begin())
		throw std::out_of_range("OUT OF VECTOR RANGE, BEFORE THE START OF THE VECTOR");

	shiftLeft(start, end);
}

template<typename ElemType>
void Vector<ElemType>::insert(iterator place, ElemType element)
{
	int iteratorIndex = static_cast<int>(place - begin());

	if (iteratorIndex > dataSize)
		throw std::out_of_range("OUT OF RANGE");

	if (iteratorIndex == dataSize)
	{
		pushBack(std::move(element));
		return;
	}


	if (dataSize >= dataCapacity)
	{
		ElemType* newData = trait::allocate(memoryManager, doubleCapacity());


		for (int i = 0; i < iteratorIndex; i++)
			trait::construct(memoryManager, &newData[i], std::move(data[i]));
		
		trait::construct(memoryManager, newData + iteratorIndex, std::move(element));
		
		for (int i = iteratorIndex + 1; i < dataSize + 1; i++)
			trait::construct(memoryManager, &newData[i], std::move(data[i - 1]));


		int prevSize = dataSize;
		destruct(begin(), end());
		trait::deallocate(memoryManager, data, dataCapacity);

		data = newData;
		dataSize = prevSize + 1;
		dataCapacity = doubleCapacity();

		return;
	}

	trait::construct(memoryManager, &data[dataSize]);
	dataSize++;

	for (int i = dataSize - 1; i > iteratorIndex; i--)
		data[i] = std::move(data[i - 1]);

	trait::construct(memoryManager, data + iteratorIndex, std::move(element));

}

template<typename ElemType>
Vector<ElemType>::iterator Vector<ElemType>::begin() const
{
	return data;
}

template<typename ElemType>
Vector<ElemType>::iterator Vector<ElemType>::end() const
{
	return data + dataSize;
}

template<typename ElemType>
int Vector<ElemType>::size() const noexcept
{
	return dataSize;
}

template<typename ElemType>
int Vector<ElemType>::capacity() const noexcept
{
	return dataCapacity;
}



template<typename ElemType>
int Vector<ElemType>::resize(int newSize)
{

	if (newSize >= dataCapacity)
	{
		reAllocate(newSize * 2);
		defaultConstruct(begin() + dataSize, begin() + newSize);
		return 1;
	}

	if (newSize > dataSize)
	{
		defaultConstruct(begin() + dataSize, begin() + newSize);
		return 1;
	}

	if (newSize < dataSize)
	{
		destruct(begin() + newSize, begin() + dataSize);
		return -1;
	}

	return 0;

}

template<typename ElemType>
void Vector<ElemType>::reserve(int newCapacity)
{
	reAllocate(newCapacity);
}

template<typename ElemType>
void Vector<ElemType>::clear() noexcept
{
	for (int i = 0; i < dataSize; i++)
		trait::destroy(memoryManager, &data[i]);

	dataSize = 0;
}

template<typename ElemType>
bool Vector<ElemType>::isEmpty() const noexcept
{
	if (dataSize)
		return false;

	return true;
}


template<typename ElemType>
std::ostream& operator<<(std::ostream& out, const Vector<ElemType>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		out << vec.data[i] << ' ';
	}

	return out;
}


#endif // !CUSTOM_VECTOR_HEADER.H
