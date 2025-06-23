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
	Node* minValueNode(Node* node);
	Node* find(Node* node, const Key& key) const;
	void destroy(Node* node);
public:
	avl_map() = default;
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

template <typename Key, typename Value>
int avl_map<Key, Value>::getHeight(Node* n)
{
	return n ? n->height : 0;
}

template <typename Key, typename Value>
int avl_map<Key, Value>::getBalance(Node* n)
{
	return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

template <typename Key, typename Value>
typename avl_map<Key, Value>::Node* avl_map<Key, Value>::rotateRight(Node* y)
{
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;
	y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
	x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

	return x;
}

template <typename Key, typename Value>
typename avl_map<Key, Value>::Node* avl_map<Key, Value>::rotateLeft(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;
	x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
	y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

	return y;
}

template <typename Key, typename Value>
typename avl_map<Key, Value>::Node* avl_map<Key, Value>::insert(Node* node, const Key& key, const Value& value)
{
	if (!node) return new Node(key, value);

	if (key < node->key) node->left = insert(node->left, key, value);
	else if (key > node->key) node->right = insert(node->right, key, value);
	else
	{
		node->value = value;
		return node;
	}

	node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
	int balance = getBalance(node);
	if (balance > 1 && key < node->left->key) return rotateRight(node);
	if (balance < -1 && key > node->right->key) return rotateLeft(node);
	if (balance > 1 && key > node->left->key)
	{
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	if (balance < -1 && key < node->right->key)
	{
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	return node;
}

template <typename Key, typename Value>
void avl_map<Key, Value>::insert(const Key& key, const Value& value)
{
	root = insert(root, key, value);
}

template <typename Key, typename Value>
typename avl_map<Key, Value>::Node* avl_map<Key, Value>::minValueNode(Node* node)
{
	Node* current = node;
	while (current->left) current = current->left;
	return current;
}

template <typename Key, typename Value>
typename avl_map<Key, Value>::Node* avl_map<Key, Value>::erase(Node* node, const Key& key)
{
	if (!node) return node;
	if (key < node->key) node->left = erase(node->left, key);
	else if (key > node->key) node->right = erase(node->right, key);
	else
	{
		if (!node->left || !node->right)
		{
			Node* temp = node->left ? node->left : node->right;
			if (!temp)
			{
				temp = node;
				node = nullptr;
			}
			else
			{
				*node = *temp;
			}
			delete temp;
		}
		else
		{
			Node* temp = minValueNode(node->right);
			node->key = temp->key;
			node->value = temp->value;
			node->right = erase(node->right, temp->key);
		}
	}

	if (!node) return node;
	node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
	int balance = getBalance(node);

	if (balance > 1 && getBalance(node->left) >= 0) return rotateRight(node);
	if (balance > 1 && getBalance(node->left) < 0)
	{
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	if (balance < -1 && getBalance(node->right) <= 0)
		return rotateLeft(node);

	if (balance < -1 && getBalance(node->right) > 0)
	{
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	return node;
}

template <typename Key, typename Value>
void avl_map<Key, Value>::erase(const Key& key)
{
	root = erase(root, key);
}

template <typename Key, typename Value>
typename avl_map<Key, Value>::Node* avl_map<Key, Value>::find(Node* node, const Key& key) const
{
	if (!node) return nullptr;
	if (key < node->key) return find(node->left, key);
	if (key > node->key) return find(node->right, key);
	return node;
}

template <typename Key, typename Value>
typename avl_map<Key, Value>::iterator avl_map<Key, Value>::find(const Key& key)
{
	return iterator(find(root, key));
}

template <typename Key, typename Value>
void avl_map<Key, Value>::destroy(Node* node)
{
	if (!node) return;
	destroy(node->left);
	destroy(node->right);
	delete node;
}

#endif
