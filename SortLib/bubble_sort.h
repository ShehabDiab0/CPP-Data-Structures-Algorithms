#pragma once

namespace SortLib
{
	template<typename ElemType, typename Comparator>
	void bubbleSort(std::vector<ElemType>& data, Comparator compare)
	{
		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data.size(); j++)
			{
				if (compare(data[i], data[j]))
					std::swap(data[i], data[j]);
			}
		}
	}
}