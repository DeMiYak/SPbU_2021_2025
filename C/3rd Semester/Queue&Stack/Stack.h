#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include"node.h"
#include<iostream>


////Реализовать шаблонные классы "стек" и "очередь" со всеми необходимыми методами:
////
////
////
////конструктор по умолчанию - пустого контейнера, конструктор копирования и перемещения;
////
////деструктор,;
////
////операцию присваивания и присваивания по перемещению;
////
////помещение элемента (Push), изъятие элемента (Pop), проверку на пустоту (IsEmpty), получение ссылки на головной элемент (GetFront) с выбрасыванием необходимых исключений;
////
////вывод элементов списка (в выходной поток) без его модификации;
////
////(не обязательно) ввод элементов в список (из входного потока) путем добавления их к списку (Push) - без очистки списка.
////
////(не обязательно) удаление всех элементов списка (без удаления объекта - не деструктор), получение количества элементов списка и др. методы.
////
////Реализовать стек и очередь посредством линейного односвязного списка.



template<class T>
class stack
{
public:

    stack(): last(nullptr) {}

    stack(const stack<T> &s) {stackCopy(s);}

    stack<T>(stack<T> &&s): last(s.last) {s.last = nullptr;}





    stack<T> &operator = (const stack<T> &s)
    {
        if(&s == this) return *this;
        del();
        stackCopy(s);
        return *this;
    }




    stack<T> &operator = (stack<T> &&s)
    {
        if(&s == this) return *this;
        del();
        last = s.last;
        s.last = nullptr;
        return *this;
    }



    ~stack() {del();}


    void Test()
    {
        stack<T> P;
        node<T> *origin = last;
        P.Push(origin->data);
        origin = origin->next;
        node<T> *temp = P.last;
        while(origin)
        {
            P.Push(origin->data);
            std::cout << temp->data << '\n';
            origin = origin->next;
        }
    }

    enum ERR_CODE {EMPTY, OUT_OF_RANGE};




    void Push(T data) {last = new node<T>(data, last);}

    T Pop()
    {
        if(!last) throw EMPTY;
        T lastData = last->data;
        node<T> *temp = last;
        last = last->next;
        delete temp;
        return lastData;

    }

    T& GetFront()
    {
        if(!last) throw EMPTY;
        node<T> *temp = last;
        while(temp->next) temp = temp->next;
        return temp->data;
    }

    const T& GetFront() const
    {
        if(!last) throw EMPTY;
        node<T> *temp = last;
        while(temp->next) temp = temp->next;
        return temp->data;
    }

    bool IsEmpty() {return last == nullptr;}

    void PrintStack()
    {
        node<T> *temp = last;
        while(temp)
        {
            std::cout << temp->data;
            if(temp->next) std::cout << "->";
            temp = temp->next;
        }
        std::cout << '\n';
    }

    size_t QuantifyStack()
    {
        if(last)
        {
            size_t size = 1;
            node<T> *temp = last;
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
        if(!last) throw EMPTY;
        size_t j = QuantifyStack();
        if(id >= j) throw OUT_OF_RANGE;
        size_t idNew = j - id - 1;
        node<T> *temp = last;
        for(; idNew; idNew--)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    const T& operator [] (size_t id) const
    {
        if(!last) throw EMPTY;
        size_t j = QuantifyStack();
        if(id >= j) throw OUT_OF_RANGE;
        size_t idNew = j - id - 1;
        node<T> *temp = last;
        for(; idNew; idNew--)
        {
            temp = temp->next;
        }
        return temp->data;
    }
//    stack operator + (const stack &s1, const stack &s2)
//    {
//        s1Temp = s1.stackCopy();
//        s2Temp = s2.stackCopy();
//        node<T> *temp = s2Temp.Front();
//        temp->next = s1.last;
//
//        return s2;
//    }

private:
    node<T> *last = nullptr;


    void stackCopy(const stack &s)
    {
        node<T> *temp = s.last;
        while(temp)
        {
            Push(temp->data);
            temp = temp->next;
        }
        PrintStack();
        node<T> *tempNew = last;
        temp = last->next; // Работает, так как по начальным данным last, next = nullptr.

        if(temp == nullptr) return;

        last->next = nullptr;
        while(temp->next)
        {
            tempNew = temp;
            temp = temp->next;
            tempNew->next = last;
            last = tempNew;
        }
        temp->next = last;
        last = temp;
    }


    void del()
    {
        while(last) Pop();
    }
};

#endif // STACK_H_INCLUDED
