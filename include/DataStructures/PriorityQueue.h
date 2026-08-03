#pragma once
#include <iostream>

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

    void swapItems(int i, int j) {
         
        HeapItem temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;

    
        heap[i].heapIndex = i;
        heap[j].heapIndex = j;

        
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
                swapItems(index, parent); // 3. استخدام swapItems بدلاً من std::swap
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

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void insert(const T& val, double priority) {
        if (count == capacity) {
            resize();
        }
        heap[count] = { val, priority, count };
        siftUp(count);
        count++;
    }

   
    bool extractMax(T& val) {
        if (isEmpty()) return false;

        val = heap[0].data;
        heap[0] = heap[count - 1];
        heap[0].heapIndex = 0; 
        count--;
        siftDown(0);
        return true;
    }

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
        heap[index].heapIndex = index;
        count--;

      
        siftUp(index);
        siftDown(index);
        return true;
    }
    bool removeByValue(const T& val, int targetIndex, T& removedVal) {
        if (targetIndex >= 0 && targetIndex < count && heap[targetIndex].data == val) {
            return removeAtIndex(targetIndex, removedVal);
        }
        return false;
    }
};