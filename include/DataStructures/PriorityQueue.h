#pragma once
#include <iostream>
#include "../Entities/Patient.h"

template <typename T>
class PriorityQueue {
private:
    struct HeapItem {
        T data;
        double priority;
        int heapIndex;
    };

    HeapItem* heap;
    int capacity;
    int count;

    void setIndex(int pos) {
        heap[pos].heapIndex = pos;
        heap[pos].data->setHeapIndex(pos);
    }

    void swapItems(int i, int j) {
        HeapItem temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;

        setIndex(i);
        setIndex(j);
    }

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

            if (heap[leftChild].priority > heap[maxIndex].priority) {
                maxIndex = leftChild;
            }
            if (rightChild < count && heap[rightChild].priority > heap[maxIndex].priority) {
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
    PriorityQueue(int initialCap = 20) : capacity(initialCap), count(0) {
        heap = new HeapItem[capacity];
    }

    ~PriorityQueue() {
        delete[] heap;
    }

    bool isEmpty() const { return count == 0; }
    int size() const { return count; }

    // O(log N) 
    void insert(const T& val, double priority) {
        if (count == capacity) {
            resize();
        }
        heap[count] = { val, priority, count };
        val->setHeapIndex(count);
        siftUp(count);
        count++;
    }

    // O(log N)
    bool extractMax(T& val) {
        if (isEmpty()) return false;

        val = heap[0].data;
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

    bool removeAtIndex(int index, T& val) {
        if (index < 0 || index >= count) return false;

        val = heap[index].data;

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
        int idx = val->getHeapIndex();
        if (idx < 0 || idx >= count || heap[idx].data != val) return false;
        return removeAtIndex(idx, removedVal);
    }
};