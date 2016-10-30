#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include "KnapsackItem.h"
#include <Map>

using namespace std;

namespace DiscreteKnapsack_WithRepetation
{
	map<int, int> MemoizationHashTable;
	vector<int> value;

	int maxValue_BottomUpDP(vector<KnapsackItem> items, int capacity);
	int maxValue_TopDown(vector<KnapsackItem> items
		, int capacity);
	int maxValue_UsingMemoization(vector<KnapsackItem> items
		, int capacity);

}

namespace DiscreteKnapsack_WithoutRepetation
{
	int maxValue_BottomUpDP(vector<KnapsackItem> items, int capacity);
}



int DiscreteKnapsack_WithRepetation::maxValue_BottomUpDP(vector<KnapsackItem> items, int capacity)
{
	value.clear();
	value = vector<int>(capacity + 1);
	value[0] = 0;
	for (int weight = 1; weight <= capacity; weight++)
	{
		value[weight] = 0;
		for (int index = 0; index < items.size(); index++)
		{
			if (items[index].getWeight() <= weight)
			{
				auto newValue = value[weight - items[index].getWeight()] + items[index].getValue();
				if (newValue > value[weight])
					value[weight] = newValue;
			}
		}
	}
	return value[capacity];
}

int DiscreteKnapsack_WithRepetation::maxValue_TopDown(vector<KnapsackItem> items
	, int capacity)
{
	MemoizationHashTable.clear();
	value.clear();
	for (int index = 0; index <= capacity; index++)
	{
		value.push_back(0);
	}
	return maxValue_UsingMemoization(items, capacity);

}

int DiscreteKnapsack_WithRepetation::maxValue_UsingMemoization(vector<KnapsackItem> items
	, int capacity)
{
	if (MemoizationHashTable.find(capacity) != MemoizationHashTable.end())
	{
		return MemoizationHashTable.at(capacity);
	}
	value[capacity] = 0;
	for (vector<KnapsackItem>::iterator item = items.begin(); item != items.end(); item++)
	{
		if (item->getWeight() <= capacity)
		{
			auto newValue = maxValue_UsingMemoization(items
				, capacity - item->getWeight()) + item->getValue();

			if (newValue > value[capacity])
				value[capacity] = newValue;
		}
	}
	MemoizationHashTable[capacity] = value[capacity];
	return value[capacity];
}


int DiscreteKnapsack_WithoutRepetation::maxValue_BottomUpDP(vector<KnapsackItem> items
	, int capacity)
{
	typedef vector<int> Row;
	typedef vector<Row> Matrix;

	Matrix value(capacity + 1, Row(items.size() + 1));
	for (int weight = 0; weight <= capacity; weight++)
	{
		for (int index = 0; index <= items.size(); index++)
		{
			value[weight][index] = 0;
		}
	}

	for (int weight = 1; weight <= capacity; weight++)
	{
		for (int index = 1; index <= items.size(); index++)
		{
			int max_value = value[weight][index-1];
			if (weight - items[index - 1].getWeight() >= 0)
			{
				int new_Max_value = (value[weight - items[index - 1].getWeight()][index - 1])
					+ items[index - 1].getValue();
				if (new_Max_value > max_value)
					max_value = new_Max_value;
			}
			value[weight][index] = max_value;
		}
	}

	return value[capacity][items.size()];
}
