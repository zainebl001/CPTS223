#ifndef AVL_MAP_HPP
#define AVL_MAP_HPP

#include <iostream>
#include <stack>

template <typename Key, typename Value>
class avl_map
{
private:
	struct Node 
	{
		Key key;
		Value value;
		int height;
		Node* left;
		Node* right;
		Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
	};

	Node* root = nullptr;

	int getHeight(Node* n);
	int getBalance(Node* n);
	Node* rotateLeft(Node* x);
	Node* rotateRight(Node* y);
	Node* insert(Node* node, const Key& key, const Value& value);
	Node* erase(Node* node, const Key& key);
	Node* find(Node* node, const Key& key) const;
	void destroy(Node* node);
public:
	alv_map() = default;
	~avl_map() { destroy(root); }

	void insert(const Key& key, const Value& value);
	void erase(const Key& key);
	class iterator
	{
	public:
		iterator(Node* root);
		bool hasNext();
		std::pair<Key, Value> next();
	private:
		std::stack<Node*> stack;
		void pushLeft(Node* node);
	};
	iterator find(const Key& key);
};

#endif
