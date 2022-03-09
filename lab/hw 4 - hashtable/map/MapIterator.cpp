#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d) {
    /**
     * complexity:
     * BC = Θ(1)
     * • when there exists a key hashed in the first position
     * WC = Θ(n), n - hash_capacity
     * • when there exists a key hashed only at the last position
     * TC = O(n)
     * constructor for the iterator
     */
	this->current_position = 0;
	while(this->current_position < d.hash_capacity && d.hash_table[this->current_position] == nullptr)
        this->current_position = this->current_position + 1;
	if(this->current_position == d.hash_capacity)
        this->current_node = nullptr;
	else
        this->current_node = d.hash_table[this->current_position];
}

void MapIterator::first() {
    /**
     * complexity:
     * BC = Θ(1)
     * • when there exists a key hashed in the first position
     * WC = Θ(n), n - hash_capacity
     * • when there exists a key hashed only at the last position
     * TC = O(n)
     * function that gets to the first element
     */
    this->current_position = 0;
    while(this->current_position < this->map.hash_capacity && this->map.hash_table[current_position] == nullptr)
        this->current_position = this->current_position + 1;
    if(this->current_position == this->map.hash_capacity)
        this->current_node = nullptr;
    else
        this->current_node = this->map.hash_table[current_position];
}

void MapIterator::next() {
    /**
     * complexity:
     * BC = Θ(1)
     * • when there is another key hashed to the same position after the current one
     *   or when the next key is hashed on the next position in the hashtable
     * WC = Θ(n), n - hash_capacity
     * • when there exists a key hashed in the last position
     * TC = O(n)
     * function that goes to the last element
     */
	if(!this->valid())
	    throw exception();
	if(this->current_node->next != nullptr) {
	    this->current_node = this->current_node->next;
	}
	else {
	    this->current_position = this->current_position + 1;
	    while(this->current_position < this->map.hash_capacity && this->map.hash_table[this->current_position] == nullptr)
            this->current_position = this->current_position + 1;
	    if(this->current_position == this->map.hash_capacity)
	        this->current_node = nullptr;
	    else {
	        this->current_node = this->map.hash_table[this->current_position];
	    }
	}
}

TElem MapIterator::getCurrent(){
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function for getting the current element in the hashtable
     */
    if(!this->valid())
        throw exception();
	return this->current_node->elem;
}

bool MapIterator::valid() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that verifies if we are within the correct limit
     */
	if(this->current_position == this->map.hash_capacity)
        return false;
	return true;
}
