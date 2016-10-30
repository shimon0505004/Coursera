#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include "KnapsackItem.h"

using namespace std;

namespace FractionalKnapsack
{
	
	double maxValue_FractionalKnapsack(vector<KnapsackItem> items, int capacity)
	{
		double maxValue = 0;
		int leftOverCapacity = capacity;
		sort(items.begin(), items.end(), std::greater<>());
		for (vector<KnapsackItem>::iterator item = items.begin(); item != items.end() 
			&& leftOverCapacity>0; item++)
		{
			if (leftOverCapacity - item->getWeight() >= 0)
			{
				maxValue += item->getValue();
				leftOverCapacity -= item->getWeight();
			}
			else
			{
				double fractionalValueOfItem = leftOverCapacity*(item->getValuePerWeight());
				maxValue += fractionalValueOfItem;
				leftOverCapacity -= leftOverCapacity;

			}
		}


		return maxValue;
	}
}
