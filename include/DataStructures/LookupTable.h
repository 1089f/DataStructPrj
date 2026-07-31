#pragma once
// Owner: Member 1 (Data Structures)
// Direct patient ID -> Patient* lookup.
// Sizing decision (agreed): FileManager pre-scans the input file for the max
// patient ID before this table is constructed, so it can be sized exactly
// (capacity = maxID + 1) instead of guessing or using a hash table.
// TODO: implement constructor(int capacity), set(id, ptr), get(id), remove(id).

template <typename T>
class LookupTable {
public:
    explicit LookupTable(int capacity) {
        // TODO: allocate array of size capacity
    }
    ~LookupTable() {}

    // TODO: void set(int id, T value);
    // TODO: T get(int id) const;
    // TODO: void remove(int id);
};
