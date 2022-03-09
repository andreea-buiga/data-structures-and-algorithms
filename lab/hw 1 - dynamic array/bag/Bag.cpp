#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * no_of pairs - the number of <TElem, TValue> pairs in the bag
     * current_size - the actual size of the bag (the sum of frequencies)
     * max_capacity - the maximum number of elements in the bag
     * pair_elements - the array in which the pairs are stored
    */
    this->no_of_pairs = 0;
    this->current_size = 0;
    this->max_capacity = 50;
    this->pair_elements = new ValuePair[this->max_capacity];
}

void Bag::resize() {
    /**
     * complexity: O(no_of_pairs)
     * worst case: we could have some excess space O(2no_of_pairs)
     *             this happens just after a growth of the dynamic array
     * 1 + 2 + 4 + ... + n/4 + n/2 + n ~ O(n)
     *
     * function that resizes the bag (when the number of pairs = maximum capacity)
     * • doubles the maximum capacity
     * • moving the full bag to another bag of elements
     * • deleting the previous bag
     * • the current bag will receive the elements from the new bag
     */
    this->max_capacity = this->max_capacity * 2;
    ValuePair *new_elements = new ValuePair[this->max_capacity];
    int i;
    for(i = 0; i < this->no_of_pairs; i++)
        new_elements[i] = this->pair_elements[i];
    delete[] this->pair_elements;
    this->pair_elements = new_elements;
}

void Bag::add(TElem elem) {
    /**
     * complexity:
     * it can be divided in two parts: resizing (if necessary) and checking if the element is in the bag
     * to increase the frequency or simply add a new element
     *  • best case: Θ(1)
     *               when the bag will have only one pair and we would only increase the frequency
     *  • worst case: Θ(no_of_pairs)
     *               when all the pairs would have one frequency (each element is distinct)
     *               + moving the elements for resizing (which is Θ(no_of_pairs))
     *               so, together the complexity for add would be Θ(no_of_pairs)
     *  • average case: O(no_of_pairs)
     *
     *  function that adds an element to the bag
     *  • checking if the bag is full (number of pairs = maximum capacity) -> resize
     *  • we will look for the element in the pairs from the beginning
     *      • if we found it
     *              • we increase the overall size of the bag
     *              • increase the frequency for the element
     *      • otherwise, it was not found, that means it's a new element
     *              • we increase the overall size of the bag
     *              • we increase the number of pairs
     *              • set the frequency of the element to 1
     *              • add the element to the index
     */
    if(this->no_of_pairs == this->max_capacity)
        //throw exception();
        resize();
    int index = 0;
    bool found = false;
    while(index < this->no_of_pairs && !(found)) {
        if(this->pair_elements[index].first == elem) {
            this->current_size = this->current_size + 1;
            this->pair_elements[index].second = this->pair_elements[index].second + 1;
            found = true;
        }
        index = index + 1;
    }
    if(!found) {
        this->no_of_pairs = this->no_of_pairs + 1;
        this->current_size = this->current_size + 1;
        this->pair_elements[index].first = elem;
        this->pair_elements[index].second = 1;
    }
}

bool Bag::remove(TElem elem) {
    /**
     * complexity:
     *  • best case: Θ(1)
     *               when the bag will have only one pair and we would only decrease the frequency
     *  • worst case: Θ(no_of_pairs)
     *               when the element we are looking for is at the end
     *               + moving the last element in the place of the current element (which is Θ(1))
     *               so, together the complexity for add would be Θ(n)
     *  • average case: O(no_of_pairs)
     *
     *  function that removes the first occurrence of the element
     *  • we will look for the element in the pairs from the beginning
     *      • if we found it
     *              • we decrease the overall size of the bag
     *              • decrease the frequency for the element
     *              • if the frequency of the element will be 0, we move the last element in place of the current element
     *  • return true if we found the element and performed the operation
     *           false otherwise
     */
	int index = 0;
	bool found = false;
	while(index < this->no_of_pairs && !(found)) {
        if(this->pair_elements[index].first == elem) {
            this->pair_elements[index].second = this->pair_elements[index].second - 1;
            this->current_size = this->current_size - 1;
            found = true;
            if(this->pair_elements[index].second == 0) {
                this->pair_elements[index] = this->pair_elements[this->no_of_pairs - 1];
                this->no_of_pairs = this->no_of_pairs - 1;
            }
        }
        index = index + 1;
    }
	return found;
}

bool Bag::search(TElem elem) const {
    /**
     * complexity:
     *  • best case: Θ(1)
     *               when the bag will have only one pair
     *  • worst case: Θ(no_of_pairs)
     *               when the element we are looking for is at the end
     *  • average case: O(no_of_pairs)
     *
     *  function that searches an element in the bag
     *  • we will look for the element in the pairs from the beginning
     *  • if we found it return true
     *  • return false otherwise
     */
    int index = 0;
    while(index < this->no_of_pairs) {
        if(this->pair_elements[index].first == elem)
            return true;
        index = index + 1;
    }
	return false; 
}

int Bag::nrOccurrences(TElem elem) const {
    /**
     * complexity:
     *  • best case: Θ(1)
     *               when the bag will have only one pair and we would only decrease the frequency
     *  • worst case: Θ(no_of_pairs)
     *               when the element we are looking for is at the end
     *  • average case: O(no_of_pairs)
     *
     *  function that returns the number of occurrences of the element
     *  • we will look for the element in the pairs from the beginning
     *  • if we found it return the number of occurrences
     *  • return 0 otherwise
     */
    int index = 0;
    while(index < this->no_of_pairs) {
        if (this->pair_elements[index].first == elem)
            return this->pair_elements[index].second;
        index = index + 1;
    }
	return 0; 
}


int Bag::size() const {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * function that return the bag's actual size (size = the sum of the frequencies)
    */
	return this->current_size;
}

bool Bag::isEmpty() const {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * function that checks if the bag is empty (if we don't have any pairs)
     */
	if(this->no_of_pairs == 0)
        return true;
    return false;
}

BagIterator Bag::iterator() const {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * function that return an iterator of the bag
     */
	return BagIterator(*this);
}

Bag::~Bag() {
    /**
     * complexity: Θ(1) (bc = wc = av)
     *
     * destructor for the bag
     * deletes the pairs
    */
	delete[] this->pair_elements;
}

int Bag::elementsWithMaximumFrequency() const {
    /**
     * complexity:
     * • best case: Θ(1)
     *              when the list is empty
     * • worst case: Θ(no_of_pairs)
     *               when the element with the maximum frequency is at the end
     * • average case: O(no_of_pairs)
     *
     * function that computes the number of element with the maximum frequency
     * • if the bag is empty, return 0
     * • we go through the bag and find the maximum frequency
     */
    if(isEmpty())
        return 0;
    int index = 0, maximum_freq = -1, how_many_max_freq = 0;
    while(index < this->no_of_pairs) {
        if(this->pair_elements[index].second > maximum_freq)
            maximum_freq = this->pair_elements[index].second;
        index = index + 1;
    }
    index = 0;
    while(index < this->no_of_pairs) {
        if(this->pair_elements[index].second == maximum_freq)
            how_many_max_freq = how_many_max_freq + 1;
        index = index + 1;
    }
    return how_many_max_freq;
}


