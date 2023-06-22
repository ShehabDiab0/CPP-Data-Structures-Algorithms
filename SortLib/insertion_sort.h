#pragma once

namespace SortLib
{
	template<typename ElemType, typename Comparator>
	void insertionSort(std::vector<ElemType>& data, Comparator compare)
	{
		for (int i = 1; i < data.size(); i++)
		{
			for (int j = i; j > 0 && compare(data[j], data[j - 1]); j--)
			{
				std::swap(data[j], data[j - 1]);
			}
		}
	}
}