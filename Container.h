#pragma once
#include "Exceptions.h"
#include "Iterator.h"
#include <initializer_list>

// TODO: В данном файле должен быть реализован шаблонный класс контейнера.
//       В отличие от обычных классов, реализацию шаблонных классов нельзя разбить на .h и .cpp файлы.
//       Поэтому все методы реализуются непосредственно внутри шаблонного класса.

template<class T>
class Vector {
	
public:
	using iterator = VectorIterator<T>;

	iterator begin() {
		return iterator(arr);
	}
	iterator end() {
		return iterator(arr + size);
	}

	//конструктор по умолчанию
	Vector() : size(0), capacity(0), arr(nullptr) {}
	//конструктор с размером
	explicit Vector(size_t size_p) : size(0), capacity(size_p) {
		arr = new T[capacity];
	}
	//конструктор по значению
	Vector(size_t size_p, const T& el_p) : size(size_p), capacity(size_p * 2) {
		arr = new T[capacity];
		for (size_t i = 0; i < size; ++i) {
			arr[i] = el_p;
		}
	}
	//констркутор принамабщий [beg, end]
	template<class _Iter>
	Vector(_Iter beg_p, _Iter end_p) {
		size = 0;
		for (auto i = beg_p; i != end_p; ++i) {
			size++;
		}
		capacity = size * 2;
		arr = new T[capacity];
		size_t i = 0;
		for (auto el = beg_p;	el != end_p; ++el) {
			arr[i] = *el;
			i++;
		}
	}
	//конструктор принимабщий initilazer_list
	Vector(const std::initializer_list<T> &list_p) {
		size = list_p.size();
		capacity = size * 2;
		size_t i = 0;
		arr = new T[capacity];
		for (auto el : list_p) {
			arr[i] = el;
			i++;
		}
	}
	//конструктор копирования
	Vector(const Vector& vec_p) : size(vec_p.size), capacity(vec_p.capacity) {
		arr = new T[capacity];
		for (size_t i = 0; i < size; ++i) {
			arr[i] = vec_p[i];
		}
	}
	//конструктор перемещения
	Vector(Vector&& vec_p) : size(std::move(vec_p.size)), capacity(std::move(vec_p.capacity)), arr(std::move(vec_p.arr)) {}
	//деструктор
	~Vector() {
		delete[] arr;
		arr = nullptr;
		size = 0;
		capacity = 0;
	}
	//присваивание с копированием
	Vector operator= (const Vector& vec_p) {
		size = vec_p.size;
		capacity = vec_p.capacity;
		for (size_t i = 0; i < size; ++i) {
			arr[i] = vec_p[i];
		}
		return *this;
	}
	//присваивание с переносом
	Vector operator= (const Vector&& vec_p) {
		size = vec_p.size;
		capacity = vec_p.capacity;
		arr = std::move(vec_p.arr);
		return *this;
	}
	T& operator[](const size_t i) {
		return arr[i];
	}
	//безопасный []
	T& at(const size_t i) {
		if (i < size) {
			return arr[i];
		}
		else {
			throw OutOfRangeException("out of range exception in method Vector::at");
		}
	}
	//аллокатор
	void reserve(size_t num) {
		if (num < 0) {
			throw BadAllocException("Bad alloc in method Vector::reserve");
		}
		else if (num <= capacity) {
			T* new_arr = new T[num];
			size = num;
			capacity = num;
			for (size_t i = 0; i < size; ++i) {
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			new_arr = nullptr;
		}
		else {
			//std::cout << "\n\n " << num << " " << size << " " << capacity << "\n";
			T* new_arr = new T[num];
			capacity = num;
			for (size_t i = 0; i < size; ++i) {
				new_arr[i] = arr[i];
			}
			/*for (size_t i = size; i < capacity; ++i) {
				new_arr[i] = T();
			}*/
			delete[] arr;
			arr = new_arr;
			new_arr = nullptr;
		}
	}
	//аллокатор обновляющий итератор
	void reserve(size_t num, iterator& it_p) {
		if (num < 0) {
			throw BadAllocException("Bad alloc in method Vector::reserve");
		}
		else if (num <= capacity) {
			T* new_arr = new T[num];
			size = num;
			capacity = num;
			int k = 0;
			for (auto i = begin(); i != end(); ++i) {
				new_arr[k] = *i;
				if (i == it_p) {
					it_p = iterator((new_arr + k));

				}
				k++;
			}
			delete[] arr;
			arr = new_arr;
			new_arr = nullptr;
		}
		else {
			//std::cout << "\n\n " << num << " " << size << " " << capacity << "\n";
			T* new_arr = new T[num];
			capacity = num;
			int k = 0;
			for (auto i = begin(); i != end(); ++i) {
				new_arr[k] = *i;
				if (i == it_p) {
					it_p = iterator((new_arr + k));
					
				}
				k++;
			}
			delete[] arr;
			arr = new_arr;
			new_arr = nullptr;
		}
	}
	//добавлкение элемента в конец
	void pushBeck(const T& elem) {
		if (size == capacity and size != 0) {
			reserve(size*2);
		}
		if (capacity == 0) {
			reserve(1);
		}
		if (size == 0) {
			arr[0] = elem;
			size++;
		} else {
			size++;
			arr[size - 1] = elem;
		}
	}
	//удаление посоеднего элемента
	void popBack() {
		if (capacity == 0) {
			throw EmptyContainerException("container of vector is empty Vector::popBack");
		}
		arr[size] = T();
		size--;
	}
	//втавка элемента
	iterator insert(iterator pos, const T& el_p) {
		if (capacity == 0) {
			reserve(1, pos);
		}
		 else if (size == capacity) {
			reserve(capacity * 2, pos);
		}
		for (auto el = end(); el != pos; el--) {
			*el = *(el - 1);
		}
		*pos = el_p;
		size++;
		return pos;
	}
	 //вставка элемента с семантикой перемещения
	iterator insert(iterator pos, const T&& el_p) {
		if (capacity == 0) {
			reserve(1);
		}
		else if (size == capacity) {
			reserve(size * 2);
		}
		for (auto i = end(); i > pos; i--) {
			*i = *(i - 1);
		}
		size++;
		*pos = std::move(el_p);
		return pos;
	}
	// удаление элемента
	iterator erase(iterator pos) {
		for (auto el = pos; el < end()-1; ++el) {
			*(el) = *(el + 1);
		}
		size--;
		return pos;
	}
	//изменение размера массива
	void resize(size_t num) {
		if (num < 0) {
			throw BadAllocException("bad alloc Vector::resize");
		}
		else if (num <= size) {
			for (int i = num; i < size; ++i) {
				arr[i] = T();
			}
			size = num;
		}
		else {
			reserve(num * 2);
			for (int i = size; i < num; ++i) {
				arr[i] = T();
			}
			size = num;
		}
	}
	//проверка на пустоту
	bool empty() {
		return size == 0;
	}
	//гетер размера
	size_t Size() const {
		return size;
	}
	//гетер размерности
	size_t Capacity() const {
		return capacity;
	}
	//очищение
	void clear() {
		for (size_t i = 0; i < size; ++i) {
			arr[i] = T();
		}
		reserve(0);
		size = 0;
		capacity = 0;
	}
	//втсавка другого контейнера элементов
	iterator insert(iterator pos_p, iterator beg_p, iterator end_p) {
		for (auto el = beg_p; el < end_p; ++el) {
			insert(pos_p, *el);
		}
		return pos_p;
	}

private:
	T* arr;
	size_t size;
	size_t capacity;
};

