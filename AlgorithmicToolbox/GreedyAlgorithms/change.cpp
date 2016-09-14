#include <iostream>

int get_change(int m) {
  //write your code here
	int count = 0;
	int divisor = static_cast<int>(m / 10);
	count += divisor;
	m = m % 10;

	divisor = static_cast<int>(m / 5);
	count += divisor;
	m = m % 5;

	divisor = static_cast<int>(m / 1);
	count += divisor;
	m = m % 1;

  return count;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
