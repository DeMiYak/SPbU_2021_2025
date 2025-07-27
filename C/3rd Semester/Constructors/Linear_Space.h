#ifndef LINEAR_SPACE_H_INCLUDED
#define LINEAR_SPACE_H_INCLUDED
#include <cstddef>
#include <complex>
#include<cmath>
#include <iostream>

class pfield{
public:
    pfield( int _v = 0, size_t _p = 5): p{_p},v{_v%(int)p}{};
    ~pfield(){}

    enum ERR_CODE{ORDER_ERR};

    pfield& operator = (const pfield& b){
        v = b.v;
        p = b.p;
        return *this;
    }

    bool operator == (const pfield& b){
        if(p != b.p)throw ORDER_ERR;

        return ((v - b.v)%(int)p == 0);
    }

    bool operator != (const pfield& b){
        if(p != b.p)throw ORDER_ERR;

        return !(*this == b);
    }

    pfield& operator + (const pfield& b)const{
        if(p != b.p)throw ORDER_ERR;

        pfield *temp = new pfield((v + b.v)%(int)p, p);
        return *temp;
    }

    pfield& operator += (const pfield& b){
        if(p != b.p)throw ORDER_ERR;

        v = (v+b.v)%(int)p;
        return *this;
    }

    pfield& operator - (const pfield& b)const{
        if(p != b.p)throw ORDER_ERR;

        pfield *temp = new pfield((v - b.v)%(int)p, p);
        return *temp;
    }

    pfield& operator -= (const pfield& b){
        if(p != b.p)throw ORDER_ERR;

        v = (v-b.v)%(int)p;
        return *this;
    }

    pfield& operator - (){
        v = -v;
        return *this;
    }

    pfield& operator + (){
        return *this;
    }

    pfield& inv(){
        v = ((int)std::pow(v, (int)(p-2))%(int)p);
        return *this;
    }

    pfield& operator * (const pfield& b)const{
        if(p != b.p)throw ORDER_ERR;

        pfield *temp = new pfield((v*b.v)%(int)p, p);
        return *temp;
    }

    pfield& operator *= (const pfield& b){
        if(p != b.p)throw ORDER_ERR;

        v = (v*b.v)%(int)p;
        return *this;
    }

    pfield& operator / (const pfield& b){
        if(p != b.p)throw ORDER_ERR;
        pfield *c = new pfield(b.v, b.p);

        pfield *temp = new pfield((v*(*c).inv().v)%(int)p, p);

        delete c;

        return *temp;
    }

    pfield& operator /= (const pfield& b){
        if(p != b.p)throw ORDER_ERR;
        pfield *c = new pfield(b.v, b.p);

        v = (v*(*c).inv().v)%(int)p;
        delete c;

        return *this;
    }

    friend std::ostream& operator << (std::ostream &stream, pfield& a){
        stream<<"["<<a.v<<"]";
        return stream;
    }

    friend std::istream& operator >> (std::istream &stream, pfield& a){
        stream>>a.v>>a.p;
        a.v=a.v%(int)a.p;
        return stream;
    }

private:
    size_t p{};
    int v{};

};

template <class T>
class vector{
public:
    vector(size_t _size = 0, const T& id = 0):size {_size}, data{new T[size]}{
        for(size_t i = 0; i < size; ++i)data[i] = id;
    }

    vector(const vector &v):size{v.size}, data{new T[size]}{
        for(size_t i = 0; i < size; ++i){
            data[i] = v[i];
        }
    }

    vector(const vector&& v): size{v.size}, data{v.data}{}

    ~vector(){delete [] data;}

    enum ERR_CODE{OUT_OF_RANGE, DIMENSION_ERR};

    T& operator [] (size_t i){return data[i];}
    const T& operator [](size_t i) const{return data[i];}

    T& operator () (size_t i){if(i>=size) throw OUT_OF_RANGE; return data[i];}
    const T& operator () (size_t i) const{if(i>=size) throw OUT_OF_RANGE; return data[i];}

    vector& operator = (const vector& v){
        if(this == &v) return *this;

        delete [] data;

        size = v.size;
        data = new T[size];
        for(size_t i = 0; i < size; ++i){
            data[i] = v[i];
        }
        return *this;
    }

    vector& operator = (const vector&& v){
        size = v.size;
        data = v.data;
        return *this;
    }

    bool operator == (const vector& v) const{
        if(this == &v) return true;
        if(size != v.size) return false;
        for(size_t i = 0; i<size; ++i){
            if(data[i] != v[i])return false;
        }
        return true;
    }

    bool operator != (const vector& v) const{
        return !(*this == v);
    }

    vector& operator + (const vector& v) const{
        if(size != v.size)throw DIMENSION_ERR;
        vector *temp = new vector(size);

        for(size_t i = 0; i < size; ++i){
            (*temp)[i] = data[i]+v[i];
        }
        return *temp;
    }

    vector& operator += (const vector& v){
        if(size != v.size)throw DIMENSION_ERR;

        for(size_t i = 0; i < size; ++i){
            data[i] += v[i];
        }
        return *this;
    }

    vector& operator *(const T& scalar) const{
        vector *temp = new vector(size);

        for(size_t i = 0; i < size; ++i){
            (*temp)[i] = data[i] * scalar;
        }
        return *temp;
    }

    vector& operator /(const T& scalar) const{
        vector *temp = new vector(size);

        for(size_t i = 0; i < size; ++i){
            (*temp)[i] = data[i] / scalar;
        }
        return *temp;
    }

    vector& operator *=(const T& scalar) const{

        for(size_t i = 0; i < size; ++i){
            data[i] *= scalar;
        }
        return *this;
    }

    vector& operator /=(const T& scalar) const{

        for(size_t i = 0; i < size; ++i){
            data[i] /= scalar;
        }
        return *this;
    }

    friend vector& operator *(const T& scalar, vector& v){
        vector *temp = new vector(v.size);

        for(size_t i = 0; i < v.size; ++i){
            (*temp)[i] = scalar * v[i];
        }
        return *temp;
    }

     std::complex<double>& operator *(const vector<std::complex<double>>& v)const{
        if(size != v.size)throw DIMENSION_ERR;
        std::complex<double>* scalar = new std::complex<double>;

        for(size_t i = 0; i < size; ++i){
            (*scalar) += data[i]*(std::conj(v[i]));
        }
        return *scalar;
     }

    double& operator *(const vector<double>& v)const{
        if(size != v.size)throw DIMENSION_ERR;
        double *scalar = new double;

        for(size_t i = 0; i < size; ++i){
            (*scalar) += data[i]*v[i];
        }
        return *scalar;
     }

     T norm(){
        return std::sqrt((*this)*(*this));
     }

      friend std::ostream& operator << (std::ostream &stream, vector& v){
        stream<<"[";
        for(size_t i = 0; i<v.size-1; ++i){
            stream<<v[i]<<", ";
        }
        stream<<v[v.size-1]<<"]";
        return stream;
    }

    friend std::istream& operator >> (std::istream &stream, vector& v){
        for(size_t i = 0; i < v.size; ++i){
            stream>>v[i];
        }
        return stream;
    }

private:
    size_t size;
    T *data;
};

#endif // LINEAR_SPACE_H_INCLUDED
