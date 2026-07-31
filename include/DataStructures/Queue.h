#pragma once
// Owner: Member 1 (Data Structures)
// Templated FIFO queue. Used for: Events queue, Waiting Emergency patients.
// NOTE: Emergency waiting queue needs O(1) removal from the middle (LeaveEvent
// can target any waiting patient) -> back this with a doubly linked list
// internally, not a plain array queue.
// TODO: implement enqueue, dequeue, remove(T value / pointer), isEmpty.

template <typename T>
class Queue {
public:
    Queue() {}
    ~Queue() {}

    // TODO: void enqueue(T value);
    // TODO: T dequeue();
    // TODO: void remove(T value); // O(1) given the item's node
    // TODO: bool isEmpty() const;
};
