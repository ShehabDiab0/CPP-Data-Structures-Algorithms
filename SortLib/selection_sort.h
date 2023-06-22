#pragma once


template<typename ElemType, typename Comparator>
void selectionSort(std::vector<ElemType>& data, Comparator compare)
{
	for (int i = 0; i < data.size(); i++)
	{
		int leastValueIndex = i;
		for (int j = i + 1; j < data.size(); j++)
		{
			if (compare(data[j], data[leastValueIndex]))
				leastValueIndex = j;
		}

		std::swap(data[i], data[leastValueIndex]);
	}
}
