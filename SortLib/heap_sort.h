#pragma once

template<typename ElemType, typename Comparator>
void heapSort(std::vector<ElemType>& data, Comparator compare)
{
	Details::buildHeap(data, compare);
	for (int i = data.size() - 1; i > 0; i--)
	{
		std::swap(data[0], data[i]);
		Details::heapifyDownwards(data, 0, i, compare);
	}
}


namespace Details
{
	template<typename ElemType, typename Comparator>
	void heapifyDownwards(std::vector<ElemType>& heap, int parentIndex, int maxHeapSize, Comparator compare)
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
			heapifyDownwards(heap, toSwap, maxHeapSize, compare);
		}
	}

	template<typename ElemType, typename Comparator>
	void buildHeap(std::vector<ElemType>& heap, Comparator compare)
	{
		int heapSize = heap.size();
		for (int i = (heap.size() / 2) - 1; i >= 0; i--)
			heapifyDownwards(heap, i, heapSize, compare);
	}
};