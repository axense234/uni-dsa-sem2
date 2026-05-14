#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap()
{
	this->m = 16;
	this->table = new KeyNode *[m]();
	this->numberOfKeys = 0;
	this->totalPairs = 0;
	this->loadFactorThreshold = 0.75;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

void MultiMap::resize()
{
	int newM = m * 2;
	KeyNode **newTable = new KeyNode *[newM]();

	for (int i = 0; i < m; i++)
	{
		KeyNode *current = table[i];
		while (current != nullptr)
		{
			KeyNode *next = current->next;

			int newIndex = ((current->key % newM) + newM) % newM;

			current->next = newTable[newIndex];
			newTable[newIndex] = current;

			current = next;
		}
		table[i] = nullptr;
	}

	delete[] table;
	table = newTable;
	m = newM;
}
// BC: Theta(totalPairs)
// WC: Theta(totalPairs)
// TC: Theta(totalPairs)

void MultiMap::add(TKey c, TValue v)
{
	if ((float)this->numberOfKeys / this->m > this->loadFactorThreshold)
	{
		resize();
	}

	int index = hash(c);
	KeyNode *current = table[index];

	while (current != nullptr)
	{
		if (current->key == c)
		{
			if (current->valuesCount >= current->valuesCapacity)
			{
				current->valuesCapacity *= 2;
				TValue *newValues = new TValue[current->valuesCapacity];
				for (int i = 0; i < current->valuesCount; i++)
				{
					newValues[i] = current->values[i];
				}
				delete[] current->values;
				current->values = newValues;
			}
			current->values[current->valuesCount++] = v;
			this->totalPairs++;
			return;
		}
		current = current->next;
	}

	KeyNode *newNode = new KeyNode;
	newNode->key = c;
	newNode->valuesCount = 1;
	newNode->valuesCapacity = 4;
	newNode->values = new TValue[4];
	newNode->values[0] = v;
	newNode->next = table[index];
	table[index] = newNode;
	numberOfKeys++;
	totalPairs++;
}
// BC: Theta(1)
// WC: Theta(totalPairs) resize
// TC: O(totalPairs)

bool MultiMap::remove(TKey c, TValue v)
{
	int index = hash(c);
	KeyNode *current = table[index];
	KeyNode *prev = nullptr;

	while (current != nullptr)
	{
		if (current->key == c)
		{
			for (int i = 0; i < current->valuesCount; i++)
			{
				if (current->values[i] == v)
				{
					for (int j = i; j < current->valuesCount - 1; j++)
					{
						current->values[j] = current->values[j + 1];
					}
					current->valuesCount--;
					totalPairs--;

					if (current->valuesCount == 0)
					{
						if (prev == nullptr)
						{
							table[index] = current->next;
						}
						else
						{
							prev->next = current->next;
						}
						delete[] current->values;
						delete current;
						numberOfKeys--;
					}
					return true;
				}
			}
			return false;
		}
		prev = current;
		current = current->next;
	}
	return false;
}
// BC: Theta(1) -> found at start
// WC: Theta(totalPairs) -> vlaue not found
// TC: O(totalPairs)

vector<TValue> MultiMap::search(TKey c) const
{
	int index = hash(c);
	KeyNode *current = table[index];

	while (current != nullptr)
	{
		if (current->key == c)
		{
			std::vector<TValue> result;
			for (int i = 0; i < current->valuesCount; i++)
			{
				result.push_back(current->values[i]);
			}
			return result;
		}
		current = current->next;
	}
	return std::vector<TValue>();
}
// BC: Theta(1) -> found at start
// WC: Theta(n) -> all keys in same bucket
// TC: O(n)

int MultiMap::size() const
{
	return totalPairs;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool MultiMap::isEmpty() const
{
	return totalPairs == 0;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

MultiMapIterator MultiMap::iterator() const
{
	return MultiMapIterator(*this);
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

MultiMap::~MultiMap()
{
	for (int i = 0; i < m; i++)
	{
		KeyNode *current = table[i];
		while (current != nullptr)
		{
			KeyNode *next = current->next;
			delete[] current->values;
			delete current;
			current = next;
		}
	}
	delete[] table;
}
// BC: Theta(totalPairs + m)
// WC: Theta(totalPairs + m)
// TC: Theta(totalPairs + m)