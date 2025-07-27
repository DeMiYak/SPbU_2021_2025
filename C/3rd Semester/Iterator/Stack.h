#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include<iostream>
#include<algorithm>
#include"List.h"

template<class T>
class stack : public list<T>
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




    enum ERR_CODE {EMPTY, OUT_OF_RANGE};




    virtual void Push(T data) {last = new node(data, last);}

    T Pop()
    {
        if(!last) throw EMPTY;
        T lastData = last->data;
        node *temp = last;
        last = last->next;
        delete temp;
        return lastData;

    }

    T GetFront()
    {
        if(!last) throw EMPTY;
        node *temp = last;
        while(temp->next) temp = temp->next;
        return temp->data;
    }

    T GetFront() const
    {
        if(!last) throw EMPTY;
        node *temp = last;
        while(temp->next) temp = temp->next;
        return temp->data;
    }

    void SetFront() const
    {
        if(!Size()) return;
        T data;
        std::cin >> data;
        last->data = data;
    }

    bool IsEmpty() const {return last == nullptr;}

    size_t Size() const
    {
        if(last)
        {
            size_t size = 1;
            node *temp = last;
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
        size_t j = Size();
        if(id >= j) throw OUT_OF_RANGE;
        size_t idNew = j - id - 1;
        node *temp = last;
        for(; idNew; idNew--)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    const T& operator [] (size_t id) const
    {
        if(!last) throw EMPTY;
        size_t j = Size();
        if(id >= j) throw OUT_OF_RANGE;
        size_t idNew = j - id - 1;
        node *temp = last;
        for(; idNew; idNew--)
        {
            temp = temp->next;
        }
        return temp->data;
    }


protected:
    typedef typename list<T>::node node;
    typedef typename list<T>::iterator iterator;
    typedef typename list<T>::const_iterator const_iterator;
    node *last = nullptr;

    virtual void Print(std::ostream &stream) const
    {
        node *temp = last;
        while(temp)
        {
            stream << temp->data;
            if(temp->next) stream << "->";
            temp = temp->next;
        }
        stream << '\n';
    }

//     class const_iterator;
//    class iterator
//    {
//    public:
//        using iterator_category = std::random_access_iterator_tag;
//        using difference_type = std::ptrdiff_t;
//        using value_type = node;
//        using pointer = node*;
//        using reference = node&;
//
//
//        iterator(pointer _i = nullptr): i(_i) {};
//        reference operator * () {return i->data;}
//        pointer operator -> () {return i;}
//
//
//        iterator& operator ++() {if(!(i->next)) return *this; i = i->next; return *this;}
//        iterator operator ++(int)
//        {
//            iterator r = *this;
//            ++(*this);
//            return r;
//        }
//
//
//        iterator& operator --() {if(i == last) return *this; node *temp = last; while(temp->next != i) temp = temp->next; i = temp; return *this;}
//        iterator operator --(int)
//        {
//            iterator r = *this;
//            --(*this);
//            return r;
//        }
//
//        difference_type operator - (const iterator &i2)
//        {/*return i - i2.i;*/
//            signed int i1 = 1, i3 = 1;
//            node *tempI = last, *tempI2 = last;
//            while(tempI != i)
//            {
//                tempI = tempI->next;
//                i1++;
//            }
//            while(tempI2 != i2.i)
//            {
//                tempI2 = tempI2->next;
//                i3++;
//            }
//
//            return i1 - i3;
//        }
//        iterator& operator += (difference_type n) {for(difference_type j = 0; j < n; j++) ++(*this); return *this;}
//        iterator& operator -= (difference_type n) {for(difference_type j = 0; j < n; j++) --(*this); return *this;}
//
//
//
//        iterator operator + (difference_type n) {iterator r = *this; (*this) += n; return r;}
//        iterator operator - (difference_type n) {iterator r = *this; (*this) -= n; return r;}
//
//
//        bool operator == (const iterator& i2) const {return i == i2.i;}
//        bool operator != (const iterator& i2) const {return i != i2.i;}
//
//
//
//        bool operator < (const iterator& i2) const {return i < i2.i;}
//        bool operator <= (const iterator& i2) const {return i <= i2.i;}
//
//
//
//        bool operator > (const iterator& i2) const {return i > i2.i;}
//        bool operator >= (const iterator& i2) const {return i >= i2.i;}
//
//
//        friend const_iterator;
//    private:
//        pointer i;
//    };
//
//
//
//
//    class const_iterator
//    {
//    public:
//        using iterator_category = std::forward_iterator_tag;
//        using difference_type = std::ptrdiff_t;
//        using value_type = const node;
//        using pointer = const node*;
//        using reference = const node&;
//
//
//        const_iterator(pointer _i = nullptr): i(_i) {};
//        const_iterator(const iterator& _i): i(_i) {};
//        reference operator * () {return i->data;}
//        pointer operator -> () {return i;}
//
//
//        const_iterator& operator ++() {if(!(i->next)) return *this; i = i->next; return *this;}
//        const_iterator operator ++(int)
//        {
//            const_iterator r = *this;
//            ++(*this);
//            return r;
//        }
//
//
//        const_iterator& operator --() {if(i == last) return *this; node *temp = last; while(temp->next != i) temp = temp->next; i = temp; return *this;}
//        const_iterator operator --(int)
//        {
//            const_iterator r = *this;
//            --(*this);
//            return r;
//        }
//
//        difference_type operator - (const const_iterator &i2)
//        {/*return i - i2.i;*/
//            signed int i1 = 1, i3 = 1;
//            node *tempI = last, *tempI2 = last;
//            while(tempI != i)
//            {
//                tempI = tempI->next;
//                i1++;
//            }
//            while(tempI2 != i2.i)
//            {
//                tempI2 = tempI2->next;
//                i3++;
//            }
//
//            return i1 - i3;
//        }
//        const_iterator& operator += (difference_type n) {for(difference_type j = 0; j < n; j++) ++(*this); return *this;}
//        const_iterator& operator -= (difference_type n) {for(difference_type j = 0; j < n; j++) --(*this); return *this;}
//
//
//
//        const_iterator operator + (difference_type n) {const_iterator r = *this; (*this) += n; return r;}
//        const_iterator operator - (difference_type n) {const_iterator r = *this; (*this) -= n; return r;}
//
//
//        bool operator == (const const_iterator& i2) const {return i == i2.i;}
//        bool operator != (const const_iterator& i2) const {return i != i2.i;}
//
//
//    private:
//        pointer i;
//    };
public:
    virtual iterator begin() {return iterator(last);}
    virtual iterator end()  {return iterator(last + Size());}

    virtual const_iterator begin() const {return const_iterator(last + Size());}
    virtual const_iterator end() const {return const_iterator(last + Size());}

    virtual const_iterator cbegin() const {return const_iterator(last);}
    virtual const_iterator cend() const {return const_iterator(last + Size());}

private:

    void stackCopy(const stack &s)
    {
        node *temp = s.last;

        if(temp == nullptr) return;

        Push(temp->data);

        if(temp->next == nullptr) return;

        temp = temp->next;
        node *lastTrue = last;
        Push(temp->data);
        node *preLast = last;
        preLast->next = nullptr;
        lastTrue->next = preLast;
        last = lastTrue;

        while(temp->next)
        {
            temp = temp->next;
            Push(temp->data);
            last->next = nullptr;
            preLast->next = last;
            preLast = last;
            last = lastTrue;
        }

    }

    void del()
    {
        while(last) Pop();
    }
};

#endif // STACK_H_INCLUDED
