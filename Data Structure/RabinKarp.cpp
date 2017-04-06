#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& pat = input.pattern, txt = input.text;
    std::vector<int> ans;
	std::vector<int> rollingHashForText(txt.size() - pat.size() + 1);

	int prime = 101;	//prime
	int x = 256;		//alphabet

	int baseOffset = 1;

	//For a pattern with n+1 characters, 
	//the polynomial is going to look like the following (x is the base , or size of the alphabet):
	//Poly(pattern) = x^n * pattern[0] + x^n-1 * pattern[1] + ... + x * pattern[n-1] + pattern[n]
	//hash(pattern) = Poly(pattern) % prime
	//To calculate rolling hash for pattern starting from index 1 and ending at index (n+1)
	// Poly(pattern_1) = (Poly(pattern_0) - x^n pattern[0]) * x + pattern[n+1]
	// For calculating rolling hash, we need to store the value of x^n 
	// or the value of base ^ (patternLength -1) as a offset.
	for (int index = 0; index < pat.length() - 1; index++)
	{
		baseOffset = (baseOffset * x) % prime;
	}

	int patternHash = 0;
	rollingHashForText[0] = 0;
	for (int index = 0; index < pat.length(); index++)
	{
		patternHash = (x*patternHash + pat[index]) % prime;
		rollingHashForText[0] = (x*rollingHashForText[0] + txt[index]) % prime;
	}

	for (int index = 1; index <= txt.size() - pat.size(); index++)
	{
		auto nextChar = txt[index - 1 + pat.size()];
		auto charToRemove = txt[index - 1];
		int offsetToRemove = baseOffset * charToRemove;

		rollingHashForText[index] = ((rollingHashForText[index - 1] - offsetToRemove) * x + nextChar) % prime;
		if (rollingHashForText[index] < 0)
			rollingHashForText[index] += prime;
	}

	for (int index = 0; index < rollingHashForText.size(); index++)
	{
		if (patternHash == rollingHashForText[index])
		{
			//check for collision
			int subIndex = 0;
			for (subIndex = 0; subIndex < pat.length(); subIndex++)
			{
				if (pat[subIndex] != txt[index + subIndex])
					break;
			}
			if (subIndex == pat.length())
			{
				//matches
				ans.push_back(index);;
			}
		}
	}

    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
