#include "BinaryTree.h"
#include <iostream>
using namespace std;
int main() {
	BinaryTree btree;

	btree.addInt(5);
	btree.addInt(4);
	btree.addInt(20);
	btree.addInt(35);
	btree.addInt(1);
	btree.addInt(6);
	btree.addInt(-3);
	btree.addInt(-23);
	btree.addInt(13);
	

	btree.print();
}