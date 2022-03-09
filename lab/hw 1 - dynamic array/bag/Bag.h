#pragma once
#include <utility>
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
typedef int TValue;
typedef std::pair<TElem, TValue> ValuePair;
class BagIterator;

class Bag {
private:
    ValuePair* pair_elements;
    int max_capacity;
    int no_of_pairs;
    int current_size;

    void resize();
	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appear is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of pair_elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

    //returns the number of elements with the maximum frequency //if the Bag is empty, it returns 0
    int elementsWithMaximumFrequency() const;

	//destructor
	~Bag();
};