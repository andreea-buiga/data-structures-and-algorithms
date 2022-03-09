#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c) {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * current position - represent the current element we'll iterate in the bag
    */
    this->current_position = 0;
}

void BagIterator::first() {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * function that resets the current position to the beginning
    */
    this->current_position = 0;
}

void BagIterator::next() {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * function that increases the current position so that we'll go to the next position
     * • checking if the current position exceeds the size of the bag to throw an exception
    */
	if(this->current_position >= this->bag.size())
	    throw exception();
	this->current_position = this->current_position + 1;
}

bool BagIterator::valid() const {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * function that checks that we stay withing the range of 0 and the size of the bag
     * • return false if the current position exceeds the size of the bag
     * • return true otherwise
    */
    if(this->current_position < this->bag.size())
        return true;
	return false;
}

TElem BagIterator::getCurrent() const {
    /**
     * complexity:
     * • best case: Θ(1)
     *              when the current element is on the first position
     * • worst case: O(n)
     * • average case: O(n)
     *
     * function that gets the current element in the bag
     * • checking if the current position exceeds the size of the bag to throw an exception
     * • although the elements in the bag are pairs, the element on the position 1, doesn't actually
     *   mean the second pair in the bag (starting from 0)
     * • so then we go the number of times the frequency of the element to get the current element in the list
     * • then return the element on that index
     */
    if(this->current_position >= this->bag.size())
        throw exception();
    int index = 0, index_with_freq = 0;
    while(index_with_freq <= this->current_position) {
        index_with_freq += this->bag.pair_elements[index].second;
        index = index + 1;
    }
    index -= 1;
    return this->bag.pair_elements[index].first;
}
