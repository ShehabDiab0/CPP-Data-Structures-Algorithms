#pragma once
#include <algorithm>
#include <stdexcept>
#include <vector>

template<typename T, typename Comparator = std::less<T>>
class PriorityQueue
{
private:
	std::vector<T> heap;
	Comparator compare;

private:
	void heapifyUpwards(int index);
	void heapifyDownwards(int parentIndex, int maxHeapSize);

public:
	PriorityQueue() = default;

	void push(const T& data);
	void pop();
	T& top();

	void clear();
	bool empty();

};


template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(const T& data)
{
	heap.push_back(data);
	heapifyUpwards(heap.size() - 1);
}

template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::pop()
{
	if (heap.empty())
		throw std::out_of_range("Heap is empty");

	std::swap(heap[0], heap[heap.size() - 1]);
	heap.pop_back();

	if (heap.size() > 1)
		heapifyDownwards(0, heap.size());
}

template<typename T, typename Comparator>
T& PriorityQueue<T, Comparator>::top()
{
	if (heap.empty())
		throw std::out_of_range("Heap is empty");

	return this->heap[0];
}

template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::clear()
{
	heap.clear();
}

template<typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::empty()
{
	return heap.empty();
}


template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::heapifyUpwards(int index)
{
	int parentIndex = (index - 1) / 2;

	while (parentIndex >= 0 && compare(heap[index], heap[parentIndex]))
	{
		std::swap(heap[index], heap[parentIndex]);
		index = parentIndex;
		parentIndex = (index - 1) / 2;
	}
}

template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::heapifyDownwards(int parentIndex, int maxHeapSize)
{
	int leftNode = (2 * parentIndex) + 1;
	int rightNode = (2 * parentIndex) + 2;

	int toSwap = parentIndex;

	if (leftNode < maxHeapSize && compare(heap[leftNode], heap[toSwap]))
		toSwap = leftNode;
	if (rightNode < maxHeapSize && compare(heap[rightNode], heap[toSwap]))
		toSwap = rightNode;

	if (toSwap != parentIndex)
	{
		std::swap(heap[parentIndex], heap[toSwap]);
		heapifyDownwards(toSwap, maxHeapSize);
	}
}