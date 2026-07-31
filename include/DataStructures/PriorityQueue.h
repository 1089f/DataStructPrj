#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class PriorityQueue {
private:
    struct HeapItem {
        T data;
        double priority;
    };

    HeapItem* heap;
    int capacity;
    int count;

    void resize() {
        capacity *= 2;
        HeapItem* newHeap = new HeapItem[capacity];
        for (int i = 0; i < count; i++) {
            newHeap[i] = heap[i];
        }
        delete[] heap;
        heap = newHeap;
    }

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].priority > heap[parent].priority) {
                std::swap(heap[index], heap[parent]);
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

            if (heap[leftChild].priority > heap[maxIndex].priority) {
                maxIndex = leftChild;
            }

            if (rightChild < count && heap[rightChild].priority > heap[maxIndex].priority) {
                maxIndex = rightChild;
            }

            if (maxIndex != index) {
                std::swap(heap[index], heap[maxIndex]);
                index = maxIndex;
            }
            else {
                break;
            }
        }
    }

public:
    PriorityQueue(int initialCap = 20) : capacity(initialCap), count(0) {
        heap = new HeapItem[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    // adding element with priority O(log N)
    void insert(const T& val, double priority) {
        if (count == capacity) {
            resize();
        }
        heap[count] = { val, priority };
        siftUp(count);
        count++;
    }

    // extracting element with highest priority O(log N)
    bool extractMax(T& val) {
        if (isEmpty()) return false;

        val = heap[0].data;
        heap[0] = heap[count - 1];
        count--;
        siftDown(0);
        return true;
    }

    // viewing element with highest priority without removing it O(1)
    bool peekMax(T& val) const {
        if (isEmpty()) return false;
        val = heap[0].data;
        return true;
    }

    // removing element at a specific index in the heap O(log N) - dedicated for     Leave Events
    bool removeAtIndex(int index, T& val) {
        if (index < 0 || index >= count) return false;

        val = heap[index].data;
        heap[index] = heap[count - 1];
        count--;

        if (index < count) {
            siftUp(index);
            siftDown(index);
        }
        return true;
    }
};
