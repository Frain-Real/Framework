/* Класс очередей */
#ifndef __QUEUE__
#define __QUEUE__

#include "standard.h"

template <typename T>
class Queue {
    private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    Node* front;
    Node* rear;

    public:
        // Конструктор по умолчанию
        Queue() : front(nullptr), rear(nullptr) {}

        // Деструктор
        ~Queue() {
            while (!isEmpty()) {
                pop();
            }
        }

        // Метод для проверки пустоты очереди
        bool isEmpty() const {
            return (front == nullptr);
        }

        // Метод для добавления элемента в конец очереди
        void enqueue(const T& data) {
            Node* newNode = new Node(data);
            if (rear == nullptr) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }

        // Метод для удаления элемента из начала очереди
        void dequeue() {
            if (isEmpty()) {
                throw std::out_of_range("Queue is empty");
            }
            Node* temp = front;
            front = front->next;
            delete temp;
            if (front == nullptr) {
                rear = nullptr;
            }
        }

        // Метод для получения элемента из начала очереди
        T& frontElement() {
            if (isEmpty()) {
                throw std::out_of_range("Queue is empty");
            }
            return front->data;
        }
};


#endif /* __QUEUE__ */