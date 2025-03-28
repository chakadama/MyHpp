#pragma once
#include <iostream>

template <typename T>
struct ListNode {
	T val;
	ListNode<T>* next;
	ListNode<T>* prev;
	ListNode() : val(0), next(nullptr) ,prev(nullptr) {}
	ListNode(T x) : val(x), next(nullptr), prev(nullptr) {}
	ListNode(T x, ListNode<T>* next, ListNode<T>* prev) : val(x), next(next), prev(prev) {}
};

template <typename T>
class MyList {
private:
	size_t size;
	ListNode<T>* head;
	ListNode<T>* tail;

public:
	MyList() : size(0), head(nullptr), tail(nullptr){}
	MyList(T data);
	~MyList();
	size_t getSize();

	void insertHead(T newData); // 头插
	void insertTail(T newData); // 尾插
	void insertData(T newData, size_t location);// 指定位置插入数据
	void deleteHead();
	void deleteTail();
	void deleteData(size_t location);
	void printList();
	T getData(size_t location);
};

template<typename T>
inline MyList<T>::MyList(T data)
{
	size = 1;
	ListNode<T>* newNode = new ListNode<T>(data);
	newNode->val = data;
	head = newNode;
	tail = newNode;
}

template<typename T>
inline MyList<T>::~MyList()
{
	size = 0;
	ListNode<T>* current = head;
	while (current != nullptr) {
		ListNode<T>* next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
inline size_t MyList<T>::getSize()
{
	return this->size;
}

template<typename T>
inline void MyList<T>::insertHead(T newData)
{
	size++;
	ListNode<T>* newNode = new ListNode<T>(newData);
	newNode->next = head;
	head->prev = newNode;
	head = newNode;
}

template<typename T>
inline void MyList<T>::insertTail(T newData)
{
	size++;
	ListNode<T>* newNode = new ListNode<T>(newData);
	newNode->prev = tail;
	tail->next = newNode;
	tail = newNode;
}

template<typename T>
inline void MyList<T>::insertData(T newData, size_t location)
{
	if (location > size || location < 0) {
		std::cout << "location out of size!" << std::endl;
	}
	else if (size == location) {
		insertTail(newData);
	}
	else if (0 == location) {
		insertHead(newData);
	}
	else {
		size++;
		ListNode<T>* p = head;
		for (size_t i = 0; i < location; i++) {
			p = p->next;
		}
		ListNode<T>* newNode = new ListNode<T>(newData);
		newNode->next = p;
		newNode->prev = p->prev;
		p->prev->next = newNode;
		p->prev = newNode;
	}
}

template<typename T>
inline void MyList<T>::deleteHead()
{
	size--;
	ListNode<T>* p = head;
	head = head->next;
	head->prev = nullptr;
	delete p;
}

template<typename T>
inline void MyList<T>::deleteTail()
{
	size--;
	ListNode<T>* p = tail;
	tail = tail->prev;
	tail->next = nullptr;
	delete p;
}

template<typename T>
inline void MyList<T>::deleteData(size_t location)
{
	if (location < 0 || location > size) {
		std::cout << "Location out of size" << std::endl;
	}
	else if (location == size) {
		deleteTail();
	}
	else if (0 == location) {
		deleteHead();
	}
	else {
		size--;
		ListNode<T>* p = head;
		for (size_t i = 0; i < location; i++) {
			p = p->next;
		}
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
	}
}

template<typename T>
inline void MyList<T>::printList()
{
	ListNode<T>* p = head;
	while (p != nullptr) {
		std::cout << p->val << " ";
		p = p->next;
	}
	std::cout << std::endl;
}

template<typename T>
inline T MyList<T>::getData(size_t location)
{
	return T();
}
