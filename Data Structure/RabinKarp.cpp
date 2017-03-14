#include<iostream>
#include<string>
#include<vector>

using std::string;

struct Data {
	std::string pattern, text;
};

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

size_t hash_value(std::string str, unsigned long long base, unsigned long long  prime)
{
	int hashCode = 0;
	for (int index = 0; index < str.length(); index++)
	{
		hashCode = ((base * hashCode) % prime );
		hashCode = (hashCode + str[index]) % prime;
	}
	return hashCode;
}

std::vector<size_t> hash_lookup_array(std::string text
	, int patternLength
	, unsigned long long base
	, unsigned long long prime)
{
	std::vector<size_t> hashArr(text.length() - patternLength + 1);
	hashArr[0] = hash_value(text.substr(0, patternLength), base, prime);
	size_t highestRadix = 1;
	for(int counter = 0; counter< patternLength ; counter++) 
	{
		highestRadix = (highestRadix * base) % prime;
	}

	for (int index = 1; index <= text.length() - patternLength; index++)
	{
		/*
		int tempHashCode = (base * hashArr[index - 1]) % prime;
		tempHashCode = (tempHashCode + text[index + patternLength - 1]) % prime;
		int valueToSubtract = (prime - (highestRadix * text[index - 1])) % prime;
		tempHashCode = (tempHashCode + valueToSubtract) % prime;
		hashArr[index] = tempHashCode;
		*/
		hashArr[index] = hash_value(text.substr(index, patternLength), base, prime);
	}
	return hashArr;
}

std::vector<int> rabin_karp_implementation(std::string text, std::string pattern)
{
	std::vector<int> answerIndexArr;
	unsigned long long base = 256; // number of characters in unicode alphabet 0 ~ 255
	unsigned long long prime = 16777213; // a large prime > base * base;
	size_t patternHash = hash_value(pattern, base, prime);
	auto hashArr = hash_lookup_array(text, pattern.length(), base, prime);
	for (int index = 0; index < hashArr.size(); index++)
	{
		if (hashArr[index] == patternHash)
		{
			if (text.substr(index, pattern.length()) == pattern)
			{
				answerIndexArr.push_back(index);
			}
		}
	}
	return answerIndexArr;
}

void print_occurrences(const std::vector<int>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		std::cout << output[i] << " ";
	std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
	return rabin_karp_implementation(input.text, input.pattern);
}

int main(void)
{
	print_occurrences(get_occurrences(read_input()));
	return 0;
}



