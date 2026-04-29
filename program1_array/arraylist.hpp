// Custom dynamic array for Resident records

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "../shared/resident.hpp"

class ResidentArray {
private:
    Resident* data;
    int capacity;
    int count;

public:
    ResidentArray(int cap = 500);
    ~ResidentArray();

    // Add a resident to the end
    void add(const Resident& r);

    // Get resident at index (no bounds-checked copy)
    Resident& get(int index);
    const Resident& get(int index) const;

    // Swap two elements by index
    void swap(int i, int j);

    // Current number of elements
    int size() const;

    // Reset count to 0 (does not free memory)
    void clear();

    // Get pointer to internal data array
    Resident* getData();
};

#endif // ARRAYLIST_HPP
