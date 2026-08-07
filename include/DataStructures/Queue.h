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

    // Non-destructive traversal hook (read-only iteration)
    template <typename Func>
    void traverse(Func visit) const {
        Node* current = frontPtr;
        while (current != nullptr) {
            visit(current->data);
            current = current->next;
        }
    }

    // Non-destructive print hook
    void print(std::ostream& os = std::cout, void (*printItem)(const T&) = nullptr) const {
        Node* current = frontPtr;
        bool first = true;
        while (current != nullptr) {
            if (!first) os << ", ";
            if (printItem != nullptr) {
                printItem(current->data);
            } else {
                os << current->data;
            }
            first = false;
            current = current->next;
        }
    }
};