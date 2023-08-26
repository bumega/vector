#pragma once
#include "Container.h"
#include "Exceptions.h"
// TODO: В данном файле должен быть реализован класс итератора.

template<class V>
class VectorIterator {
public:
	VectorIterator() : ptr(nullptr) {}
	explicit VectorIterator(V* el_p) : ptr(el_p){}
	VectorIterator(const VectorIterator& it_p) : ptr(it_p.ptr) {}
	~VectorIterator() {
		ptr = nullptr;
	}
	VectorIterator<V>& operator++ () {
		if (ptr) {
			ptr++;
			return *this;
		} else {
			throw BadIterator("Bad iterator in iterator++");
		}
	}
	VectorIterator<V>& operator++ (int) {
		if (ptr) {
			auto cur = *this;
			ptr++;
			return cur;
		} else {
			throw BadIterator("Bad iterator in iterator++");
		}
	}
	VectorIterator<V>& operator-- () {
		if (ptr) {
			ptr--;
			return *this;
		} else {
			throw BadIterator("Bad iterator in iterator--");
		}
	}
	VectorIterator<V>& operator-- (int) {
		if (ptr) {
			auto cur = *this;
			ptr--;
			return cur;
		} else {
			throw BadIterator("Bad iterator in iterator--");
		}
	}
	V& operator*() {
		if (ptr) {
			return *ptr;
		} else {
			throw BadIterator("Bad iterator in iterator*");
		}
	}
	VectorIterator<V>& operator=(const VectorIterator<V>& it_p) {
		ptr = it_p.ptr;
		return *this;
	}
	VectorIterator<V> operator+(int num_p) {
		VectorIterator<V> curr(ptr + num_p);
		return curr;
	}
	VectorIterator<V> operator-(int num_p) {
		VectorIterator<V> curr(ptr - num_p);
		return curr;
	}
	bool operator==(const VectorIterator<V>& it_p) {
		return ptr == it_p.ptr;
	}
	bool operator!=(const VectorIterator<V>& it_p) {
		return ptr != it_p.ptr;
	}
	bool operator<(const VectorIterator<V>& it_p) {
		return ptr < it_p.ptr;
	}
	bool operator>(const VectorIterator<V>& it_p) {
		return ptr > it_p.ptr;
	}
	bool operator<=(const VectorIterator<V>& it_p) {
		return ptr <= it_p.ptr;
	}
	bool operator>=(const VectorIterator<V>& it_p) {
		return ptr >= it_p.ptr;
	}
	V* operator->() const noexcept {
		return ptr;
	}
	V& operator[](size_t i) {
		if (i < 0) {
			return *(ptr + i);
		} else {
			throw OutOfRangeException("Out of range exception i < 0 in iterator[]");
		}
	}
private:
	V* ptr;

};