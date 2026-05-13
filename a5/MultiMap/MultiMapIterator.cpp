#include "MultiMapIterator.h"
#include "MultiMap.h"

#include <exception>

MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(c)
{
	this->currentBucket = 0;
	this->currentPositionInValues = 0;
	this->currentNode = nullptr;

	for (int i = 0; i < col.m; i++)
	{
		if (this->col.table[i] != nullptr)
		{
			this->currentBucket = i;
			this->currentNode = this->col.table[i];
			this->currentPositionInValues = 0;
			return;
		}
	}
}
// BC: Theta(m)
// WC: Theta(m)
// TC: Theta(m)

TElem MultiMapIterator::getCurrent() const
{
	if (!valid())
	{
		throw std::exception();
	}
	return TElem(this->currentNode->key, this->currentNode->values[this->currentPositionInValues]);
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool MultiMapIterator::valid() const
{
	return this->currentNode != nullptr && this->currentPositionInValues < this->currentNode->valuesCount;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

void MultiMapIterator::next()
{
	if (!valid())
	{
		throw std::exception();
	}

	this->currentPositionInValues++;

	if (this->currentPositionInValues >= this->currentNode->valuesCount)
	{
		this->currentNode = currentNode->next;
		this->currentPositionInValues = 0;

		while (this->currentNode == nullptr)
		{
			this->currentBucket++;
			if (this->currentBucket >= col.m)
			{
				this->currentNode = nullptr;
				return;
			}
			this->currentNode = this->col.table[currentBucket];
		}
	}
}
// BC: Theta(1)
// WC: Theta(m)
// TC: O(m)

void MultiMapIterator::first()
{
	this->currentBucket = 0;
	this->currentPositionInValues = 0;
	this->currentNode = nullptr;

	for (int i = 0; i < col.m; i++)
	{
		if (this->col.table[i] != nullptr)
		{
			this->currentBucket = i;
			this->currentNode = this->col.table[i];
			this->currentPositionInValues = 0;
			return;
		}
	}
}
// BC: Theta(m)
// WC: Theta(m)
// TC: Theta(m)
