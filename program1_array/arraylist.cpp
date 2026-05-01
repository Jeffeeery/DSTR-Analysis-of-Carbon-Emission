#include "arraylist.hpp"

// Constructor: allocate array
ResidentArray::ResidentArray(int cap) {
    capacity = cap;
    count = 0;
    data = new Resident[capacity];
}

// Deconstructor: free up memory
ResidentArray::~ResidentArray() {
    delete[] data;
}

// Add resident to end
void ResidentArray::add(const Resident& r) {
    if (count < capacity)
        data[count++] = r;
}

// Get by index (non-const)
Resident& ResidentArray::get(int index) {
    return data[index];
}

// Get by index (const)
const Resident& ResidentArray::get(int index) const {
    return data[index];
}

// Swap two elements
void ResidentArray::swap(int i, int j) {
    Resident temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

// Return count
int ResidentArray::size() const {
    return count;
}

// Reset count
void ResidentArray::clear() {
    count = 0;
}

// Get pointer to internal data array
Resident* ResidentArray::getData() {
    return data;
}

const Resident* ResidentArray::getData() const {
    return data;
}
