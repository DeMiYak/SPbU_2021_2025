/**
* Реализовать итераторы (обычный и константный) для классов стек и очередь,
* а также виртуальные методы begin()/end() и cbegin()/cend(), работающие соответственно принципам STL.
*
* * Заменить вызов print() в operator << на использование итератора.
*/

#include <iostream>
#include <algorithm>
#include"List.h"
#include"Queue.h"
#include"Stack.h"


using namespace std;



class array
{
public:
    array(size_t s = 0): size(s), data(new double[s]) {}



    double& operator [] (size_t i) {return data[i]; }
    const double& operator [] (size_t i) const {return data[i]; }



    class const_iterator;
    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = double;
        using pointer           = double*;
        using reference         = double&;



        iterator (pointer _i = nullptr): i(_i) {};
        reference operator * () {return *i; }
        pointer operator -> () {return i; }



        iterator& operator++() { ++i; return *this; }
        iterator operator++(int)
        {
            iterator r = *this;
            ++i;
            return r;
        }



        iterator& operator--() { --i; return *this; }
        iterator operator--(int)
        {
            iterator r = *this;
            --i;
            return r;
        }



        difference_type operator-(const iterator& i2) { return i - i2.i; }
        iterator& operator += (difference_type n) {i += n; return *this; }
        iterator& operator -= (difference_type n) {i -= n; return *this; }



        iterator operator + (difference_type n) {iterator r = *this; r += n; return r; }
        iterator operator - (difference_type n) {iterator r = *this; r -= n; return r; }






        bool operator == (const iterator& i2) const {return i == i2.i; }
        bool operator != (const iterator& i2) const {return i != i2.i; }



        bool operator < (const iterator& i2) const {return i < i2.i; }
        bool operator <= (const iterator& i2) const {return i <= i2.i; }



        bool operator > (const iterator& i2) const {return i > i2.i; }
        bool operator >= (const iterator& i2) const {return i >= i2.i; }





        friend const_iterator;
    private:
        pointer i;
    };



    iterator begin() {return iterator(data); }
    iterator end() {return iterator(data + size); }




    class const_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = double;
        using pointer           = const double*;
        using reference         = const double&;



        const_iterator (pointer _i = nullptr): i(_i) {};
        const_iterator (const iterator& _i): i(_i.i) {};



        reference operator * () {return *i; }
        pointer operator -> () {return i; }



        const_iterator& operator++() { ++i; return *this; }
        const_iterator operator++(int)
        {
            const_iterator r = *this;
            ++i;
            return r;
        }



        bool operator == (const const_iterator& i2) const {return i == i2.i; }
        bool operator != (const const_iterator& i2) const {return i != i2.i; }



    private:
        pointer i;
    };



    const_iterator begin() const {return const_iterator(data); }
    const_iterator end() const {return const_iterator(data + size); }



    const_iterator cbegin() const {return const_iterator(data); }
    const_iterator cend() const {return const_iterator(data + size); }



private:



    array(const array&) = delete;
    array(array&&) = delete;



    array& operator = (const array&) = delete;
    array& operator = (array&&) = delete;



    size_t size;
    double *data;
};




template<class T>
bool rcmp (T d1, T d2) {return d2 < d1;}


int main()
{

    size_t p;
    cout << "Press 1 to pick the queue or 2 to pick the stack: ";
    cin >> p;
    double key;
    size_t id;

    if(p == 1)
    {
        queue<double> q;


        size_t p;
        cout << "Choose the method:\n1. Push\n2. PopFront\n3. GetFront\n4. SetFront\n5. IsEmpty\n6. QuantifyQueue\n7. Print queue's element\n8. PrintQueue\n\n";
        cin >> p;
        while(1 <= p && p <= 8)
        {
            switch(p)
            {
            case 1:
                cout << "Enter the number (0 to return): ";
                cin >> key;
                while(key)
                {
                    q.Push(key);
                    cout << q;
                    cin >> key;
                }
                break;
            case 2:
                cout << "Pop: " << q.Pop();
                break;
            case 3:
                key = q.GetFront();
                cout << "Get: " << key;
                break;
            case 4:
                q.SetFront();
                cout << q;
                break;
            case 5:
                cout << "Is Empty: " << q.IsEmpty();
                break;
            case 6:
                cout << "Current amount: " << q.Size();
                cout << q;
                break;
            case 7:
                cout << "Enter the number: ";
                cin >> id;
                cout << q[id];
                break;
            case 8:
                cout << q;
                break;
            default:
                break;
            }
            cout << "\nChoose the method:\n1. Push\n2. PopFront\n3. GetFront\n4. SetFront\n5. IsEmpty\n6. QuantifyQueue\n7. Print queue's element\n8. PrintQueue\n\n";
            cin >> p;
        }
        queue<double> q2 = q;
        cout << q2;
        sort(q2.begin() + 2, q2.end(), rcmp);
        cout << q2;
    }
    else if(p == 2)
    {
        stack<double> s;


        size_t p;
        cout << "Choose the method:\n1. Push\n2. PopFront\n3. GetFront\n4. SetFront\n5. IsEmpty\n6. QuantifyStack\n7. Print stack's element\n8. PrintStack\n\n";
        cin >> p;
        while(1 <= p && p <= 9)
        {
            switch(p)
            {
            case 1:
                cout << "Enter the number (0 to return): ";
                cin >> key;
                while(key)
                {
                    s.Push(key);
                    cout << s;
                    cin >> key;
                }
                break;
            case 2:
                cout << "Pop: " << s.Pop();
                break;
            case 3:
                key = s.GetFront();
                cout << "Get: " << key;
                break;
            case 4:
                s.SetFront();
                cout << s;
                break;
            case 5:
                cout << "Is Empty: " << s.IsEmpty();
                break;
            case 6:
                cout << "Current amount: " << s.Size();
                cout << s;
                break;
            case 7:
                cout << "Enter the number: ";
                cin >> id;
                cout << s[id];
                break;
            case 8:
                cout << s;
            default:
                break;
            }
            cout << "\nChoose the method:\n1. Push\n2. PopFront\n3. GetFront\n4. SetFront\n5. IsEmpty\n6. QuantifyStack\n7. Print stack's element\n8. PrintStack\n\n";
            cin >> p;
        }
        stack<double> s2 = s;
        cout << s2;
        sort(s2.begin() + 2, s2.end(), rcmp);
        cout << s2;
    } else {cout << "Wrong number. Finishing programme...";}
    // cout << "\n... Memory cleared";
    array a (10);
/*
    for (auto i = a.begin(); i != a.end(); ++i)
    {
        cin >> *i;
    }
*/



    for (auto& i: a) cin >> i;



    sort(begin(a)+2, end(a), rcmp);



    for (const auto& i: a) cout << i << " ";
/*
    for (auto i = a.cbegin(); i != a.cend(); ++i)
    {
        cout << *i;
    }
*/
    return 0;
}
