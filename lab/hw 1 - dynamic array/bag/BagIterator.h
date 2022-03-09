#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
private:
	const Bag& bag;
	int current_position;

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
