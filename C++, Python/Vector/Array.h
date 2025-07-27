#pragma once
#include<iostream>
#include<assert.h> // Temporary

// Homework
// Make for templates too and test on Main.cpp
template<typename T>
class array {
public:
	/// <summary>
	/// Creates an array of size
	/// and assigns value to all array elements
	/// </summary>
	explicit array(size_t size, T value);
	/// <summary>
	/// Creates an array of size
	/// and assigns zero to all array elements
	/// </summary>
	explicit array(size_t size);
	/// <summary>
	/// Creates a zero size array with nullptr
	/// </summary>
	array();
	/// <summary>
	/// Copy constructor
	/// </summary>
	array(const array<T>& a);

	array(array<T>&& a) : _block(std::move(a._block)), _size(std::move(a._size)) {};
	
	/// <summary>
	/// Add a
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="size"></param>
	/// <param name="value"></param>
	array<T>& operator+=(const array<T>& a);
	array<T>& operator=(const array<T>& a);

	void print() const;

	// Перезаполняет все элементы массива
	array<T>& refill();

	~array() {
		delete[] _block;
	}
private:
	T* _block;
	size_t _size;
};

template<typename T>
array<T>::array(size_t size, T value) : _size(size){
	if (!size) _block = nullptr;
	else {
		_block = new T[size];
		for (size_t i = 0; i < size; ++i) _block[i] = value;
	}
}

template<typename T>
array<T>::array(size_t size) : _size(size)
{
	if (!size) _block = nullptr;
	else _block = new T[size];
	for (size_t i = 0; i < size; ++i) {
		std::cin >> T(0);
	}
}

template<typename T>
array<T>::array() : _size(0), _block(nullptr){};

template<typename T>
array<T>::array(const array<T>& a) : _size(a._size){
	if (!_size) _block = nullptr;
	else {
		_block = new T[_size];
		for (size_t i = 0; i < _size; ++i) {
			_block[i] = a._block[i];
		}
	}
}

template<typename T>
array<T>& array<T>::operator=(const array<T>& a) {
	if (this != &a) {
		delete[] _block;
		_size = a._size;
		if (!_size) _block = nullptr;
		else {
			_block = new T[_size];
			for (size_t i = 0; i < _size; ++i) {
				_block[i] = a._block[i];
			}
		}
	}
	return *this;
}

template<typename T>
array<T>& array<T>::operator+=(const array<T>& a){
	assert(a._size == _size && _size && a._size, "Error: different or null sizes.\n");
	for (size_t i = 0; i < _size; ++i) {
		_block[i] += a._block[i];
	}
	return *this;
}

template<typename T>
array<T> operator+(const array<T>& a, const array<T>& b){
	array<T> c(a);
	return c += b;
}

template<typename T>
void array<T>::print() const{
	std::cout << "Size = " << _size << std::endl;
	std::cout << "Array = ";
	for (size_t i = 0; i < _size; ++i) {
		std::cout << _block[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
array<T>& array<T>::refill() {
	std::cout << "Current size = " << _size << std::endl;
	for (size_t i = 0; i < _size; ++i) {
		std::cin >> _block[i];
	}
	return *this;
}