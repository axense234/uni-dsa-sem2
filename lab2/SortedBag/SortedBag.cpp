#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r)
{
	this->maxSize = 10;
	this->currentSize = 0;
	this->elems = new TComp[maxSize];
	this->relation = r;
}

SortedBag::SortedBag(const SortedBag &other)
{
	this->maxSize = other.maxSize;
	this->currentSize = other.currentSize;
	this->relation = other.relation;

	this->elems = new TComp[maxSize];
	for (int i = 0; i < currentSize; ++i)
	{
		this->elems[i] = other.elems[i];
	}
}

SortedBag &SortedBag::operator=(const SortedBag &other)
{
	delete[] this->elems;

	this->maxSize = other.maxSize;
	this->currentSize = other.currentSize;
	this->relation = other.relation;

	this->elems = new TComp[maxSize];
	for (int i = 0; i < currentSize; ++i)
	{
		this->elems[i] = other.elems[i];
	}
	return *this;
}

void SortedBag::resize()
{
	int newCapacity = this->maxSize * 2;
	TComp *newElems = new TComp[newCapacity];

	for (int i = 0; i < this->currentSize; ++i)
	{
		newElems[i] = this->elems[i];
	}

	delete[] this->elems;
	this->elems = newElems;
	this->maxSize = newCapacity;
}

void SortedBag::add(TComp e)
{
	if (this->currentSize == maxSize)
	{
		this->resize();
	}

	int addIndex = -1;

	for (int i = 0; i < this->currentSize; ++i)
	{
		if (!this->relation(this->elems[i], e))
		{
			addIndex = i;
			break;
		}
	}

	if (addIndex == -1)
	{
		this->elems[this->currentSize++] = e;
		return;
	}

	for (int i = this->currentSize; i > addIndex; --i)
	{
		this->elems[i] = this->elems[i - 1];
	}

	this->elems[addIndex] = e;
	this->currentSize++;
}

bool SortedBag::remove(TComp e)
{
	int left = 0, right = this->currentSize - 1, removeIndex = -1;

	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (this->elems[middle] == e)
		{
			removeIndex = middle;

			while (removeIndex > 0 && this->elems[removeIndex - 1] == e)
			{
				removeIndex--;
			}

			break;
		}

		if (this->relation(this->elems[middle], e))
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}

	if (removeIndex == -1)
	{
		return false;
	}

	for (int i = removeIndex; i < this->currentSize - 1; ++i)
	{
		this->elems[i] = this->elems[i + 1];
	}

	this->currentSize--;
	return true;
}

bool SortedBag::search(TComp elem) const
{
	int left = 0, right = this->currentSize - 1;

	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (this->elems[middle] == elem)
		{
			return true;
		}

		if (this->relation(this->elems[middle], elem))
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}

	return false;
}

int SortedBag::nrOccurrences(TComp elem) const
{
	int left = 0, right = this->currentSize - 1, firstIndex = -1;

	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (this->elems[middle] == elem)
		{
			firstIndex = middle;
			right = middle - 1;
		}
		else if (this->relation(this->elems[middle], elem))
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}

	if (firstIndex == -1)
	{
		return 0;
	}

	int count = 0;
	while (firstIndex + count < this->currentSize &&
		   this->elems[firstIndex + count] == elem)
	{
		count++;
	}

	return count;
}

int SortedBag::size() const
{
	return this->currentSize;
}

bool SortedBag::isEmpty() const
{
	return this->currentSize == 0;
}

SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}

SortedBag::~SortedBag()
{
	delete[] this->elems;
}
