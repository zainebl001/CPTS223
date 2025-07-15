#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Product
{
	string uniqId;
	string productName;
	string category;
};

template<typename K, typename V>
class SimpleMap
{
private:
	static const int SIZE = 1000;
	struct Node
	{
		K key;
		V value;
		Node* next;
		Node(K k, V v) : key(k), value(v), next(nullptr) {}
	};
	Node* table[SIZE];

	int hashFunc(const K& key)
	{
		hash<K> hasher;
		return hasher(key) % SIZE;
	}
public:
	SimpleMap() { fill(begin(table), end(table), nullptr); }
	~SimpleMap()
	{
		for (int i = 0; i < SIZE; i++)
		{
			Node* curr = table[i];
			while (curr)
			{
				Node* temp = curr;
				curr = curr->next;
				delete temp;
			}
		}
	}

	void put(const K& key, const V& value)
	{
		int idx = hashFunc(key);
		Node* curr = table[idx];
		while (curr)
		{
			if (curr->key == key)
			{
				curr->value = value;
				return;
			}
			curr = curr->next;
		}
		Node* newNode = new Node(key, value);
		newNode->next = table[idx];
		table[idx] = newNode;
	}

	V* get(const K& key)
	{
		int idx = hashFunc(key);
		Node* curr = table[idx];
		while (curr)
		{
			if (curr->key == key) return &curr->value;
			curr = curr->next;
		}
		return nullptr;
	}
};

SimpleMap<string, Product> productMap;
vector<Product> allProducts;

void printHelp()
{
	cout << "List of commands: \n";
	cout << " 1. find <inventoryid>\n";
	cout << " 2. listInventory <category_string>\n";
	cout << "\n";
}

void loadCSV(const string& filename)
{
	ifstream file(filename);
	string line;
	getline(file, line);
	while (getline(file, line))
	{
		stringstream ss(line);
		string token;
		Product p;
		getline(ss, p.uniqId, ',');
		getline(ss, p.productName, ',');
		getline(ss, token, ',');
		getline(ss, token, ',');
		getline(ss, p.category, ',');
		if (p.category.empty()) p.category = "NA";
		allProducts.push_back(p);
		productMap.put(p.uniqId, p);
	}
	file.close();
}

void handleFind(const string& id)
{
	Product* p = productMap.get(id);
	if (p)
	{
		cout << "Product found:\n";
		cout << "ID: " << p->uniqId << endl;
		cout << "Name: " << p->productName << endl;
		cout << "Category: " << p->category << endl;
	}
	else
	{
		cout << "Inventory/Product not found\n";
	}
}

void handleListInventory(const string& category)
{
	bool found = false;
	for (const Product& p : allProducts)
	{
		if (p.category.find(category) != string::npos)
		{
			cout << p.uniqId << " | " << p.productName << endl;
			found = true;
		}
	}
	if (!found) cout << "Invalid Category" << endl;
}

void evalCommand(string line)
{
	if (line == ":help") printHelp();
	else if (line.rfind("find", 0) == 0)
	{
		string id = line.substr(5);
		handleFind(id);
	}
	else if (line.rfind("listInventory", 0) == 0)
	{
		string category = line.substr(14);
		handleListInventory(category);
	}
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    loadCSV("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
    cout << "\n> ";
}

int main(int argc, char const *argv[])
{
    string line;
    bootStrap();
    while (getline(cin, line) && line != ":quit")
    {
	if (line == ":quit") break;
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
