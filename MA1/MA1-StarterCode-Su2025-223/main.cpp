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
	{
	cout << "Test 1 Level Order Print:" << endl;
	BST<int> tree;
	tree.add(10);
	tree.add(6);
	tree.add(15);
	tree.add(3);
	tree.add(7);
	cout << "Expected: 10 6 15 3 7" << endl;
	tree.printLevelOrder();
	cout << endl;
	}

	{
	cout << "Test 2 Copy Constructor:" << endl;
	BST<int> original;
	original.add(6);
	original.add(3);
	original.add(9);
	BST<int> copy(original);
	cout << "Original: ";
	original.printInOrder();
	cout << endl;
	cout << "Copy: ";
	copy.printInOrder();
	cout << endl;

	if (original.size() == copy.size())
	{
		cout << "Deep copy successful." << endl;
	}
	else
	{
		cout << "Deep copy failed." << endl;
	}
	cout << endl;
	}

	{
	cout << "Test 3 Copy Isolation:" << endl;
	BST<int> original;
	original.add(10);
	original.add(5);
	original.add(20);
	BST<int> copy(original);
	copy.add(64);
	cout << "Original: " << original.size() << endl;
	cout << "Copy: " << copy.size() << endl;
	if (original.size() != copy.size())
	{
		cout << "Pass." << endl;
	}
	else
	{
		cout << "Fail." << endl;
	}
	cout << endl;
	}

	{
	cout << "Test 4 Copy Assignment" << endl;
	BST<int> a;
	a.add(1);
	a.add(2);
	BST<int> b;
	b.add(10);
	b.add(20);
	b = a;

	cout << "A: ";
	a.printInOrder();
	cout << endl;
	cout << "B: ";
	b.printInOrder();
	cout << endl;

	if (b.size() == a.size())
	{
		cout << "Pass" << endl;
	}
	else
	{
		cout << "Fail" << endl;
	}
	cout << endl;
	}

	{
	cout << "Test 5 Move Constructor:" << endl;
	BST<int> temp;
	temp.add(100);
	temp.add(50);
	temp.add(150);
	BST<int> moved(move(temp));

	cout << "Tree moved: ";
	moved.printInOrder();
	cout << endl;
	cout << "Original tree size after move: " << temp.size() << endl;

	if (temp.empty())
	{
		cout << "Pass" << endl;
	}
	else
	{
		cout << "Fail" << endl;
	}
	cout << endl;
	}

	{
	cout << "Test 6 Move Assignment:" << endl;
	BST<int> a;
	a.add(1);
	a.add(2);
	BST<int> b;
	b.add(753);
	b = move(a);
	cout << "B: ";
	b.printInOrder();
	cout << endl;
	cout << "A size after move: " << a.size() << endl;

	if (a.empty())
	{
		cout << "Pass" << endl;
	}
	else
	{
		cout << "Fail" << endl;
	}
	cout << endl;
	}

 	return 0;
}
