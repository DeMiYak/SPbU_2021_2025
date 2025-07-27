#pragma once
#include<iostream>
//
//template<typename T>
//class myvector {
//public:
//	myvector() : len(0), vec(new T[0]) {};
//	myvector(size_t _len) : len(_len), vec(new T[_len]) {};
//	myvector(myvector<T> _vec) : myvector(_vec.len) {
//		std::swap(vec, _vec.vec);
//	}
//	myvector(const myvector<T>& _vec): myvector(_vec.len) {
//		for (int i = 0; i < len; i++) {
//			vec[i] = _vec.vec[i];
//		}
//	}
//	myvector(myvector<T>&& _vec) : myvector(_vec.len) {
//		std::swap(vec, _vec.vec);
//	}
//
//	void push_back(T value);
//
//	T back() const;
//
//	size_t size() const { return len }
//private:
//	T* vec;
//	size_t len;
//};