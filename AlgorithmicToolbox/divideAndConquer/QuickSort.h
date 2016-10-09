#pragma once
#include <random>

namespace QuickSort
{
	template<class T>
	void quickSort(std::vector<T>& inputArray, int low, int high);

	template<class T>
	int partition(std::vector<T>& inputArray, int low, int high);

	template<class T>
	void quickSort3(std::vector<T>& inputArray, int low, int high);

	template<class T>
	std::pair<int, int> partition3(std::vector<T>& inputArray, int low, int high);

	template<class T>
	void swap(T& first, T& second);
};

template<class T>
void QuickSort::quickSort(std::vector<T>& inputArray, int low, int high)
{
	if (low >= high)
		return;
	int randomIndex = (rand() % (high - low + 1)) + low;
	swap(inputArray[randomIndex], inputArray[low]);

	int partitionIndex = partition(inputArray, low, high);
	quickSort(inputArray, low, partitionIndex - 1);
	quickSort(inputArray, partitionIndex + 1, high);

}

template<class T>
int QuickSort::partition(std::vector<T>& inputArray, int low, int high)
{
	T pivotElement = inputArray[low];
	int finalPivotSwapIndex = low;
	for (int index = low + 1; index <= high; index++)
	{
		if (inputArray[index] <= pivotElement)
		{
			finalPivotSwapIndex++;
			swap(inputArray[index], inputArray[finalPivotSwapIndex]);
		}
	}
	swap(inputArray[low], inputArray[finalPivotSwapIndex]);
	return finalPivotSwapIndex;
}

template<class T>
void QuickSort::swap(T& first, T& second)
{
	T temp = first;
	first = second;
	second = temp;
}

template<class T>
void QuickSort::quickSort3(std::vector<T>& inputArray, int low, int high)
{
	if (low >= high)
		return;
	int randomIndex = (rand() % (high - low + 1)) + low;
	swap(inputArray[randomIndex], inputArray[low]);

	std::pair<int, int> partitionLowHigh = partition3(inputArray, low, high);
	quickSort(inputArray, low, partitionLowHigh.first - 1);
	quickSort(inputArray, partitionLowHigh.second + 1, high);

}

//dijkstra's 3-way partitioning algorithm
template<class T>
std::pair<int, int> QuickSort::partition3(std::vector<T>& inputArray, int low, int high)
{
	T partitioningItem = inputArray[low];
	int lt = low;
	int gt = high;
	for (int i = low; i <= gt;)
	{
		if (inputArray[i] < partitioningItem)
		{
			swap(inputArray[lt], inputArray[i]);
			i++;
			lt++;
		}
		else if (inputArray[i] > partitioningItem)
		{
			swap(inputArray[gt], inputArray[i]);
			gt--;
		}
		else
		{
			i++;
		}
	}

	std::pair<int, int> partitionarr(lt, gt);
	return partitionarr;
}
