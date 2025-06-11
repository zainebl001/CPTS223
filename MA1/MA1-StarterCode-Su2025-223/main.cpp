#include <iostream>
#include "BST.h" 
using namespace std;

/* 
1. The move constructor moves the ownership of an object's resources to a new object, leaving the object in an empty state, this does not copy memory.
2. The move assignment operator is used when assigning to an existing object. This deletes what is currently contained, takes the resources from the source, and make the source null.

BST::empty()		O(1), checks if root is the nullptr
BST::add()		O(n), if tree is unbalanced
BST::makeEmpty()	O(n), Deletes each node recursively
BST::printLevelOrder()	O(n), visits each node once
BST::cloneTree()	O(n), copies each node recursively
*/

int main()
{
	
	return 0;
}
