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
void BinaryTree::delInt(int deldata)
{
    Node* curr = findNodeByData(deldata);//находим элемент в дереве, и назначаем его текущим

    if (curr) {
        Node* tmpLeft = nullptr;
        Node* tmpRight = nullptr;
        Node* p = curr->parent;// указатель на родительский узел удаляемого узла

        if (!curr->leftChild && !curr->rightChild)//если удаляемый узел лист
        {
            delete curr;
        }

        else if (curr->leftChild && !curr->rightChild)//если есть только левый дочерний узел
        {
            if (curr->parent == nullptr)//если удаляемый элемент корень
            {
                Node* max = curr->leftChild; // для поиска максимума в левом поддереве
                while (max->rightChild)//пока существует правый элемент,идем по правой части дерева
                {
                    if (max->rightChild != nullptr)//если правый элемент не равен nullptr, то идем по правой части дерева
                    {
                        max = max->rightChild;
                        continue;
                    }
                }

                curr->data = max->data;// назначаем удаляемому узлу max data, т.е. значение того узла, который должен быть на его месте

                // теперь нужно удалить узел max (т.к. его значение перешло в curr) и сбросить указатель rightChild для его родителя
                if (max->leftChild == nullptr)// если у  maxchild нет левого ребенка
                {
                    Node* p2 = max->parent;
                    p2->rightChild = nullptr;//зануляем правого ребенка, у родителя 
                    delete max;
                }
                else
                {
                    Node* p2 = max->parent;
                   // p2->leftChild = nullptr;
                    p2->rightChild = max->leftChild;
                    (max->leftChild)->parent = p2;
                    delete max;
                }
            }

            //случай если удаляемый элемент не корень, у него есть левый ребенок, но нет правого ребенка
            else if (curr->parent != nullptr && curr->leftChild != nullptr && curr->rightChild == nullptr)
            {
                tmpLeft = curr->leftChild;//сохраняем значение левого ребенка текущего элемента
                if (p->rightChild->data == deldata) //удаляемый узел является правым ребенком у своего родителя
                {
                    p->rightChild == tmpLeft;//присваиваем правому ребенку родителя удаляемой вершины левого ребенка   
                    tmpLeft->parent = p;//переназначаем родителя правого левого элемента 
                    delete curr;
                }
                if (p->leftChild->data == deldata) //удаляемый узел является левым ребенком у своего родителя
                {
                    p->leftChild == tmpLeft;
                    tmpLeft->parent = p;
                    delete curr;
                }       
            }
            else if (curr->parent != nullptr && curr->leftChild == nullptr && curr->rightChild != nullptr)
            {
                tmpRight = curr->rightChild;
                if (p->rightChild->data == deldata)//удаляемый узел является правым ребенком своего родителя
                {
                    p->rightChild = tmpRight;
                    tmpRight->parent = p;
                    delete curr;
                }
                if(p->leftChild->data=deldata)//удаляемый узел является левым ребенок своего родителя
                {
                    p->leftChild = tmpRight;
                    tmpRight->parent = p;
                    delete curr;
                }
                else if (curr->parent != nullptr && curr->leftChild != nullptr && curr->rightChild != nullptr)//если элемент не является корневым и у него есть 2 ребенка
                {
                    tmpLeft = curr->leftChild;
                    tmpRight = curr->rightChild;
                    if (p->leftChild->data == deldata&&p->rightChild==nullptr)//если в правом поддереве нет элементе нет детей
                    {
                        p->rightChild = tmpRight;
                        p->leftChild = tmpLeft;
                        tmpRight->parent = p;
                        tmpRight->parent = p;
                        delete curr;
                    }
                    else if (p->leftChild->data == deldata && p->rightChild != nullptr)//если удаляемое значение принадлжеит к левому дереву и в правом дереве есть ребенок
                    {
                        p->leftChild = tmpRight;

                        if (p->rightChild->data< tmpRight->data) //если правый ребенок больше чем правый у удаляемой вершины, то ничего не делаем
                        {
                            p->rightChild = tmpRight;
                            tmpRight->parent = p;
                            delete curr;
                        }
                    }
                    else if (p->rightChild->data == deldata && p->leftChild != nullptr) 
                    {
                        p->rightChild = tmpRight;
                        if (p->leftChild->data > tmpLeft->data) 
                        {
                            p->leftChild = tmpLeft;
                            tmpLeft->parent = p;
                            delete curr;
                        }

                    }
                }

            }
        }
        else if (!curr->leftChild && curr->rightChild)//если есть только правый дочерний узел
        {
            if (curr->parent == nullptr)//если удаляемый элемент корень
            {
                tmpRight = curr->rightChild;
                root = tmpRight;
                root->parent = nullptr;
                delete curr;
            }
            //если удаляемый элемент не корень
            tmpRight = curr->rightChild;
            p->rightChild = curr->rightChild;
            tmpRight->parent = p;
            delete curr;
        }

        else //если есть оба дочерних узла у удаляемого
        {
            Node* max = curr->leftChild; // для поиска максимума в левом поддереве
            while (max->rightChild)
            {
                if (max->rightChild != nullptr)
                {
                    max = max->rightChild;
                    continue;
                }
            }
            curr->data = max->data;// назначаем удаляемому узлу max data, т.е. значение того узла, который должен быть на его месте

            // теперь нужно удалить узел max (т.к. его значение перешло в curr) и сбросить указатель rightChild для его родителя
            if (max->leftChild == nullptr)
            {
                Node* p2 = max->parent;
                p2->rightChild = nullptr;
                delete max;
            }
            else
            {
                Node* p2 = max->parent;
                p2->leftChild = nullptr;
                p2->rightChild = max->leftChild;
                (max->leftChild)->parent = p2;
                delete max;
            }
        }
    }
}