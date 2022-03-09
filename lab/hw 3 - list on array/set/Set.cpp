#include "Set.h"
#include "SetIterator.h"

Set::Set() {
    /**
     * complexity: BC = WC = TC = Θ(n), n - capacity
     * function that initialises a set
     */
    this->max_capacity = 60002;
    this->first_empty = 0;
    this->next = new int[this->max_capacity];
    this->head = -1;
    int i;
    for(i = 0; i < this->max_capacity - 1; i++)
        this->next[i] = i + 1;
    this->next[this->max_capacity - 1] = -1;
    this->elements = new TElem[this->max_capacity];
    this->current_size = 0;
}

bool Set::add(TElem elem) {
    /**
     * complexity: BC: Θ(1) - if the element we want to add is on the first position
     *             WC: Θ(n) - if the element we want to add doesn't exist,
     *                        but we have to check all the elements to be unique, or it already exists, but we still check
     *             TC: O(n)
     * function that adds an element to the set
     */
    bool found = false;
    /// we need a current element used for traversal, which is initialized to the index of the head of the list
    int current = this->head;
    /// we check if the element already exists in the set
    while (current != -1 && this->elements[current] != elem)
        current = this->next[current];
    /// if we got to the end, that means we didn't find it, so we can add it
    if(current == -1) {
        found = true;
        int new_position = this->first_empty;
        this->elements[new_position] = elem;
        this->first_empty = this->next[first_empty];
        this->next[new_position] = this->head;
        this->head = new_position;
        this->current_size = this->current_size + 1;
    }
    return found;
}

bool Set::remove(TElem elem) {
    /**
     * complexity: BC: Θ(1) - if the element we want to remove is on the first position
     *             WC: Θ(n) - if the element we want to remove doesn't exist or it is the last element
     *             TC: O(n)
     * function that removes an element from the set
     */
    /// we need a current element used for traversal, which is initialized to the index of the head of the list
    /// we need a previous node so that when we delete the element, the next before the deleted element would be updated
    int previous_node = -1, current_node = this->head;
    while(current_node != -1 && this->elements[current_node] != elem) {
        previous_node = current_node;
        current_node = this->next[current_node];
    }
    if(current_node == -1)
        return false;
    else {
        if(current_node == this->head)
            this->head = this->next[current_node];
        else
            this->next[previous_node] = this->next[current_node];
        this->next[current_node] = this->first_empty;
        this->first_empty = current_node;
        this->current_size = this->current_size - 1;
    }
    return true;
}

bool Set::search(TElem elem) const {
    /**
     * complexity: BC: Θ(1) - if the element we want to search is on the first position
     *             WC: Θ(n) - if the element we want to search doesn't exist or it is the last element
     *             TC: O(n)
     * function that searches an element in the set
     */
    bool found = false;
    /// we need a current element used for traversal, which is initialized to the index of the head of the list
	int current = this->head;
    while (current != -1 && this->elements[current] != elem)
        current = this->next[current];
    /// if we didn't reach the end, that means the element was found
    if(current != - 1)
        found = true;
	return found;
}

int Set::size() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that returns the size of the set
     */
    return this->current_size;
}

bool Set::isEmpty() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that checks if the set is empty
     */
	if(this->head == -1)
        return true;
	return false;
}

Set::~Set() {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that destroys the elements of the set
     */
    delete[] this->next;
    delete[] this->elements;
}

SetIterator Set::iterator() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that returns the iterator of the set
     */
	return SetIterator(*this);
}

int Set::getRange() const {
    /**
     * complexity: BC = WC = TC = Θ(n) - because we will always need to check the whole set to get the maximum and minimum
     * function that returns the range between the maximum and the minimum element
     */
    if(isEmpty())
        return -1;
    int minimum = this->elements[head], maximum = this->elements[head], current = this->head;
    while(current != -1) {
        if(this->elements[current] > maximum)
            maximum = this->elements[current];
        if(this->elements[current] < minimum)
            minimum = this->elements[current];
        current = this->next[current];
    }
    return maximum - minimum;
}
