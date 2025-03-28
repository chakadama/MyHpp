#include <iostream>

#include "MyVector.hpp"
#include "MyList.hpp"

static void vectorTest() {
	MyVector<int> v1;
	v1.pushBack(3);
	v1.pushBack(4);
	v1.pushBack(5);
	v1.printVector();

	v1.insertData(22, 0);
	v1.insertData(71, 1);
	v1.insertData(77, 3);
	v1.printVector();
	//v1.MaopaoSort();
	v1.quickSort();
	v1.printVector();

	v1.deleteTail();
	v1.deleteData(0);
	v1.printVector();

	v1.revise(0, 45);
	v1.revise(1, 0);
	v1.printVector();

	v1.MaopaoSort();
	v1.printVector();

	std::cout << std::endl;
}

static void listTest() {
	MyList<int> L1(5);
	L1.insertHead(2);
	L1.insertHead(1);
	L1.insertTail(8);
	L1.printList();

	L1.insertData(3, 1);
	L1.printList();
	L1.insertData(7, 5);
	L1.printList();

	L1.deleteData(0);
	L1.printList();
	L1.deleteData(1);
	L1.printList();
}

int main() {
	//vectorTest();
	//listTest();

	return 0;
}