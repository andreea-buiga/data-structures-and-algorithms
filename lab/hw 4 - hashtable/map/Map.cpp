#include "Map.h"
#include "MapIterator.h"

Map::Map() {
    /**
     * complexity: BC = WC = TC = Θ(n), n - hash_capacity
     * constructor of the map
     */
	this->hash_length = 0;
	this->hash_capacity = 300;
	this->hash_table = new Node*[this->hash_capacity];
	int i;
	for(i = 0; i < this->hash_capacity; i++)
	    this->hash_table[i] = nullptr;
}

Map::~Map() {
    /**
     * complexity: BC = WC = TC = Θ(n * m), n - hash_capacity, m - no. of keys for a given position
     * destructor of the map
     */
	int i;
	for(i = 0; i < this->hash_capacity; i++) {
	    Node* current_node;
	    while(this->hash_table[i] != nullptr) {
	        current_node = this->hash_table[i]->next;
	        delete this->hash_table[i];
            this->hash_table[i] = current_node;
	    }
	}
	delete[] this->hash_table;
}

TValue Map::add(TKey c, TValue v){
    /**
     * complexity:
     * BC = Θ(1)
     * • the key to be added is hashed first at the given position of the hashtable
     * WC = Θ(n), n - hash_capacity
     * • we will need to search all the hashtable in order to check if it already exists
     *   (to update it's value) or it is hashed last at the given position and all keys are hashed on that position
     * TC = O(n)
     * function that adds a new element pair <TKey c, TValue v> to the map
     */
    /*if(this->hash_length == this->hash_capacity)
        this->rehash();*/
    /// getting the position of the key
    int position = this->hash_function(c);
    if(this->hash_table[position] == nullptr) {
        /// create a new node to store the data
        Node* new_node = new Node;
        new_node->elem.first = c;
        new_node->elem.second = v;
        this->hash_table[position] = new_node;
        this->hash_length = this->hash_length + 1;
        return NULL_TVALUE;
    }
    else {
        Node* current_node = this->hash_table[position];
        while(current_node != nullptr && current_node->elem.first != c)
            current_node = current_node->next;
        /// the key was found, update its value
        if(current_node != nullptr) {
            int old_value = current_node->elem.second;
            current_node->elem.second = v;
            return old_value;
        }
        else {
            /// the key was not found
            /// create a new node to store the data
            Node* new_node = new Node;
            new_node->elem.first = c;
            new_node->elem.second = v;
            Node* next = this->hash_table[position]->next;
            this->hash_table[position]->next = new_node;
            new_node->next = next;
            this->hash_length = this->hash_length + 1;
        }
    }
    if ((double)this->hash_length / (double)this->hash_capacity >= 0.7)
        this->rehash();
    return NULL_TVALUE;
}

TValue Map::search(TKey c) const{
    /**
     * complexity:
     * BC = Θ(1)
     * • the key to be searched is hashed first at the given position of the hashtable
     * WC = Θ(n), n - hash_capacity
     * • when the key searched will be hashed last at the given position in the hashtable and all keys are hashed on that position
     * TC = O(n)
     * function that searches a key in the map
     */
    /// getting the position of the key
	int position = this->hash_function(c);
	/// current_node points to the first node in the hashtable
    Node* current_node = this->hash_table[position];
    while(current_node != nullptr && current_node->elem.first != c)
        current_node = current_node->next;
    if(current_node != nullptr)
        return current_node->elem.second;
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
    /**
     * complexity:
     * BC = Θ(1)
     * • the key to be removed is hashed first at the given position of the hashtable
     * WC = Θ(n), n - hash_capacity
     * • when the key to be removed will be hashed last at the given position in the hashtable and all keys are hashed on that position
     * TC = O(n)
     * function that removes a key from the map
     */
    /// getting the position of the key
    int position = this->hash_function(c);
    if(this->hash_table[position] == nullptr)
        return NULL_TVALUE;
    Node *current_node = this->hash_table[position], *previous_node = nullptr;
    while(current_node != nullptr && current_node->elem.first != c) {
        previous_node = current_node;
        current_node = current_node->next;
    }
    TValue val = 0;
    /// the key was not found
    if(current_node == nullptr) {
        return NULL_TVALUE;
    }
    else {
        /// the key was found at the first node
        if(previous_node == nullptr)
            this->hash_table[position] = current_node->next;
        else {
            /// the key was found somewhere else
            previous_node->next = current_node->next;
        }
        /// remember the value of the key before deleting the pair
        val = current_node->elem.second;
        delete current_node;
    }
    this->hash_length = this->hash_length - 1;
    return val;
}

int Map::size() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that returns the length of the map
     */
	return this->hash_length;
}

bool Map::isEmpty() const{
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that verifies if the map is empty
     */
	if(this->hash_length == 0)
	    return true;
    return false;
}

MapIterator Map::iterator() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that computes the iterator of the map
     */
	return MapIterator(*this);
}

int Map::hash_function(TKey key) const{
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that computes the hash function using modulo hash_capacity
     */
    return abs(key) % this->hash_capacity;
}

void Map::rehash() {
    /**
     * complexity: BC = WC = TC = Θ(n), n - hash_capacity
     * function that expands the map by doubling it
     */
    Node** new_hash_table = new Node*[this->hash_capacity * 2];
    int i;
    for(i = 0; i < this->hash_capacity * 2; i++)
        new_hash_table[i] = nullptr;
    for(i = 0; i < this->hash_capacity; i++) {
        Node* current_original = this->hash_table[i], *previous_original = nullptr;
        while(current_original != nullptr) {
            previous_original = current_original->next;
            int position = this->hash_function(current_original->elem.first);
            if(new_hash_table[position] == nullptr) {
                new_hash_table[position] = current_original;
                new_hash_table[position]->next = nullptr;
            }
            else {
                Node *next = new_hash_table[position]->next;
                new_hash_table[position]->next = current_original;
                current_original->next = next;
            }
            current_original = previous_original;
        }
    }
    delete[] this->hash_table;
    this->hash_table = new_hash_table;
    this->hash_capacity = this->hash_capacity * 2;
}

vector<TKey> Map::keySet() const {
    /**
     * complexity:
     * BC = Θ(m)
     * WC = Θ(m + n) when all the elements are hashed on the same position
     * TC = O(n + m)
     */
    vector<TKey> all_keys;
    MapIterator map_it = this->iterator();
    while(map_it.valid()) {
        all_keys.push_back(map_it.getCurrent().first);
        map_it.next();
    }
    return all_keys;
}

