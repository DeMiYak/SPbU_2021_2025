#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template <class T>
struct node
{
public:
    T data;
    node<T> *next;
    node(T _data, node *_next = nullptr): data(_data), next(_next) {}
};

#endif // NODE_H_INCLUDED
