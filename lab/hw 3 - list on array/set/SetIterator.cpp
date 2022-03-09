#include "SetIterator.h"
#include "Set.h"
#include <exception>

using namespace std;

SetIterator::SetIterator(const Set& m) : set(m) {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that initialises the iterator
     */
	this->current = m.head;
}

void SetIterator::first() {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that initialises the iterator
     */
    this->current = set.head;
}

void SetIterator::next() {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that initialises the iterator
     */
    if(!valid())
        throw exception();
	this->current = this->set.next[current];
}

TElem SetIterator::getCurrent() {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that initialises the iterator
     */
    if(!valid())
        throw exception();
    return this->set.elements[this->current];
}

bool SetIterator::valid() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that initialises the iterator
     */
	if(this->current != -1)
        return true;
	return false;
}



