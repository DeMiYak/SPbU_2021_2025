//
// Created by vadim on 30.09.2022.
//

#ifndef LABSTACKANDQUEUE_QUEUE_H
#define LABSTACKANDQUEUE_QUEUE_H

#include "Node.h"
#include "iostream"

template<class T>
class Queue {
    Queue() = default;

    explicit Queue(T data) {
        Push(data);
    }

    Queue(const Queue<T> &&queue)  noexcept {
        QueueCopy(queue);
    }

    Queue<T>(Queue<T> &queue) noexcept: nodeHead(queue.nodeHead), nodeTail(queue.nodeTail) {}

    ~Queue() {
        Del();
    }

    enum ERR_CODE {
        Queue_EMPTY
    };

    void PushBack(T data) {
        if (nodeTail != nullptr) {
            nodeTail->connectedNode = new Node<T>(data);
            nodeTail = nodeTail->connectedNode;
        } else {
            nodeTail = new Node<T>(data);
            nodeHead = nodeTail;
        }
    }

    T PopFront() {
        if (nodeHead == nullptr)
            throw Queue_EMPTY;
        Node<T> *tempNode = nodeHead;
        T nodeData = nodeHead->data;
        nodeHead = nodeHead->connectedNode;
        delete tempNode;
        return nodeData;
    }

    T GetFront() {
        if (nodeHead == nullptr)
            throw Queue_EMPTY;
        return nodeHead->data;
    }

    void SetFront(T data) {
        if (nodeHead == nullptr)
            throw Queue_EMPTY;
        nodeHead->data = data;
    }

    bool IsEmpty() {
        return nodeTail == nullptr;
    }

    Queue<T> &operator=(Queue<T> &&queue)  noexcept {
        if (&queue == this)
            return *this;
        this->Del();
        nodeTail = queue.nodeTail;
        nodeHead = queue.nodeHead;
        return *this;
    }

    Queue<T> &operator=(const Queue<T> &queue) {
        if (&queue == this)
            return *this;
        this->Del();
        QueueCopy(queue);
        return *this;
    }

    void PrintNods() {
        Node<T> *itNode = nodeHead; // Head -> [1->2->3->4->5] <- Tail
        while (itNode) {
            std::cout << itNode->data << ' ';
            itNode = itNode->connectedNode;
        }
        std::cout << "\n";
    }

private:
    Node<T> *nodeHead = nullptr;
    Node<T> *nodeTail = nullptr;

    void QueueCopy(const Queue<T> &queue) {
        Node<T> *itNode = queue.nodeHead;
        while (itNode) {
            this->PushBack(itNode->data);
            itNode = itNode->connectedNode;
        }
    }

    void Del() {
        while (nodeHead != nullptr) {
            this->PopFront();
        }
        nodeTail = nullptr;
    }
};


#endif //LABSTACKANDQUEUE_QUEUE_H
