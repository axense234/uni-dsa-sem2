#include "SetIterator.h"
#include "Set.h"

#include <exception>

SetIterator::SetIterator(const Set &m) : set(m)
{
	this->current = this->set.head;
}

void SetIterator::first()
{
	this->current = this->set.head;
}

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

bool SetIterator::valid() const
{
	return this->current != -1;
}
