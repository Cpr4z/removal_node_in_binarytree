#include "BinaryTree.h"
#include <iostream>



void BinaryTree::addInt(int newData) {
	if (root == 0)
		root = new Node(newData);
	else {
		Node* current = root;
		Node* newNode = 0;
		while (newNode == 0) {
			if (current->data >= newData) {//если текущее число в Node больше чем новое число то идем по левой ветке
				
				if (current->leftChild != 0) {//если левый ребенок текущего элемента не пустой, то присваеваием текущему элементу левого ребенка
					current = current->leftChild;
					continue;
				}
				newNode = new Node(newData, current);//если нет левого ребенка, то создаем новую Node
				current->leftChild = newNode;
			}
			else//идем по правой ветке
			{
				if (current->rightChild != 0) {
					current = current->rightChild;
					continue;
				}
				else {
					newNode = new Node(newData, current);
					current->rightChild = newNode;
				}

			}
		}
	}
}
void BinaryTree::print() {
	Node* queue[100];

	int queueCounter = 0;

	queue[queueCounter++] = root;
	while(queueCounter!=0){
		Node* current = queue[0];
		
		queueCounter--;

		for (int i = 0; i < queueCounter; i++) {
			queue[i] = queue[i + 1];
		}


		if (current->parent)
			std::cout << current->parent->data;
		std::cout << " " << current->data << std::endl;
		if (current->leftChild)
			queue[queueCounter++] = current->leftChild;
		if (current->rightChild)
			queue[queueCounter++] = current->rightChild;
	
	}
}
BinaryTree::Node* BinaryTree::findNodeByData(int finddata)
{
    Node* curr = root;
    while (curr)//пока указатель на текущий элемент не равен nullptr
    {
        if (curr->data == finddata)//если текущее значение равно тому значению, которое ищем
        {
            return curr;
        }
        if (curr->data > finddata)//если текущее значение больше чем то значение, которое ищем, то идем в левое поддерево
        {
            curr = curr->leftChild;
        }
        else//если меньше, то идем в правое поддерево
        {
            curr = curr->rightChild;
        }
    }
    return nullptr;//если элемента нет, то возвращаем nullptr
}
// удаление элемента
BinaryTree::Node* BinaryTree::treeMax(Node* x) {
	while (x->rightChild != nullptr)
		x = x->rightChild;
	return x;
}
BinaryTree::Node* BinaryTree::treeMin(Node* y) {
	while (y->leftChild != nullptr)
		y = y->leftChild;
	return y;
}
void BinaryTree::TransPlant(Node* U, Node* V) {
	if (U->parent == nullptr) {
		root = V;
	}
	else if (U == U->parent->leftChild){
		U->parent->leftChild = V;
	}
	else {
		U->parent->rightChild = V;
	}
	if (V != nullptr)
		V->parent = U->parent;
}
void BinaryTree::delInt(int deldata)
{
	Node* curr = findNodeByData(deldata);//находим элемент в дереве, и назначаем его текущим
	if (curr->leftChild == nullptr)
		TransPlant(curr, curr->rightChild);
	else if (curr->rightChild == nullptr)
		TransPlant(curr, curr->leftChild);
	else {
		Node* y = treeMin(curr->rightChild);
		if (y->parent != curr) {
			y->rightChild = curr->rightChild;
			y->rightChild->parent = y;
		}
		TransPlant(curr, y);
		y->leftChild = curr->leftChild;
		y->leftChild->parent = y;
	}
}