#ifndef BST_H
#define BST_H

#include <string>
using namespace std;
class Node {
	public:
		string data;
		int height;
		int size;
		Node* left;
		Node* right;

		Node(const string& data);
};

class Tree {
	public:
		Node* root;
		Tree();

		int getHeight(Node*);
		int getBalance(Node*);
		int getSize(Node*);
		
		Node* rightRotate(Node*);
		Node* leftRotate(Node*);

		Node* AVLinsert(Node*, const string&);

		int wordRange(const string&, const string&);

		void printTree(Node*, int);
};

#endif
