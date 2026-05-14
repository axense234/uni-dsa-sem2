#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap &multi;
	int currentBucket;
	int currentPositionInValues;
	KeyNode *currentNode;

	// DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap &multi);

public:
	TElem getCurrent() const;
	bool valid() const;
	void next();
	void first();
};
