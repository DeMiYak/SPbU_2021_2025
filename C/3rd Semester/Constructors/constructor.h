#ifndef CONSTRUCTOR_H_INCLUDED
#define CONSTRUCTOR_H_INCLUDED

#include<iostream>
#include<cmath>

template <class T> class array
{
public:
    // ������������/�����������


    // ����������� �� ���������
    array (size_t _size = 0): size(_size), data (new T[size]) {}
    // ����������� �����������
    array (const array& a): size(a.size), data(new T[size])
    {
        for (size_t i = 0; i < size; ++i)
            data[i] = a[i];
    }
    // ����������� �����������
    array (const array&& a): size(a.size), data(a.data) {}


    // ����������
    ~array () {delete [] data; }


//
    enum ERR_CODE {OUT_OF_RANGE, DIM_ERR, DIV_ZERO};


    // ��������� �������� �������� �������

    // �������� �������� �������� �������
    T& operator [] (size_t i) {return data[i]; }
    const T& operator [] (size_t i) const {return data[i]; }


    // �������� �������� �������� ������� (����������)
    T& operator () (size_t i) {if (i >= size) throw OUT_OF_RANGE; return data[i]; }
    const T& operator () (size_t i) const {if (i >= size) throw OUT_OF_RANGE; return data[i]; }


    // ������������ ������������
    array& operator = (const array& a)
    {
        if (this == &a) return *this;



        delete [] data;



        size = a.size;
        data = new T [size];
        for (size_t i = 0; i < size; ++i)
            data[i] = a[i];



        return *this;
    }


    // ������������ ������������
    array& operator = (const array&& a)
    {
        size = a.size;
        data = a.data;
        return *this;
    }


    // ���������


    array& operator *= (const T& sc)
    {
        for(size_t i = 0; i < size; i++) data[i] *= sc;
        return *this;
    }

    // �������� ���������� ���������
    T operator * (const array& a) const             // Scalar Multiplication
    {
        T sum = 0;                                      // Ctrl + Shift + C = ����������� ����������� ������� (���������)
        if(size == a.size)                              // Ctrl + Shift + X = ������ "���������", ������������������
        {
            // using std::cout;
            // using std::endl;
            // cout << "1" << endl;
            // cout << size << ' ' << a.size << endl;
            for(size_t i = 0; i < size; i++)
            {
                sum += data[i]*a[i];
                // cout << sum << endl;
            }
        } else throw DIM_ERR;
        return sum;
    }

    // �������� ��������� ������� �� ����� (���������������)
    friend array& operator * (const T& sc, const array& a) // ��������� �����
    {
        array *temp = new array(a.size);

        for(size_t i = 0; i < a.size; i++)
        {
            (*temp)[i] = a[i]*sc;
        }
        return *temp;
    }

    array& operator *(const T& sc) const                   // ��������� ������
    {
        array *temp = new array(size);

        for (size_t i = 0; i < size; i++)
        {
            (*temp)[i] = (*this)[i]*sc;
        }
        return *temp;
    }

    // �������

    array& operator /= (const T& sc)
    {
        if(sc == 0) throw DIV_ZERO;
        for(size_t i = 0; i < size; i++)
        {
            data[i] /= sc;
        }
        return *this;
    }

    friend array& operator / (const T& sc, const array& a)
    {
        if(sc == 0) throw DIV_ZERO;
        array *temp = new array(a.size);
        for(size_t i = 0; i < a.size; i++)
            (*temp)[i] = a[i]/sc;
        return *temp;
    }

    array& operator / (const T& sc) const
    {
        if(sc == 0) throw DIV_ZERO;
        array *temp = new array(size);
        for(size_t i = 0; i < size; i++)
            (*temp)[i] = data[i]/sc;
        return *temp;
    }
    // ��������
    // ����������� (� ������� �������� �������)
    array& operator += (const T& sc) const
    {
        for(size_t i = 0; i < size; i++)
            data[i] += sc;
        return *this;
    }

    array& operator += (const array& a) const
    {
        if(size != a.size) throw DIM_ERR;
        for(size_t i = 0; i < size; i++)
            data[i] += a[i];
        return *this;
    }

    friend array& operator + (const T& sc, const array& a)
    {
        array *temp = new array(a.size);
        for(size_t i = 0; i < a.size; i++) (*temp)[i] = a[i] + sc;
        return *temp;
    }

    array& operator + (const T& sc) const
    {
        array *temp = new array(size);
        for(size_t i = 0; i < size; i++) (*temp)[i] = data[i] + sc;
        return *temp;
    }

    array& operator + (const array& a) const
    {
        if(size != a.size) throw DIM_ERR;
        array *temp = new array(size);
        for(size_t i = 0; i < size; i++)
            (*temp)[i] = a[i] + data[i];
        return *temp;
    }
    // ���������
    array& operator -= (const T& sc) const
    {
        for(size_t i = 0; i < size; i++)
            data[i] -= sc;
        return *this;
    }

    array& operator -= (const array& a) const
    {
        if(size != a.size) throw DIM_ERR;
        for(size_t i = 0; i < size; i++) data[i] -= a[i];
        return *this;
    }

    array& operator - (const T& sc) const
    {
        array *temp = new array(size);
        for(size_t i = 0; i < size; i++) (*temp)[i] = data[i] - sc;
        return *temp;
    }
    friend array& operator - (const T& sc, const array& a)
    {
        array *temp = new array(a.size);
        for(size_t i = 0; i < a.size; i++) (*temp)[i] = sc - a[i];
        return *temp;
    }

    array& operator - (const array& a)
    {
        if(size != a.size) throw DIM_ERR;
        array *temp = new array(size);
        for(size_t i = 0; i < size; i++) (*temp)[i] = data[i] - a[i];
        return *temp;
    }
    // ���������
    bool operator == (const array& a) const
    {
        if (this == &a) return true;
        if (size != a.size) return false;
        for (size_t i = 0; i < size; ++i)
            if (data[i] != a[i]) return false;
        return true;
    }

    bool operator != (const array &a) const
    {
        return !(*this == a);
    }


    // ������� "�����" (��� ������������� ���������� ������ ������������� ��������)
    T Norm(size_t degree)
    {

    }
    // ��������� �����/������
    friend std::istream& operator >> (std::istream &stream, array &a)
    {
        for(size_t i = 0; i < a.size; ++i) stream >> a[i];
        return stream;
    }

    friend std::ostream& operator << (std::ostream &stream, array &a)
    {
        stream << "[";
        if(a.size)
        {

            for(size_t i = 0; i < a.size - 1; ++i) stream << a[i] << ", ";
            stream << a[a.size - 1];
        }
        stream << "]";
        return stream;
    }



private:
    size_t size;
    T *data;
};

#endif // CONSTRUCTOR_H_INCLUDED
