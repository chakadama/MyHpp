#pragma once
#include <iostream>

template <typename T>
struct TreeNode {
	T val;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightChild;

	TreeNode() : val(0), leftChild(nullptr), rightChild(nullptr) {}
	TreeNode(T x) : val(x), leftChild(nullptr), rightChild(nullptr) {}
	TreeNode(T x, TreeNode<T>* leftChild, TreeNode<T>* rightChild) 
		: val(x), leftChild(leftChild), rightChild(rightChild) {}
};

template <typename T>
class MyTree {
private:
	size_t size;
	TreeNode<T>* root;

public:
	MyTree() : size(0), root(nullptr){}
	MyTree(T val);
	~MyTree();

};

template<typename T>
inline MyTree<T>::MyTree(T val)
{
	size++;
	TreeNode<T>* newNode = new TreeNode<T>(val);
	root->leftChild = newNode;
	root->rightChild = nullptr;
}

template<typename T>
inline MyTree<T>::~MyTree()
{
}
