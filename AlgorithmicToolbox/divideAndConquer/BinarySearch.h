#pragma once

#include<vector>

namespace BinarySearch {

	template<typename T>
	int binary_search(const std::vector<T>& inputArray, const T& key)
	{
		return binary_search(inputArray, inputArray.begin(), inputArray.end(), key);
	}

	template<typename T>
	int binary_search(const std::vector<T>& inputArray,
		const typename std::vector<T>::const_iterator& begin,
		const typename std::vector<T>::const_iterator& end,
		const T& key)
	{
		if (begin < inputArray.begin() || end > inputArray.end())
			return -1;

		if (begin >= end)
			return -1;

		if (std::distance(begin,end) == 1)
		{
			if (key == *begin)
				return std::distance(inputArray.begin(), begin);
			else
				return -1;
		}
		else 
		{
			int numberOfElement = std::distance(begin, end);
			int middleElementIndex = floor(numberOfElement / 2);
			if (key == *(begin + middleElementIndex))
				return middleElementIndex;
			else if (key < *(begin + middleElementIndex))
				return binary_search(inputArray, begin, begin + middleElementIndex, key);
			else
				return binary_search(inputArray, begin + middleElementIndex + 1, end, key);
		}
	}
}

