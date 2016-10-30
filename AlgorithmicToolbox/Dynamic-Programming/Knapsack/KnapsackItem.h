#pragma once
class KnapsackItem
{
public:
	explicit KnapsackItem(int value, int weight);
	~KnapsackItem();
	int getValue();
	int getWeight();
	double getValuePerWeight();

	bool operator< (const KnapsackItem& second);
	bool operator> (const KnapsackItem& second);
	bool operator== (const KnapsackItem& second);
	bool operator<= (const KnapsackItem& second);
	bool operator>= (const KnapsackItem& second);

private:
	int value;
	int weight;
	double valuePerWeight;
};

