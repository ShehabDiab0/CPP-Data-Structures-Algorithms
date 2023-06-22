#pragma once


template<typename ElemType, typename Comparator>
void shellSort(std::vector<ElemType>& data, Comparator compare)
{
	for (int gap = data.size() / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < data.size(); i++)
		{
			ElemType element = data[i];
			int j = i;
			while (j >= gap && compare(element, data[j - gap]))
			{
				data[j] = data[j - gap];
				j -= gap;
			}

			data[j] = element;
		}
	}
}
