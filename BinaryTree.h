#pragma once

class BinaryTree {
public:
	BinaryTree() {
		root = 0;
	}
	~BinaryTree() {
		if (root != 0)
			delete root;
	}
	void addInt(int newData);
	void print();
	void delInt(int deldata);
	
private:
	struct Node {
		Node(int _data,Node* _parent=0): 
			data(_data),
			leftChild(0),
			rightChild(0),
			parent(_parent) {}
		~Node() {
			if (leftChild != 0)
				delete leftChild;
			if (rightChild != 0)
				delete rightChild;
		}


		Node* leftChild;
		Node* rightChild;
		Node* parent;
		int data;
	};
	Node* findNodeByData(int finddata);
	Node* root;

};