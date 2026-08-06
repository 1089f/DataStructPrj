#pragma once
#include <iostream>
#include "../Entities/Patient.h"

template <typename T>
class PriorityQueue {
public:
    typedef double (*PriorityFunc)(const T&);
    typedef bool (*ComparatorFunc)(const T&, const T&);

private:
    struct HeapItem {
        T data;
        double priority;
        int heapIndex;
    };

    HeapItem* heap;
    int capacity;
    int count;

    PriorityFunc priorityFunc;
    ComparatorFunc compFunc;

    void setIndex(int pos) {
        heap[pos].heapIndex = pos;
        if (heap[pos].data != nullptr) {
            heap[pos].data->setHeapIndex(pos);
        }
    }

    void swapItems(int i, int j) {
        HeapItem temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;

        setIndex(i);
        setIndex(j);
    }

    void resize() {
        int newCap = capacity * 2;
        HeapItem* newHeap = new HeapItem[newCap];
        for (int i = 0; i < count; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
        capacity = newCap;
    }

    bool isHigherPriority(int i, int j) const {
        if (compFunc != nullptr) {
            return compFunc(heap[i].data, heap[j].data);
        }
        if (priorityFunc != nullptr) {
            return priorityFunc(heap[i].data) > priorityFunc(heap[j].data);
        }
        return heap[i].priority > heap[j].priority;
    }

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (isHigherPriority(index, parent)) {
                swapItems(index, parent);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    void siftDown(int index) {
        while (2 * index + 1 < count) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int maxIndex = index;

            if (isHigherPriority(leftChild, maxIndex)) {
                maxIndex = leftChild;
            }
            if (rightChild < count && isHigherPriority(rightChild, maxIndex)) {
                maxIndex = rightChild;
            }

            if (maxIndex != index) {
                swapItems(index, maxIndex);
                index = maxIndex;
            }
            else {
                break;
            }
        }
    }

public:
    PriorityQueue(int initialCap = 20)
        : capacity(initialCap), count(0), priorityFunc(nullptr), compFunc(nullptr) {
        heap = new HeapItem[capacity];
    }

    PriorityQueue(PriorityFunc pfunc, int initialCap = 20)
        : capacity(initialCap), count(0), priorityFunc(pfunc), compFunc(nullptr) {
        heap = new HeapItem[capacity];
    }

    PriorityQueue(ComparatorFunc comp, int initialCap = 20)
        : capacity(initialCap), count(0), priorityFunc(nullptr), compFunc(comp) {
        heap = new HeapItem[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    void setPriorityFunc(PriorityFunc pfunc) {
        priorityFunc = pfunc;
    }

    void setComparator(ComparatorFunc comp) {
        compFunc = comp;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }

    // O(log N) 
    void insert(const T& val, double priority) {
        if (count == capacity) {
            resize();
        }
        heap[count] = { val, priority, count };
        if (val != nullptr) {
            val->setHeapIndex(count);
        }
        siftUp(count);
        count++;
    }

    void insert(const T& val) {
        double prio = 0.0;
        if (priorityFunc != nullptr && val != nullptr) {
            prio = priorityFunc(val);
        }
        insert(val, prio);
    }

    // O(log N)
    bool extractMax(T& val) {
        if (isEmpty()) return false;

        val = heap[0].data;
        if (val != nullptr) {
            val->setHeapIndex(-1);
        }

        heap[0] = heap[count - 1];
        count--;
        if (count > 0) {
            setIndex(0);
            siftDown(0);
        }
        return true;
    }

    // O(1)
    bool peekMax(T& val) const {
        if (isEmpty()) return false;
        val = heap[0].data;
        return true;
    }
    bool getAt(int i, T& val) const {
        if (i < 0 || i >= count) return false;
        val = heap[i].data;
        return true;
    }//Member 4 added it

    bool removeAtIndex(int index, T& val) {
        if (index < 0 || index >= count) return false;

        val = heap[index].data;
        if (val != nullptr) {
            val->setHeapIndex(-1);
        }

        if (index == count - 1) {
            count--;
            return true;
        }

        heap[index] = heap[count - 1];
        count--;
        setIndex(index);

        siftUp(index);
        siftDown(index);
        return true;
    }

    bool remove(const T& val, T& removedVal) {
        if (val == nullptr) return false;
        int idx = val->getHeapIndex();
        if (idx < 0 || idx >= count || heap[idx].data != val) return false;
        return removeAtIndex(idx, removedVal);
    }

    void reheapify() {
        if (priorityFunc != nullptr) {
            for (int i = 0; i < count; i++) {
                heap[i].priority = priorityFunc(heap[i].data);
            }
        }
        for (int i = (count / 2) - 1; i >= 0; i--) {
            siftDown(i);
        }
    }
};