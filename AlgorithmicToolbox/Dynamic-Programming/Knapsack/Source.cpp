#include <iostream>
#include <vector>
#include "KnapsackItem.h"
#include "FractionalKnapsack.h"
#include "DiscreteKnapsack.h"

using namespace std;


/////////////////////////////////////////////////////////////////////
///
/// \brief starter file for fractional and discrete knapsack problem
///
///
///
///
////////////////////////////////////////////////////////////////////

int main(void)
{
	int numberOfItems, capacity;
	cin >> capacity;
	cin >> numberOfItems;
	vector<KnapsackItem> items;
	for (int count = 0; count < numberOfItems; count++)
	{
		int value, weight;
		cin >> value;
		cin >> weight;
		KnapsackItem newItem(weight, weight);
		items.push_back(newItem);
	}

	cout << FractionalKnapsack::maxValue_FractionalKnapsack(items, capacity) << endl;
	cout << DiscreteKnapsack_WithRepetation::maxValue_BottomUpDP(items, capacity) << endl;
	cout << DiscreteKnapsack_WithRepetation::maxValue_TopDown(items, capacity) << endl;
	cout << DiscreteKnapsack_WithoutRepetation::maxValue_BottomUpDP(items, capacity) << endl;


}
