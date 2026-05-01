#include "Set.h"
#include "SetIterator.h"

Set::Set()
{
	this->head = -1;
	this->tail = -1;
	this->firstEmpty = 0;
	this->nbOfNodes = 0;

	for (int i = 0; i < this->CAPACITY - 1; ++i)
	{
		nodes[i].info = NULL_TELEM;
		nodes[i].prev = i - 1;
		nodes[i].next = i + 1;
	}

	// last node
	nodes[CAPACITY - 1].info = NULL_TELEM;
	nodes[CAPACITY - 1].prev = CAPACITY - 2;
	nodes[CAPACITY - 1].next = -1;
}
// BC: Theta(CAPACITY)
// WC: Theta(CAPACITY)
// TC: Theta(CAPACITY)

bool Set::add(TElem elem)
{
	// check if elem is in set
	if (this->search(elem))
	{
		return false;
	}

	// check is there is space using firstEmpty
	if (firstEmpty == -1)
	{
		return false;
	}

	// handle firstEmpty
	int newNode = firstEmpty;
	firstEmpty = nodes[firstEmpty].next;

	// create new node that will be the new tail
	nodes[newNode].info = elem;
	nodes[newNode].next = -1;
	nodes[newNode].prev = tail;

	// handle links
	if (head == -1)
	{
		// first elem
		head = newNode;
		tail = newNode;
	}
	else
	{
		// add it to the end
		nodes[tail].next = newNode;
		tail = newNode;
	}

	nbOfNodes++;
	return true;
}
// BC: Theta(1) -> first elem is the given elem
// WC: Theta(nbOfNodes) -> last elem is the given elem or the elem doesn't exist in the list
// TC: O(nbOfNodes)

bool Set::remove(TElem elem)
{
	int current = this->head;
	while (current != -1)
	{
		if (nodes[current].info == elem)
		{
			// handle prev node of current
			if (nodes[current].prev != -1)
			{
				nodes[nodes[current].prev].next = nodes[current].next;
			}
			else
			{
				// head removal case
				this->head = nodes[current].next;
			}

			// handle next node of current
			if (nodes[current].next != -1)
			{
				nodes[nodes[current].next].prev = nodes[current].prev;
			}
			else
			{
				// tail removal case
				this->tail = nodes[current].prev;
			}

			// clear out the node
			nodes[current].next = this->firstEmpty;
			nodes[current].prev = -1;
			nodes[current].info = NULL_TELEM;
			this->firstEmpty = current;

			nbOfNodes--;
			return true;
		}
		current = nodes[current].next;
	}
	return false;
}
// BC: Theta(1) -> first elem is the given elem
// WC: Theta(nbOfNodes) -> last elem is the given elem or the elem doesn't exist in the list
// TC: O(nbOfNodes)

bool Set::search(TElem elem) const
{
	int current = this->head;
	while (current != -1)
	{
		if (nodes[current].info == elem)
		{
			return true;
		}
		current = nodes[current].next;
	}

	return false;
}
// BC: Theta(1) -> first elem is the given elem
// WC: Theta(nbOfNodes) -> last elem is the given elem or the elem doesn't exist in the list
// TC: O(nbOfNodes)

int Set::size() const
{
	return this->nbOfNodes;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

bool Set::isEmpty() const
{
	return nbOfNodes == 0;
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

Set::~Set() {}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)

SetIterator Set::iterator() const
{
	return SetIterator(*this);
}
// BC: Theta(1)
// WC: Theta(1)
// TC: Theta(1)
