#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;

FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap &d) : map(d)
{
	this->currentIndex = 0;
}

void FixedCapBiMapIterator::first()
{
	this->currentIndex = 0;
}

void FixedCapBiMapIterator::next()
{
	if (!this->valid())
	{
		throw exception();
	}

	this->currentIndex++;
	return;
}

TElem FixedCapBiMapIterator::getCurrent()
{
	if (!this->valid())
	{
		throw exception();
	}

	return this->map.elements[this->currentIndex];
}

bool FixedCapBiMapIterator::valid() const
{
	return this->currentIndex < this->map.size();
}
