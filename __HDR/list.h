/* Класс списков */
#ifndef __LIST__
#define __LIST__

#include "standard.h"
#include "stdlib.h"

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        static void* operator new(size_t size) {
            void* p = malloc(size);
            return p;
        }

        static void operator delete(void* p) {
            free(p);
        }

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    u32 size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    void push_back(T value) {
        Node* new_node = new Node(value);
        if (tail == nullptr) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        ++size;
    }

    void push_front(T value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        ++size;
    }

    void insert(int index, T value) {
        if (index == 0) {
            push_front(value);
        } else if (index == size) {
            push_back(value);
        } else {
            Node* new_node = new Node(value);
            Node* current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            new_node->prev = current;
            new_node->next = current->next;
            current->next->prev = new_node;
            current->next = new_node;
            size++;
        }
    }

    

    T get(int index) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void remove(int index) {
        if (index == 0) {
            pop_front();
        } else if (index == size - 1) {
            pop_back();
        } else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            size--;
        }
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    void pop_back() {
        if (tail == nullptr) {
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
    }

    T& operator[](int index) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    static void* operator new(size_t size) {
        void* p = malloc(size);
        return p;
    }

    static void operator delete(void* p) {
        free(p);
    }

};





#endif /* __LIST__ */