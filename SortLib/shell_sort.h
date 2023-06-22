#pragma once

namespace SortLib
{
	template<typename ElemType, typename Comparator>
	void shellSort(std::vector<ElemType>& data, Comparator compare)
	{
		for (int gap = data.size() / 2; gap > 0; gap /= 2)
		{
			for (int i = gap; i < data.size(); i++)
			{
				for (int j = i; j >= gap && compare(data[j], data[j - gap]); j -= gap)
				{
					std::swap(data[j], data[j - gap]);
				}
			}
		}
	}
}