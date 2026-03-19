#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity)
{
	// If capacity is less or equal to 0 we throw bad request
	if (capacity <= 0)
		throw 400;

	// Data is dynamic
	this->data = new Data;
	this->capacity = capacity;
	this->len = 0;
}

FixedCapBiMap::~FixedCapBiMap()
{
	delete this->data;
}

bool FixedCapBiMap::add(TKey c, TValue v)
{
	// If it's full throw bad request
	if (isFull())
		throw 400;

	// Check if the given key has 2 associated values already
	short key_associated_values = 0;
	for (int i = 0; i < len; ++i)
	{
		if (key_associated_values == 2)
			return false;

		if (this->data[i]->first == c)
		{
			key_associated_values++;
		}
	}

	// Add the new pair to the data
	// Probably a better way of doing this
	this->data[len++]->first = c;
	this->data[len++]->second = v;
}

ValuePair FixedCapBiMap::search(TKey c) const
{
	// TODO - Implementation
	return std::pair<TValue, TValue>(NULL_TVALUE, NULL_TVALUE);
}

bool FixedCapBiMap::remove(TKey c, TValue v)
{
	// TODO - Implementation
	// Find the pair in our data
	int pair_index = -1;
	for (int i = 0; i < size(); ++i)
	{
		if (this->data[i]->first == c && this->data[i]->second == v)
		{
			pair_index = i;
			break;
		}
	}

	if (pair_index == -1)
	{
		// We remove the pair now
		// Shifting the pairs to the left like in a vector?
		for (int i = pair_index; i < size() - 1; ++i)
		{
			this->data[i]->first = this->data[i + 1]->first;
			this->data[i]->second = this->data[i + 1]->second;
		}
		// Update the len
		this->len--;
		return true;
	}
	else
	{
		return false;
	}
}

int FixedCapBiMap::size() const
{
	// TODO - Implementation
	return this->len;
}

bool FixedCapBiMap::isEmpty() const
{
	// TODO - Implementation
	return this->len == 0;
}

bool FixedCapBiMap::isFull() const
{
	// TODO - Implementation
	return this->len == this->capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const
{
	return FixedCapBiMapIterator(*this);
}
