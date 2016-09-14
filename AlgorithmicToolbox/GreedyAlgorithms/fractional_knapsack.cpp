#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class item
{
public:
	int value_i;
	int weight_i;
	long double value_weight_ratio_i;
	item(int v = 0, int w = 0)
	{
		value_i = v;
		weight_i = w;
		if (w != 0)
		{
			value_weight_ratio_i = static_cast<long double>((static_cast<long double>(v)) / w);
		}
	}
	bool operator<(const item& secondItem) const
	{
		return value_weight_ratio_i < secondItem.value_weight_ratio_i;
	}
};

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
	double value = 0.0;
	int index = 0;
	vector<item> items(weights.size());
	for (vector<int>::iterator weightIterator = weights.begin(); weightIterator != weights.end(); weightIterator++)
	{
		items[index] = item(values[index], weights[index]);
		index++;
	}
	sort(items.begin(), items.end());

	for (vector<item>::iterator itemIterator = items.begin(); itemIterator != items.end(); itemIterator++)
	{
		std::cout << (*itemIterator).value_weight_ratio_i << std::endl;
	}
	// write your code here

	return value;
}

int main() {
	int n;
	int capacity;
	std::cin >> n >> capacity;
	vector<int> values(n);
	vector<int> weights(n);
	for (int i = 0; i < n; i++) {
		std::cin >> values[i] >> weights[i];
	}

	double optimal_value = get_optimal_value(capacity, weights, values);

	std::cout.precision(10);
	std::cout << optimal_value << std::endl;
	return 0;
}
