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
	item(int v=0, int w=0)
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
  double capacity_in_double = static_cast<double>(capacity);
  vector<item> items(weights.size());
  for (vector<int>::iterator weightIterator = weights.begin(); weightIterator != weights.end(); weightIterator++)
  {
	  items[index] = item(values[index], weights[index]);
	  index++;
  }
  sort(items.begin(), items.end());

  int countOfTotalItems = index;
  index =0;
    
  for(int index=0; index<countOfTotalItems ; index++)
  {
    if(capacity_in_double==0)
    {
        return value;    
    }
    double weight_of_i_that_can_be_put_inside_knapsack = std::min(static_cast<double>(items[index].weight_i),capacity_in_double);
    value = value + (weight_of_i_that_can_be_put_inside_knapsack)*((static_cast<double>(items[index].value_i)/items[index].weight_i));
    capacity_in_double = capacity_in_double-weight_of_i_that_can_be_put_inside_knapsack;
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
