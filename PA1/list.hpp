#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include <iostream>

template <typename T>
class List {
private:
	Node<T>* head;
	int size;

public:
	List();
	List(const List<T>& other);
	~List();

	List<T>& operator=(const List<T>& other);

	void insertAtFront(const T& data);
	void insertAtBack(const T& data);
	bool removeNode(const T& data);
	Node<T>* findNode(const T& data);

	bool isEmpty() const;
	int getSize() const;
	void clear();
	void display() const;

	Node<T>* getHead() const;
	T getDataAtIndex(int index) const;

	bool contains(const T& data) const;
};

template <typename T>
List<T>::List()
{
	head = nullptr;
	size = 0;
}

template <typename T>
List<T>::List(const List<T>&other)
{
	head = nullptr;
	size = 0;

	Node<T>* current = other.head;
	while (current != nullptr)
	{
		insertAtBack(current->getData());
		current = current->getNext();
	}
}

template <typename T>
List<T>::~List()
{
	clear();
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this != &other)
	{
		clear();

		Node<T>* current = other.head;
		while (current != nullptr)
		{
			insertAtBack(current->getData());
			current = current->getNext();
		}
	}
	return *this;
}

template <typename T>
void List<T>::insertAtFront(const T& data)
{
	Node<T>* newNode = new Node<T>(data, head);
	head = newNode;
	size++;
}

template <typename T>
void List<T>::insertAtBack(const T& data)
{
	Node<T>* newNode = new Node<T>(data);

	if (head == nullptr)
	{
		head = newNode;
	}
	else
	{
		Node<T>* current = head;
		while (current->getNext() != nullptr)
		{
			current = current->getNext();
		}
		current->setNext(newNode);
	}
	size++;
}

template <typename T>
bool List<T>::removeNode(const T& data)
{
	if (head == nullptr)
	{
		return false;
	}

	if (head->getData() == data)
	{
		Node<T>* temp = head;
		head = head->getNext();
		delete temp;
		size--;
		return true;
	}

	Node<T>* current = head;
	while (current->getNext() != nullptr)
	{
		if (current->getNext()->getData() == data)
		{
			Node<T>* temp = current->getNext();
			current->setNext(temp->getNext());
			delete temp;
			size--;
			return true;
		}
		current = current->getNext();
	}

	return false;
}

template <typename T>
Node<T>* List<T>::findNode(const T& data)
{
	Node<T>* current = head;
	while (current != nullptr)
	{
		if (current->getData() == data)
		{
			return current;
		}
		current = current->getNext();
	}
	return nullptr;
}

template <typename T>
bool List<T>::isEmpty() const
{
	return head == nullptr;
}

template <typename T>
int List<T>::getSize() const
{
	return size;
}

template <typename T>
void List<T>::clear()
{
	while (head != nullptr)
	{
		Node<T>* temp = head;
		head = head->getNext();
		delete temp;
	}
	size = 0;
}

template <typename T>
void List<T>::display() const
{
	Node<T>* current = head;
	while (current != nullptr)
	{
		std::cout << current->getData() << " ";
		current = current->getNext();
	}
	std::cout << std::endl;
}

template <typename T>
Node<T>* List<T>::getHead() const
{
	return head;
}

template <typename T>
T List<T>::getDataAtIndex(int index) const
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Index out of range");
	}

	Node<T>* current = head;
	for (int i = 0; i < index; i++)
	{
		current = current->getNext();
	}

	return current->getData();
}

template <typename T>
bool List<T>::contains(const T& data) const
{
	return findNode(data) != nullptr;
}

#endif
