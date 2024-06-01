#include "bst.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Node :: Node(const string& data) : data(data), height(1), size(1), left(nullptr), right(nullptr) {}

Tree :: Tree() : root(nullptr) {}



int Tree :: getHeight(Node* node) {
	if (node == nullptr) return 0;
	
	return node->height;
}

int Tree :: getBalance(Node* node) {
	if (node == NULL) return 0;
	
	return getHeight(node->left) - getHeight(node->right);
}

int Tree :: getSize(Node* node) {
	if (node == NULL) return 0;
	return node->size;
}

Node* Tree :: rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

	y->size = getSize(y->left) + getSize(y->right) + 1;
	x->size = getSize(x->left) + getSize(x->right) + 1;

	return x;
}

Node* Tree :: leftRotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	x->size = getSize(x->left) + getSize(x->right) + 1;
	y->size = getSize(y->left) + getSize(y->right) + 1;

	return y;
}

Node* Tree :: AVLinsert(Node* node, const string& data) {
	if (node == nullptr) return new Node(data);

	if (data < node->data) {
		node->left = AVLinsert(node->left, data);
	} else if (data > node->data) {
		node->right = AVLinsert(node->right, data);
	} else {
		return node;
	}

	node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

	node->size = getSize(node->left) + getSize(node->right) + 1;
	
	int balance = getBalance(node);

	if (balance > 1 && data < node->left->data) {
		return rightRotate(node);

	} else if (balance < -1 && data > node->right->data) {
		return leftRotate(node);

	} else if (balance > 1 && data > node->left->data) {
		node->left = leftRotate(node->left);
		return rightRotate(node);

	} else if (balance < -1 && data < node->right->data) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}



int wordRangeUtil(Node* root, string start, string end) {
	if (root == NULL) return 0;

	if (root->data > end)
		return wordRangeUtil(root->left, start, end);
	
	else if (root->data < start)
		return wordRangeUtil(root->right, start, end);
	
	else {
		int numL = 0, numR = 0;

		if (root->left != NULL && root->left->data >= start) {
			numL = root->left->size;
		} else {
			numL = wordRangeUtil(root->left, start, end);
		}

		if (root->right != NULL && root->right->data <= end) {
			numR = root->right->size;
		} else {
			numR = wordRangeUtil(root->right, start, end);
		}

		return numL + numR + 1;
	}
}

int Tree :: wordRange(const string& start, const string& end) {
	return wordRangeUtil(root, start, end);
}



void Tree :: printTree(Node* root, int space) {
	if (root == NULL) return;

	space += 10;

	printTree(root->right, space);

	cout << endl;
	for (int i = 10; i < space; i++) cout << " ";
	cout << root->data << "\n";

	printTree(root->left, space);
}
