#pragma once
#include <vector>

template<typename ElemType, typename Comparator = std::less<ElemType>>
void bubbleSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void insertionSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void selectionSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void shellSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void mergeSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void mergeSortRange(std::vector<ElemType>& data, int startIndex, int endIndex, Comparator compare = std::less<ElemType>());

void countSort(std::vector<int>& data); // works only with numbers

// these are coming soon
/*
template<typename ElemType, typename Comparator = std::less<ElemType>>
void quickSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void quickSortRange(std::vector<ElemType>& data,int startIndex, int endIndex, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void threeWayQuickSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void heapSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());

template<typename ElemType, typename Comparator = std::less<ElemType>>
void introSort(std::vector<ElemType>& data, Comparator compare = std::less<ElemType>());
*/


// util functions for mergeSort
namespace Details
{
	template<typename ElemType, typename Comparator = std::less<ElemType>>
	void merge(std::vector<ElemType>& nums, int low, int mid, int high, Comparator compare = std::less<ElemType>());

	template<typename ElemType, typename Comparator = std::less<ElemType>>
	void mergeDriver(std::vector<ElemType>& data, int low, int high, Comparator compare = std::less<ElemType>());
}

#include "bubble_sort.h"
#include "count_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "selection_sort.h"
#include "shell_sort.h"