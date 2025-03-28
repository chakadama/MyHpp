#pragma once
#include <iostream>

template <typename T>
class MyVector
{
private:
	T* data;
	int size;
	int capacity;

public:
	MyVector();
	MyVector(T newData);
	~MyVector();
	size_t getSize();

	void pushBack(T newData); // 尾插数据
	void insertData(T newData, size_t location); // 指定位置插入数据
	void deleteTail(); // 删除尾部数据
	void deleteData(size_t location); // 指定位置删除数据
	T getData(size_t order); // 查询指定位置数据
	void printVector();
	void revise(size_t location, T newData); // 修改指定位置数据

	void MaopaoSort(); // 冒泡排序

	size_t partition(MyVector<T>& myvector, size_t left, size_t right);
	void quickSort(MyVector<T>& myvector, size_t left, size_t right);
	void quickSort(); // 快速排序
};

template<typename T>
inline MyVector<T>::MyVector()
{
	size = 0;
	capacity = 1; // Initialize capacity to 1 to avoid zero capacity
	data = new T[capacity];
}

template<typename T>
inline MyVector<T>::MyVector(T newData)
{
	size = 1;
	capacity = 1;
	data = new T[capacity];
	data[0] = newData;
}

template<typename T>
inline MyVector<T>::~MyVector()
{
	std::cout << "MyVector 析构" << std::endl;
}

template<typename T>
inline size_t MyVector<T>::getSize()
{
	return this->size;
}

template<typename T>
inline void MyVector<T>::pushBack(T newData)
{
	if (size >= capacity) {
		capacity *= 2;
		T* newArray = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			newArray[i] = data[i];
		}
		delete[] data;
		data = newArray;
	}
	data[size] = newData;
	size++;
}

template<typename T>
inline void MyVector<T>::insertData(T newData, size_t location)
{
	if (location > size) {
		std::cout << "Over the size!" << std::endl;
		return;
	}
	if (size >= capacity) {
		capacity *= 2;
		T* newArray = new T[capacity];
		for (size_t i = 0; i < size; i++) {
			newArray[i] = data[i];
		}
		delete[] data;
		data = newArray;
	}
	for (size_t i = size; i > location; i--) {
		data[i] = data[i - 1];
	}
	data[location] = newData;
	size++;
}

template<typename T>
inline void MyVector<T>::deleteTail()
{
	size--;
}

template<typename T>
inline void MyVector<T>::deleteData(size_t location)
{
	for (size_t i = location; i < size; i++) {
		data[i] = data[i + 1];
	}
	size--;
}

template<typename T>
inline T MyVector<T>::getData(size_t order)
{
	if (order >= size) {
		std::cout << "Out of size!" << std::endl;
		return T();
	}
	return data[order];
}

template<typename T>
inline void MyVector<T>::printVector()
{
	for (size_t i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
inline void MyVector<T>::revise(size_t location, T newData)
{
	if (location >= size) {
		std::cout << "location > size" << std::endl;
		return;
	}
	data[location] = newData;
}

template<typename T>
inline void MyVector<T>::MaopaoSort()
{
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i + 1; j < size; j++) {
			if (data[i] > data[j]) {
				T mid = data[i];
				data[i] = data[j];
				data[j] = mid;
			}
		}
	}
}

template<typename T>
inline size_t MyVector<T>::partition(MyVector<T>& myvector, size_t left, size_t right)
{
	T pos = myvector.getData(left);
	while (left < right) {
		while (left < right && pos <= myvector.getData(right)) {
			right--;
		}
		myvector.revise(left, myvector.getData(right));
		while (left < right && pos >= myvector.getData(left)) {
			left++;
		}
		myvector.revise(right, myvector.getData(left));
	}
	myvector.revise(left, pos);
	return left;
}

template<typename T>
inline void MyVector<T>::quickSort(MyVector<T>& myvector, size_t left, size_t right) {
	if (left < right) {
		size_t pos = partition(myvector, left, right);
		quickSort(myvector, left, pos);
		quickSort(myvector, pos + 1, right);
	}
}

template<typename T>
inline void MyVector<T>::quickSort()
{
	quickSort(*this, 0, size - 1);
}