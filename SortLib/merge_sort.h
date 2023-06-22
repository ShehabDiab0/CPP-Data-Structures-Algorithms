#pragma once

namespace SortLib
{
	template<typename ElemType, typename Comparator>
	void mergeSort(std::vector<ElemType>& data, Comparator compare)
	{
		Details::mergeDriver(data, 0, data.size() - 1, compare);
	}

	template<typename ElemType, typename Comparator>
	void mergeSortRange(std::vector<ElemType>& data, int startIndex, int endIndex, Comparator compare)
	{
		Details::mergeDriver(data, startIndex, endIndex, compare);
	}
}



namespace SortLib
{
	namespace Details
	{
		template<typename ElemType, typename Comparator>
		void merge(std::vector<ElemType>& data, int low, int mid, int high, Comparator compare)
		{
			if (low >= high)
				return;

			std::vector<ElemType> sortedArr(high - low + 1);
			int leftCounter = low;
			int rightCounter = mid + 1;
			int indexTrack = 0;

			while (leftCounter <= mid && rightCounter <= high)
			{
				if (compare(data[leftCounter], data[rightCounter]))
				{
					sortedArr[indexTrack++] = std::move(data[leftCounter++]);
					continue;
				}
				sortedArr[indexTrack++] = std::move(data[rightCounter++]);
			}

			while (leftCounter <= mid)
				sortedArr[indexTrack++] = std::move(data[leftCounter++]);
			while (rightCounter <= high)
				sortedArr[indexTrack++] = std::move(data[rightCounter++]);

			for (int i = 0; i < high - low + 1; i++)
				data[i + low] = std::move(sortedArr[i]);
		}


		template<typename ElemType, typename Comparator>
		void mergeDriver(std::vector<ElemType>& data, int low, int high, Comparator compare)
		{
			if (low >= high)
				return;

			int mid = (low + high) / 2;
			mergeDriver(data, low, mid, compare);
			mergeDriver(data, mid + 1, high, compare);
			merge(data, low, mid, high, compare);
		}
	}
}














