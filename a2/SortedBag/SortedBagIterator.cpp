#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag &b) : bag(b)
{
	this->currentIndex = 0;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

TComp SortedBagIterator::getCurrent()
{
	if (!this->valid())
	{
		throw exception();
	}
	return this->bag.elems[this->currentIndex];
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool SortedBagIterator::valid()
{
	return this->currentIndex < this->bag.currentSize;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

void SortedBagIterator::next()
{
	if (!this->valid())
	{
		throw exception();
	}

	this->currentIndex++;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

void SortedBagIterator::first()
{
	this->currentIndex = 0;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
