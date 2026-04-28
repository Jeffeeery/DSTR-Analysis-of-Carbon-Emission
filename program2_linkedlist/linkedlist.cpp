#include "linkedlist.hpp"

// Constructor: initialise empty list
ResidentList::ResidentList() {
    head = nullptr;
    count = 0;
}

// Deconstructor: free up memory
ResidentList::~ResidentList() {
    clear();
}

// Insert a new node at the tail of the list
void ResidentList::insertAtTail(const Resident& r) {
    Node* newNode = new Node(r);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* curr = head;
        while (curr->next != nullptr)
            curr = curr->next;
        curr->next = newNode;
    }
    count++;
}

// Return pointer to node at given index
Node* ResidentList::getAt(int index) const {
    Node* curr = head;
    for (int i = 0; i < index; i++)
        curr = curr->next;
    return curr;
}

// Return head node
Node* ResidentList::getHead() const {
    return head;
}

// Return current number of nodes
int ResidentList::size() const {
    return count;
}

// Delete all nodes and reset list
void ResidentList::clear() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
    count = 0;
}

// Set a new head (Sorting Algorithms)
void ResidentList::setHead(Node* newHead) {
    head = newHead;
}
