//
// Created by vadim on 29.09.2022.
//

#ifndef LABSTACKANDQUEUE_STACK_H
#define LABSTACKANDQUEUE_STACK_H

#include "Node.h"
#include <iostream>

template<class T>
class Stack {
public:
    Stack() = default;

    explicit Stack(T data) {
        Push(data);
    }

    Stack(const Stack<T> &stack) {
        StackCopy(stack);
    }

    Stack<T>(Stack<T> &&stack) noexcept: node(stack.node) {
        stack.node = nullptr;
    }

    ~Stack() {
        Del();
    }

    enum ERR_CODE {
        STACK_EMPTY
    };

    void Push(T data) {
        node = new Node<T>(data, node);
    }

    T Pop() {
        if (node == nullptr)
            throw STACK_EMPTY;
        Node<T> *tempNode = node;
        T nodeData = node->data;
        node = node->connectedNode;
        delete tempNode;
        return nodeData;
    }

    T GetFront() {
        if (node == nullptr)
            throw STACK_EMPTY;
        return node->data;
    }

    void SetFront(T data) {
        if (node == nullptr)
            throw STACK_EMPTY;
        node->data = data;
    }

    bool IsEmpty() {
        return node == nullptr;
    }

    Stack<T> &operator=(Stack<T> &&stack)  noexcept {
        if (&stack == this)
            return *this;
        this->Del();
        node = stack.node;
        return *this;
    }

    Stack<T> &operator=(const Stack<T> &stack) {
        if (&stack == this)
            return *this;
        this->Del();
        StackCopy(stack);
        return *this;
    }

    void PrintNods() {
        Node<T> *itNode = node;
        while (itNode) {
            std::cout << itNode->data << ' ';
            itNode = itNode->connectedNode;
        }
        std::cout << "\n";
    }

private:
    Node<T> *node = nullptr;

    void StackCopy(const Stack<T> &stack) {
        Node<T> *itNode = stack.node;
        while (itNode) {
            this->Push(itNode->data);
            itNode = itNode->connectedNode;
        }
        Node<T> *lastNode = this->node;
        itNode = this->node->connectedNode;
        while (itNode->connectedNode != nullptr) {
            Node<T> *tempNode = itNode->connectedNode;
            itNode->connectedNode = lastNode;
            lastNode = itNode;
            itNode = tempNode;
        }
        itNode->connectedNode = lastNode;
        this->node->connectedNode = nullptr;
        this->node = itNode;
    }

    void Del() {
        while (node != nullptr) {
            this->Pop();
        }
    }
};


#endif //LABSTACKANDQUEUE_STACK_H
