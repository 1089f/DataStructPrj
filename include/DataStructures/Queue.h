#pragma once
#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* frontPtr;
    Node* rearPtr;
    int count;

public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    ~Queue() {
        T temp;
        while (!isEmpty()) {
            dequeue(temp);
        }
    }

    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    int size() const {
        return count;
    }

    void enqueue(const T& val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        }
        else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    bool dequeue(T& val) {
        if (isEmpty()) return false;

        Node* temp = frontPtr;
        val = frontPtr->data;
        frontPtr = frontPtr->next;

        if (frontPtr == nullptr) {
            rearPtr = nullptr;
        }

        delete temp;
        count--;
        return true;
    }

    bool peek(T& val) const {
        if (isEmpty()) return false;
        val = frontPtr->data;
        return true;
    }
};