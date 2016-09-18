#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  //write your code here
  int k = floor(((sqrt((8 * (static_cast<double>(n))) + 1))-1) / 2);
  //std::cout << k << std::endl;
  //double k = static_cast<double>( (((sqrt(8.00) * sqrt((static_cast<double>(n)) + (static_cast<double>(1 / 8)))) -1 )/ 2));
  int difference = n -(k*(k+1)/2);
  int check = 0;
  for (int index = 0; index < k; index++)
  {
	  summands.push_back(index + 1);
	  check += (index + 1);
  }
  summands[k - 1] = summands[k - 1] + difference;
  check += difference;
  if (check != n)
  {
	  std::cout << "Error" << std::endl;
  }

  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
