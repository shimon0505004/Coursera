#include "KnapsackItem.h"

KnapsackItem::KnapsackItem(int value, int weight)
{
	this->value = value;
	this->weight = weight;
	if (weight == 0)
		this->valuePerWeight = 0;
	else
		this->valuePerWeight = (static_cast<double>(value) / static_cast<double>(weight));
}

KnapsackItem::~KnapsackItem()
{
}

int KnapsackItem::getValue()
{
	return value;
}

int KnapsackItem::getWeight()
{
	return weight;
}

double KnapsackItem::getValuePerWeight()
{
	return valuePerWeight;
}

bool KnapsackItem::operator<(const KnapsackItem& second)
{
	return this->valuePerWeight < second.valuePerWeight;
}

bool KnapsackItem::operator>(const KnapsackItem& second)
{
	return this->valuePerWeight > second.valuePerWeight;
}

bool KnapsackItem::operator<=(const KnapsackItem& second)
{
	return this->valuePerWeight <= second.valuePerWeight;
}

bool KnapsackItem::operator>=(const KnapsackItem& second)
{
	return this->valuePerWeight >= second.valuePerWeight;
}

bool KnapsackItem::operator==(const KnapsackItem& second)
{
	return this->valuePerWeight == second.valuePerWeight;
}
