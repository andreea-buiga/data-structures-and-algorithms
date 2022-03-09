#pragma once
#include <utility>
#include <cmath>
#include <vector>
using namespace std;
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)
class MapIterator;

class Node {
public:
    TElem elem;
    Node* next;
    Node() {
        this->next = nullptr;
    }
};

class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

private:
    int hash_length;
    int hash_capacity;
	Node** hash_table;
	int hash_function(TKey key) const;
	void rehash();
public:

	// implicit constructor
	Map();

	// adds a pair (key, value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

    //returns a vector with all the keys from the map
    vector<TKey> keySet() const;

	// destructor
	~Map();

};



