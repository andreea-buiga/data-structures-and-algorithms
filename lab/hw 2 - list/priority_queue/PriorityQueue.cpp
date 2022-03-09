
#include "PriorityQueue.h"
#include <exception>
using namespace std;

PriorityQueue::PriorityQueue(Relation r) {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * :param: r - the relation between each pair when we prioritise
     */
    this->relation = r;
    this->head = nullptr;
}

void PriorityQueue::push(TElem e, TPriority p) {
    /**
     * complexity: BC: Θ(1) - if the element we want to add is on the first position or the element we want to add
     *                        has a higher priority than the head
     *             WC: Θ(n) - if the element we want to add would be on the last position
     *             TC: O(n)
     * function that pushes an element with priority to the queue
     */

    /// create new node
    Node* new_node = new Node();
    new_node->data.first = e;
    new_node->data.second = p;
    if(this->head == nullptr)
        this->head = new_node;
    else {
        /// the head of the list has a smaller priority than the new node
        /// insert new node before the head node and change head node
        if(!this->relation(this->head->data.second, p)) {
            new_node->next = this->head;
            this->head = new_node;
        }
        else {
            /// go through the list and find a position to insert a new node
            Node* start = this->head;
            while(start->next != nullptr && this->relation(start->next->data.second, p))
                start = start->next;
            /// the new node would be added at the required position
            new_node->next = start->next;
            start->next = new_node;
        }
    }
}

Element PriorityQueue::top() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that returns the element with the highest priority with respect to the order relation
     * throws exception if the queue is empty
     */
    if(isEmpty())
        throw exception();
    return this->head->data;
}

Element PriorityQueue::pop() {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that removes and returns the element with the highest priority
     * throws exception if the queue is empty
     */
    if(isEmpty())
        throw exception();
    Node* temp_node = this->head;
    this->head = this->head->next;
    return temp_node->data;
}

bool PriorityQueue::isEmpty() const {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that checks if the priority queue is empty
     */
    if(this->head == nullptr)
        return true;
	return false;
}

PriorityQueue::~PriorityQueue() {
    /**
     * complexity: BC = WC = TC = Θ(n)
     * destructor of the queue
     */
	auto head_node = this->head;
	while(head_node != nullptr) {
	    auto next = head_node->next;
	    delete head_node;
	    head_node = next;
	}
	delete head_node;
}

void PriorityQueue::merge(PriorityQueue &pq) {
    /**
     * complexity: BC: Θ(pq.size * n) - if all pq elements would have a higher priority than the head
     *             WC: Θ(pq.size * n + pq.size^2) - by pushing it into the priority queue we could compare all the elements in it
     *             TC: O(pq.size * n + pq.size^2)
     * function that adds all elements (and their priorities) from pq into the PriorityQueue
    */
    while(!pq.isEmpty()) {
        auto el = pq.pop();
        this->push(el.first, el.second);
    }
}

Node::Node() {
    /**
     * complexity: BC = WC = TC = Θ(1)
     * function that creates a new node
     */
    this->next = nullptr;
}
