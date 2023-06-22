#pragma once

template<typename ElemType, typename Comparator>
void bubbleSort(std::vector<ElemType>& data, Comparator compare)
{
	for (int i = 0; i < data.size() - 1; i++)
	{
		bool isSwapped = false;
		for (int j = 0; j < data.size() - i - 1; j++)
		{
			if (compare(data[j], data[j + 1]))
			{
				std::swap(data[j], data[j + 1]);
				isSwapped = true;
			}
		}
		if (!isSwapped)
			break;
	}
}