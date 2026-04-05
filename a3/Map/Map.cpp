#include "Map.h"
#include "MapIterator.h"

Map::Map()
{
	this->currentSize = 0;
	this->head = nullptr;
	this->tail = nullptr;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

Map::~Map()
{
	TDLLElem *current = this->head;
	while (current != nullptr)
	{
		TDLLElem *nextElem = current->next;
		delete current;
		current = nextElem;
	}

	this->head = nullptr;
	this->tail = nullptr;
}
// BC: Theta(currentSize)
// WC: Theta(currentSize)
// TC: Theta(currentSize)

TValue Map::add(TKey c, TValue v)
{
	TDLLElem *current = this->head;

	// search for existing key
	while (current != nullptr)
	{
		// found elem so we update value and return old value
		if (current->key == c)
		{
			TValue old = current->value;
			current->value = v;
			return old;
		}
		current = current->next;
	}

	// add a new pair at the end or beginning if empty
	TDLLElem *newElem = new TDLLElem{c, v, this->tail, nullptr};

	if (this->head == nullptr)
	{
		// list was empty
		this->head = newElem;
		this->tail = newElem;
	}
	else
	{
		// add to the end
		this->tail->next = newElem;
		this->tail = newElem;
	}

	this->currentSize++;
	return NULL_TVALUE;
}
// BC: Theta(1) -> elem is head
// WC: Theta(currentSize) -> elem is tail
// TC: O(currentSize)

TValue Map::search(TKey c) const
{
	TDLLElem *current = this->head;

	while (current != nullptr)
	{
		if (current->key == c)
		{
			return current->value;
		}
		current = current->next;
	}

	return NULL_TVALUE;
}
// BC: Theta(1) -> elem is head
// WC: Theta(currentSize) -> elem is tail
// TC: O(currentSize)

TValue Map::remove(TKey c)
{
	TDLLElem *current = this->head;

	// search for the key
	while (current != nullptr)
	{
		if (current->key == c)
		{
			TValue oldValue = current->value;

			// fix the links
			if (current->prev != nullptr)
			{
				current->prev->next = current->next;
			}
			else
			{
				// removing head
				this->head = current->next;
			}

			if (current->next != nullptr)
			{
				current->next->prev = current->prev;
			}
			else
			{
				// removing tail
				this->tail = current->prev;
			}

			delete current;
			this->currentSize--;
			return oldValue;
		}
		current = current->next;
	}

	return NULL_TVALUE;
}
// BC: Theta(1) -> if targeted elem is head
// WC: Theta(currentSize) -> if targeted elem isnt in the dll
// TC: O(currentSize)

int Map::size() const
{
	return this->currentSize;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool Map::isEmpty() const
{
	return this->currentSize == 0;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

MapIterator Map::iterator() const
{
	return MapIterator(*this);
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)