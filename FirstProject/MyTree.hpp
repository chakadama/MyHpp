#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
struct TreeNode {
	T val;
	size_t height;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightChild;

	TreeNode() : val(0), height(0), leftChild(nullptr), rightChild(nullptr) {}
	TreeNode(T x) : val(x), height(1), leftChild(nullptr), rightChild(nullptr) {}
};

template <typename T>
class MyTree {
private:
	size_t size;
	TreeNode<T>* root;

	// 获取节点高度
	size_t getHeight(TreeNode<T>* node)const;
	// 更新节点高度
	void updateHeight(TreeNode<T>* node);
	// 获取平衡因子
	size_t getBalanceFactor(TreeNode<T>* node);
	// 右旋
	TreeNode<T>* rightRotate(TreeNode<T>* y);
	// 左旋
	TreeNode<T>* leftRotate(TreeNode<T>* x);
	// 平衡节点
	TreeNode<T>* balance(TreeNode<T>* node);
	// 插入节点辅助函数
	TreeNode<T>* insertHelper(TreeNode<T>* node, T val);
	// 找到最小值节点
	TreeNode<T>* findMin(TreeNode<T>* node);
	// 删除节点辅助函数
	TreeNode<T>* deleteHelper(TreeNode<T>* node, T val);
	// 中序遍历辅助函数
	void inOrderHelper(TreeNode<T>* node)const;
	// 销毁树
	void destroyTree(TreeNode<T>* node);

public:
	MyTree() : size(0), root(nullptr) {}
	~MyTree();

	// 插入
	void insert(T val);
	// 删除
	void remove(T val);
	// 查找
	bool contains(T val)const;
	// 中序遍历
	void inOrderTraversal()const;
	// 获取树的高度
	size_t height()const;
};

template<typename T>
inline size_t MyTree<T>::getHeight(TreeNode<T>* node)const
{
	return node ? node->height : 0;
}

template<typename T>
inline void MyTree<T>::updateHeight(TreeNode<T>* node)
{
	if (node) {
		node->height = 1 + std::max(getHeight(node->leftChild), getHeight(node->rightChild));
	}
}

template<typename T>
inline size_t MyTree<T>::getBalanceFactor(TreeNode<T>* node)
{
	return node ? getHeight(node->leftChild) - getHeight(node->rightChild) : 0;
}

template<typename T>
inline TreeNode<T>* MyTree<T>::rightRotate(TreeNode<T>* y)
{
	TreeNode<T>* x = y->leftChild;
	TreeNode<T>* T2 = x->rightChild;

	x->rightChild = y;
	y->leftChild = T2;
	updateHeight(y);
	updateHeight(x);
	return x;
}

template<typename T>
inline TreeNode<T>* MyTree<T>::leftRotate(TreeNode<T>* x)
{
	TreeNode<T>* y = x->rightChild;
	TreeNode<T>* T2 = y->leftChild;

	y->leftChild = x;
	x->rightChild = T2;
	updateHeight(x);
	updateHeight(y);
	return y;
}

template<typename T>
inline TreeNode<T>* MyTree<T>::balance(TreeNode<T>* node)
{
	if (!node) {
		return nullptr;
	}
	updateHeight(node);

	int balanceFactor = getBalanceFactor(node);
	if (balanceFactor > 1 && getBalanceFactor(node->leftChild) >= 0) {
		// LL
		return rightRotate(node);
	}
	else if (balanceFactor < -1 && getBalanceFactor(node->rightChild) <= 0) {
		// RR
		return leftRotate(node);
	}
	else if (balanceFactor > 1 && getBalanceFactor(node->leftChild) < 0) {
		// LR，先左旋再右旋
		node->leftChild = leftRotate(node->leftChild);
		return rightRotate(node);
	}
	else if (balanceFactor < -1 && getBalanceFactor(node->rightChild) > 0) {
		// RL，先右旋再左旋
		node->rightChild = rightRotate(node->rightChild);
		return leftRotate(node);
	}
	else {
		// 已经平衡
		return node;
	}
}

template<typename T>
inline TreeNode<T>* MyTree<T>::insertHelper(TreeNode<T>* node, T val)
{
	if (!node) {
		return new TreeNode<T>(val);
	}
	if (val < node->val) {
		node->leftChild = insertHelper(node->leftChild, val);
	}
	else if (val > node->val) {
		node->rightChild = insertHelper(node->rightChild, val);
	}
	else {
		// 重复值
		return node;
	}
	return balance(node);
}

template<typename T>
inline TreeNode<T>* MyTree<T>::findMin(TreeNode<T>* node)
{
	while (node && node->leftChild) {
		node = node->leftChild;
	}
	return node;
}

template<typename T>
inline TreeNode<T>* MyTree<T>::deleteHelper(TreeNode<T>* node, T val)
{
	if (!node) {
		return nullptr;
	}
	if (val < node->val) {
		node->leftChild = deleteHelper(node->leftChild, val);
	}
	else if (val > node->val) {
		node->rightChild = deleteHelper(node->rightChild, val);
	}
	else {
		// 需要删除的节点
		if (!node->leftChild || !node->rightChild) {
			TreeNode<T>* temp = node->leftChild ? node->leftChild : node->rightChild;

			// 无子节点
			if (!temp) {
				temp = node;
				node = nullptr;
			}
			else {
				// 一个子节点
				*node = *temp; // 用子节点内容覆盖当前节点
			}

			delete temp;
		}
		else {
			// 两个子节点
			TreeNode<T>* temp = findMin(node->rightChild);
			node->val = temp->val;
			node->rightChild = deleteHelper(node->rightChild, temp->val);
		}
	}
	// 树为空时
	if (!node) {
		return nullptr;
	}
	return balance(node);
}

template<typename T>
inline void MyTree<T>::inOrderHelper(TreeNode<T>* node) const
{
	if (node) {
		inOrderHelper(node->leftChild);
		std::cout << node->val << " ";
		inOrderHelper(node->rightChild);
	}
}

template<typename T>
inline void MyTree<T>::destroyTree(TreeNode<T>* node)
{
	if (node) {
		destroyTree(node->leftChild);
		destroyTree(node->rightChild);
		delete node;
	}
}

template<typename T>
inline MyTree<T>::~MyTree()
{
	destroyTree(root);
}

template<typename T>
inline void MyTree<T>::insert(T val)
{
	root = insertHelper(root, val);
}

template<typename T>
inline void MyTree<T>::remove(T val)
{
	root = deleteHelper(root, val);
}

template<typename T>
inline bool MyTree<T>::contains(T val) const
{
	TreeNode<T>* current = root;
	while (current) {
		if (val == current->val) {
			return true;
		}
		else if (val < current->val) {
			current = current->leftChild;
		}
		else {
			current = current->rightChild;
		}
	}
	return false;
}

template<typename T>
inline void MyTree<T>::inOrderTraversal() const
{
	inOrderHelper(root);
	std::cout << std::endl;
}

template<typename T>
inline size_t MyTree<T>::height() const
{
	return getHeight(root);
}