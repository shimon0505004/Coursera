#pragma once
#include<Vector>
#include<Map>
#include<cmath>

namespace MajorityElement 
{
	template<class T>
	bool find_majority(const std::vector<T>& list);
};

template<class T>
bool MajorityElement::find_majority(const std::vector<T>& list)
{
	int majority_size = floor(list.size() / 2) + 1;
	std::map<T, int> countMap;

	for (int index=0;
		index < list.size(); index++)
	{
		if (countMap.empty() || countMap.count(list[index]) == 0)
		{
			int count = 1;
			countMap[list[index]] = count;
			if (count >= majority_size)
				return true;
		}
		else
		{
			int currentSize = countMap[list[index]];
			currentSize++;
			countMap[list[index]] = currentSize;
			if (currentSize >= majority_size)
				return true;
		}
	}
	return false;
}

