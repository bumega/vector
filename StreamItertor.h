#pragma once
#include <iostream>
template<typename T>
class StreamIterator {
public:
	StreamIterator(std::ostream& stream) : stream(stream), sep('\n'){}
	StreamIterator(std::ostream& stream, char c) : stream(stream), sep(c) {}
	~StreamIterator() = default;
	StreamIterator& operator=(const T& value) {
		stream << value;
		stream << sep;
		return *this;
	}
	StreamIterator& operator++() {
		return *this;
	}
	StreamIterator& operator++(int) {
		return *this;
	}
	StreamIterator& operator--() {
		return *this;
	}
	StreamIterator& operator--(int) {
		return *this;
	}
	StreamIterator& operator*() {
		return *this;
	}
private:
	std::ostream& stream;
	char sep;
};