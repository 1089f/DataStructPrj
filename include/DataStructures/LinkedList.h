#pragma once
#include <iostream>

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

private:
    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }

    // adding to the end O(1)
    void insertEnd(const T& val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    // adding to the front O(1)
    void insertFront(const T& val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    // removing the first element O(1)
    bool removeHead(T& val) {
        if (isEmpty()) return false;

        Node* temp = head;
        val = head->data;

        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
			tail = nullptr; // the list is now empty
        }

        delete temp;
        count--;
        return true;
    }

	// deleting a specific node O(1)
    bool removeNode(Node* nodePtr) {
        if (nodePtr == nullptr || isEmpty()) return false;

        if (nodePtr == head) {
            T tempVal;
            return removeHead(tempVal);
        }

        if (nodePtr == tail) {
            Node* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
            delete temp;
            count--;
            return true;
        }

		// deleting a node in the middle
        nodePtr->prev->next = nodePtr->next;
        nodePtr->next->prev = nodePtr->prev;

        delete nodePtr;
        count--;
        return true;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        count = 0;
    }

    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }

    // Non-destructive traversal hook (read-only iteration)
    template <typename Func>
    void traverse(Func visit) const {
        Node* current = head;
        while (current != nullptr) {
            visit(current->data);
            current = current->next;
        }
    }

    // Non-destructive print hook
    void print(std::ostream& os = std::cout, void (*printItem)(const T&) = nullptr) const {
        Node* current = head;
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
