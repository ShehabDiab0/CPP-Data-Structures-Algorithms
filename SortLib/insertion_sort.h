#pragma once

template<typename ElemType, typename Comparator>
void insertionSort(std::vector<ElemType>& data, Comparator compare)
{
	for (int i = 1; i < data.size(); i++)
	{
		ElemType element = data[i];
		int j = i;
		while (j > 0 && compare(element, data[j - 1]))
		{
			data[j] = data[j - 1];
			j--;
		}
		data[j] = element;
	}
}
