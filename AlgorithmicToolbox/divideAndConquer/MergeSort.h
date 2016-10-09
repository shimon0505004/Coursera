#pragma once
#include<vector>

namespace MergeSort
{
	template<class T>
	std::vector<T> mergeSort(std::vector<T> inputArray);

	template<class T>
	std::vector<T> merge(std::vector<T> lowerHalf,
		std::vector<T> upperHalf);


	template<class T>
	std::pair<std::vector<T>, int> mergeSort2(std::vector<T> inputArray);

	template<class T>
	std::pair<std::vector<T>, int> merge2(std::vector<T> lowerHalf,
		std::vector<T> upperHalf);

}

template<class T>
std::vector<T> MergeSort::mergeSort(std::vector<T> inputArray)
{
	if (inputArray.size() <= 1)
		return inputArray;

	int middleIndex = (inputArray.size() / 2);
	typename std::vector<T>::iterator middleIterator = inputArray.begin() + middleIndex;

	std::vector<T> lowerSortedArray = mergeSort(std::vector<T>(inputArray.begin(), middleIterator));
	std::vector<T> upperSortedArray = mergeSort(std::vector<T>(middleIterator, inputArray.end()));

	return MergeSort::merge(lowerSortedArray, upperSortedArray);
}

template<class T>
std::vector<T> MergeSort::merge(std::vector<T> lowerHalf,
	std::vector<T> upperHalf)
{
	std::vector<T> mergedArr;
	typename std::vector<T>::iterator lowerHalfIterator = lowerHalf.begin();
	typename std::vector<T>::iterator upperHalfIterator = upperHalf.begin();

	for (;
		lowerHalfIterator != lowerHalf.end() &&
		upperHalfIterator != upperHalf.end();
		)
	{
		if (*lowerHalfIterator <= *upperHalfIterator)
		{
			mergedArr.push_back(*lowerHalfIterator);
			lowerHalfIterator++;
		}
		else
		{
			mergedArr.push_back(*upperHalfIterator);
			upperHalfIterator++;
		}

	}
	if (lowerHalfIterator == lowerHalf.end())
		mergedArr.insert(mergedArr.end(), upperHalfIterator, upperHalf.end());
	else
		mergedArr.insert(mergedArr.end(), lowerHalfIterator, lowerHalf.end());

	return mergedArr;
}

//////MergeSort2 counts the number of invertions needed for sorting
template<class T>
std::pair<std::vector<T>, int> MergeSort::mergeSort2(std::vector<T> inputArray)
{
	if (inputArray.size() <= 1)
		return std::pair<std::vector<T>, int>(inputArray, 0);

	int middleIndex = (inputArray.size() / 2);
	typename std::vector<T>::iterator middleIterator = inputArray.begin() + middleIndex;

	std::pair<std::vector<T>, int> lowerSorted = mergeSort2(std::vector<T>(inputArray.begin(), middleIterator));
	std::pair<std::vector<T>, int> upperSorted = mergeSort2(std::vector<T>(middleIterator, inputArray.end()));

	std::pair<std::vector<T>, int> sorted = MergeSort::merge2(lowerSorted.first, upperSorted.first);
	return std::pair<std::vector<T>, int>(sorted.first, lowerSorted.second + upperSorted.second + sorted.second);
}

template<class T>
std::pair<std::vector<T>, int> MergeSort::merge2(std::vector<T> lowerHalf,
	std::vector<T> upperHalf)
{
	std::vector<T> mergedArr;
	int count = 0;
	typename std::vector<T>::iterator lowerHalfIterator = lowerHalf.begin();
	typename std::vector<T>::iterator upperHalfIterator = upperHalf.begin();

	for (;
		lowerHalfIterator != lowerHalf.end() &&
		upperHalfIterator != upperHalf.end();
		)
	{
		if (*lowerHalfIterator <= *upperHalfIterator)
		{
			mergedArr.push_back(*lowerHalfIterator);
			lowerHalfIterator++;
		}
		else
		{
			mergedArr.push_back(*upperHalfIterator);
			upperHalfIterator++;
			count+= distance(lowerHalfIterator, lowerHalf.end());
		}

	}
	if (lowerHalfIterator == lowerHalf.end())
		mergedArr.insert(mergedArr.end(), upperHalfIterator, upperHalf.end());
	else
		mergedArr.insert(mergedArr.end(), lowerHalfIterator, lowerHalf.end());

	return std::pair<std::vector<T>, int>(mergedArr, count);
}

