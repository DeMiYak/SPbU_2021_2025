#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include"Node.h"
#include<iostream>

////–еализовать шаблонные классы "стек" и "очередь" со всеми необходимыми методами:
////
////
////
////конструктор по умолчанию - пустого контейнера, конструктор копировани€ и перемещени€;
////
////деструктор,;
////
////операцию присваивани€ и присваивани€ по перемещению;
////
////помещение элемента (Push), изъ€тие элемента (Pop), проверку на пустоту (IsEmpty), получение ссылки на головной элемент (GetFront) с выбрасыванием необходимых исключений;
////
////вывод элементов списка (в выходной поток) без его модификации;
////
////(не об€зательно) ввод элементов в список (из входного потока) путем добавлени€ их к списку (Push) - без очистки списка.
////
////(не об€зательно) удаление всех элементов списка (без удалени€ объекта - не деструктор), получение количества элементов списка и др. методы.
////
////–еализовать стек и очередь посредством линейного односв€зного списка.


template<class T>
class queue
{
public:

    // Queue Constructors

    queue(): front(nullptr), back(nullptr) {}

    queue(const queue<T> &q){queueCopy(q);}

    queue<T>(queue<T> &&q): front(q.front), back(q.back) {q.front = nullptr; q.back = nullptr;}


    // Queue Assignments

    queue<T> &operator = (queue<T> &&q)
    {
        if(&q == this) return *this;
        del();
        front = q.front;
        back = q.back;
        q.front = q.back = nullptr;
        return *this;
    }


    queue<T> &operator = (const queue<T> &q)
    {
        if(&q == this) return *this;
        del();
        queueCopy(q);
        return *this;
    }



    // Queue Destructor

    ~queue() {del();}




    enum ERR_CODE {EMPTY, OUT_OF_RANGE};


    // Standard Methods for Queue

    void Push(T data)
    {
        if(back)
        {
            back->next = new node<T>(data);
            back = back->next;
        } else
        {
            back = new node<T>(data);
            front = back;
        }
    }

    T PopFront()
    {
        if(!front) throw EMPTY;
        node<T> *temp = front;
        T frontData = front->data;
        front = front->next;
        delete temp;
        return frontData;
    }

    const T PopFront() const
    {
        if(!front) throw EMPTY;
        node<T> *temp = front;
        T frontData = front->data;
        front = front->next;
        delete temp;
        return frontData;
    }

    T& GetFront()
    {
        if(!front) throw EMPTY;
        return front->data;
    }

    const T& GetFront() const
    {
        if(!front) throw EMPTY;
        return front->data;
    }

    bool IsEmpty() {return front == nullptr;}


    // Print Method
    void PrintQueue()
    {
        node<T> *temp = front;
        std::cout << '[';
        while(temp)
        {
            if(temp != front) {std::cout << ", ";}
            std::cout << temp->data;
            temp = temp->next;
        }
        std::cout << ']' << '\n';
    }

    // Quantity Method

    size_t QuantifyQueue()
    {
        if(front)
        {
            size_t size = 1;
            node<T> *temp = front;
            while(temp->next)
            {
                size++;
                temp = temp->next;
            }
            return size;
        } else return 0;
    }

    T& operator [] (size_t id)
    {
        id -= 1;
        if(!front) throw EMPTY;
        if(id >= QuantifyQueue()) throw OUT_OF_RANGE;
        node<T> *temp = front;
        for(; id; id--)
            temp = temp->next;
        return temp->data;
    }

    const T& operator [] (size_t id) const
    {
        id -= 1;
        if(!front) throw EMPTY;
        if(id >= QuantifyQueue()) throw OUT_OF_RANGE;
        node<T> *temp = front;
        for(; id; id--)
            temp = temp->next;
        return temp->data;
    }

private:
    node<T> *front = nullptr, *back = nullptr;


    void queueCopy(const queue<T> &q)
    {
        node<T> *temp = q.front;
        while(temp)
        {
            Push(temp->data);
            temp = temp->next;
        }
    }



    void del()
    {
        while(front)
            PopFront();
        back = nullptr;
    }
};

#endif // QUEUE_H_INCLUDED
