// Member 1 - [BAN]
// program2_linkedlist/linkedlist.h - Singly Linked List for Resident records

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../shared/resident.h"

struct Node {
    Resident data;
    Node* next;
    Node(const Resident& r) : data(r), next(nullptr) {}
};

class ResidentList {
private:
    Node* head;
    int count;

public:
    ResidentList();
    ~ResidentList();

    // Insert at tail
    void insertAtTail(const Resident& r);

    // Get pointer to node at index (0-based)
    Node* getAt(int index) const;

    // Get head node
    Node* getHead() const;

    // Current number of nodes
    int size() const;

    // Remove all nodes
    void clear();

    // Set a new head (used by sorting algorithms)
    void setHead(Node* newHead);
};

#endif // LINKEDLIST_H
