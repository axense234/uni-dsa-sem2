#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

MapIterator::MapIterator(const Map &d) : map(d)
{
	this->current = this->map.head;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

void MapIterator::first()
{
	this->current = this->map.head;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

void MapIterator::next()
{
	if (this->valid())
	{
		this->current = this->current->next;
	}
	else
	{
		// if iterator is not valid, next() should throw an exception
		throw exception();
	}
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

TElem MapIterator::getCurrent()
{
	if (this->valid())
	{
		return std::make_pair(this->current->key, this->current->value);
	}
	else
	{
		throw exception();
	}
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool MapIterator::valid() const
{
	return this->current != nullptr;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)