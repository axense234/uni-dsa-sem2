#include "SetIterator.h"
#include "Set.h"

#include <exception>

SetIterator::SetIterator(const Set &m) : set(m)
{
	this->current = this->set.head;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

void SetIterator::first()
{
	this->current = this->set.head;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

void SetIterator::next()
{
	if (this->valid())
	{
		this->current = this->set.nodes[this->current].next;
	}
	else
	{
		throw std::exception();
	}
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

TElem SetIterator::getCurrent()
{
	if (this->valid())
	{
		return this->set.nodes[this->current].info;
	}
	else
	{
		throw std::exception();
	}
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool SetIterator::valid() const
{
	return this->current != -1;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
