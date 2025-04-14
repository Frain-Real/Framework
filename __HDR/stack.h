/* Класс очередей */
#ifndef __STACK__
#define __STACK__

#include "standard.h"

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr) : data(d), next(n) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const T& data) {
        top = new Node(data, top);
    }

    void pop() {
        if (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    T peek() const {
        if (top != nullptr) {
            return top->data;
        } else {
            throw std::runtime_error("Stack is empty");
        }
    }
};


#endif /* __STACK__ */