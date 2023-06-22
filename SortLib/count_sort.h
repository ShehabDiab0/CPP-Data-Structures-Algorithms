#pragma once
#include <vector>
#include <algorithm>



namespace SortLib
{
	void countSort(std::vector<int>& nums)
	{
		auto [minValue, maxValue] = std::minmax_element(nums.begin(), nums.end());
		std::vector<int> occurrences(*maxValue - *minValue + 1, 0);

		for (int i = 0; i < nums.size(); i++)
			occurrences[nums[i] - *minValue]++;

		for (int i = 1; i < occurrences.size(); i++)
			occurrences[i] += occurrences[i - 1];

		std::vector<int> finalSortedArr(nums.size());
		for (int i = nums.size() - 1; i >= 0; i--)
		{
			int currNumber = nums[i];
			int elementFinalIndex = occurrences[currNumber - *minValue] - 1;
			finalSortedArr[elementFinalIndex] = currNumber;
			occurrences[currNumber - *minValue]--;
		}

		nums = std::move(finalSortedArr);
	}
}