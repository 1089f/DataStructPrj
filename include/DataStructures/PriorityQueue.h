#pragma once
// Owner: Member 1 (Data Structures)
// Templated max-heap based priority queue. Used for: Waiting Regular patients.
// IMPORTANT design rules agreed by the team:
//  1. Every element tracks its own heapIndex (kept in sync by swap()).
//  2. swap(i, j) is the ONLY function allowed to move two elements in the
//     underlying array. sift-up/sift-down must call swap(), never move
//     elements directly. This guarantees heapIndex is never out of sync.
//  3. remove(T value) uses heapIndex for O(log N) arbitrary removal
//     (needed for LeaveEvent / UrgentEvent on a Regular patient).
// TODO: implement enqueue (insert + sift-up), dequeue (extract-max), remove(T).

template <typename T>
class PriorityQueue {
public:
    PriorityQueue() {}
    ~PriorityQueue() {}

    // TODO: void enqueue(T value, double priority);
    // TODO: T dequeue();
    // TODO: void remove(T value); // uses heapIndex stored on the element
private:
    // TODO: void swap(int i, int j); // the ONLY place that moves two elements
    // TODO: void siftUp(int i);
    // TODO: void siftDown(int i);
};
