#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include<iostream>
#include<algorithm>

template<class T>
class list
{
public:

    list() {}
    virtual ~list() {}

    virtual void Push(T data) = 0;
    virtual T Pop() = 0;
    virtual T GetFront() const = 0;
    virtual bool IsEmpty () const = 0;
    virtual size_t Size() const = 0;

protected:
   virtual void Print (std::ostream &stream) const = 0;

    struct node
    {
        T data;
        struct node *next;
        node(T _data, struct node *_next = nullptr): data(_data), next(_next) {}
    };
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const node;
        using pointer = const node*;
        using reference = const node&;


        const_iterator(pointer _i = nullptr): i(_i) {};
        const_iterator(const iterator& _i): i(_i) {};
        reference operator * () {return i->data;}
        pointer operator -> () {return i;}


        const_iterator& operator ++() {if(!(i->next)) return *this; i = i->next; return *this;}
        const_iterator operator ++(int)
        {
            const_iterator r = *this;
            ++i;
            return r;
        }


        const_iterator& operator --() {--i; return *this;}
        const_iterator operator --(int)
        {
            const_iterator r = *this;
            --i;
            return r;
        }

        difference_type operator - (const const_iterator &i2) {return i - i2.i;}
        const_iterator& operator += (difference_type n) {for(difference_type j = 0; j < n; j++) ++(*this); return *this;}
        const_iterator& operator -= (difference_type n) {for(difference_type j = 0; j < n; j++) --(*this); return *this;}



        const_iterator operator + (difference_type n) {const_iterator r = *this; (*this) += n; return r;}
        const_iterator operator - (difference_type n) {const_iterator r = *this; (*this) -= n; return r;}


        bool operator == (const const_iterator& i2) const {return i == i2.i;}
        bool operator != (const const_iterator& i2) const {return i != i2.i;}



    private:
        pointer i;
    };

    friend std::ostream& operator << (std::ostream &stream, const list<T> &l)
    {
        l.Print(stream);
        //for(const auto& i: l) stream << i << " ";
        return stream;
    }

    friend std::istream& operator >> (std::istream &stream, list<T> &l)
    {
        T data;
        std::cin >> data;
        l.Push(data);
        return stream;
    }

};

#endif // LIST_H_INCLUDED
