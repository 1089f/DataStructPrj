#pragma once
#include <iostream>

template <typename T>
class LookupTable {
private:
    T* table;
    int capacity;
    int count;

    void resize(int newCapacity) {
        T* newTable = new T[newCapacity];
        for (int i = 0; i < newCapacity; i++) {
            newTable[i] = nullptr;
        }
        for (int i = 0; i < capacity; i++) {
            newTable[i] = table[i];
        }
        delete[] table;
        table = newTable;
        capacity = newCapacity;
    }

public:
    LookupTable(int initialCap = 100) : capacity(initialCap), count(0) {
        table = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~LookupTable() {
        delete[] table;
    }

    // adding element by ID  O(1)
    void insert(int id, T ptr) {
        if (id < 0) return;
        if (id >= capacity) {
            resize(id * 2 + 1);
        }
        if (table[id] == nullptr) {
            count++;
        }
        table[id] = ptr;
    }

    // searching for an element by ID  O(1)
    T get(int id) const {
        if (id < 0 || id >= capacity) return nullptr;
        return table[id];
    }

    // removing an element by ID     O(1)
    bool remove(int id) {
        if (id < 0 || id >= capacity || table[id] == nullptr) return false;
        table[id] = nullptr;
        count--;
        return true;
    }

    bool contains(int id) const {
        return get(id) != nullptr;
    }

    int size() const {
        return count;
    }

    void clear() {
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
        count = 0;
    }

    // Non-destructive traversal hook (read-only iteration over populated slots)
    template <typename Func>
    void traverse(Func visit) const {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                visit(table[i]);
            }
        }
    }

    // Non-destructive print hook
    void print(std::ostream& os = std::cout, void (*printItem)(const T&) = nullptr) const {
        bool first = true;
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                if (!first) os << ", ";
                if (printItem != nullptr) {
                    printItem(table[i]);
                } else {
                    os << table[i];
                }
                first = false;
            }
        }
    }
};