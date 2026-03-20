#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity)
{
	if (capacity <= 0)
	{
		throw std::exception();
	}

	this->elements = new TElem[capacity];
	this->capacity = capacity;
	this->mapSize = 0;
}

FixedCapBiMap::~FixedCapBiMap()
{
	delete[] this->elements;
}

bool FixedCapBiMap::add(TKey c, TValue v)
{
	if (this->mapSize == this->capacity)
	{
		throw std::exception();
	}

	short hit = 0;
	for (int i = 0; i < this->mapSize; i++)
	{
		if (this->elements[i].first == c)
		{
			if (hit == 1)
				return false;
			hit++;
		}
	}

	this->elements[this->mapSize++] = TElem{c, v};
	return true;
}

ValuePair FixedCapBiMap::search(TKey c) const
{
	ValuePair query{NULL_TVALUE, NULL_TVALUE};

	short hit = 0;
	for (int i = 0; i < this->mapSize; i++)
	{
		if (this->elements[i].first == c)
		{
			if (hit == 0)
			{
				query.first = this->elements[i].second;
			}
			else if (hit == 1)
			{
				query.second = this->elements[i].second;
			}
			hit++;
		}
	}

	return query;
}

bool FixedCapBiMap::remove(TKey c, TValue v)
{
	TElem elem{c, v};

	int foundIndex = -1;

	for (int i = 0; i < this->mapSize; ++i)
	{
		// This should be fine since TElem is "simple"
		if (this->elements[i] == elem)
		{
			foundIndex = i;
			break;
		}
	}

	if (foundIndex == -1)
	{
		return false;
	}

	// Order doesn't matter, so move last el to targeted el - 0(1)
	this->elements[foundIndex] = this->elements[this->mapSize - 1];
	this->mapSize--;

	// Classic Approach (shift left) - 0(n)
	// for (int i = foundIndex; i < this->mapSize - 1; i++)
	// {
	// 	this->elements[i] = this->elements[i + 1];
	// }
	// this->mapSize--;

	return true;
}

int FixedCapBiMap::size() const
{
	return this->mapSize;
}

bool FixedCapBiMap::isEmpty() const
{
	return this->mapSize == 0;
}

bool FixedCapBiMap::isFull() const
{
	return this->mapSize == this->capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const
{
	return FixedCapBiMapIterator(*this);
}
