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
	double sellingPrice = 0.0;
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
SimpleMap<string, vector<Product>> categoryMap;
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
		for (int i = 0; i < 5; ++i) getline(ss, token, ',');

		getline(ss, token, ',');
		if (!token.empty() && token[0] == '$')
			token = token.substr(1);
		try
		{
			p.sellingPrice = stod(token);
		}
		catch (...)
		{
			p.sellingPrice = 0.0;
		}

		getline(ss, token, ',');
		getline(ss, token, ',');
		getline(ss, p.category, ',');
		if (p.category.empty()) p.category = "NA";
		allProducts.push_back(p);
		productMap.put(p.uniqId, p);
		stringstream catStream(p.category);
		string singleCategory;

		while (getline(catStream, singleCategory, '|'))
		{
			singleCategory.erase(0, singleCategory.find_first_not_of(" \t"));
			singleCategory.erase(singleCategory.find_last_not_of(" \t") + 1);
			vector<Product>* list = categoryMap.get(singleCategory);
			if (!list)
			{
				categoryMap.put(singleCategory, vector<Product>{p});
			}
			else
			{
				list->push_back(p);
			}
		}
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

void handleListInventory(const string& args)
{
	stringstream ss(args);
	string category, method, order;
	ss >> category >> method >> order;

	vector<Product>* list = categoryMap.get(category);
	if (!list)
	{
		cout << "Invalid Category" << endl;
		return;
	}

	vector<Product> result = *list;

	bool usemergeSort = (method == "merge" || order == "merge");
	bool descending = (method == "desc" || order == "desc");
	auto ascendingComp = [](const Product& a, const Product& b)
	{
		return a.sellingPrice < b.sellingPrice;
	};
	auto descendingComp = [](const Product& a, const Product& b)
	{
		return a.sellingPrice > b.sellingPrice;
	};

	if (usemergeSort)
	mergeSort(result, descending ? descendingComp : ascendingComp);
	else
	insertionSort(result, descending ? descendingComp : ascendingComp);

	for (const Product& p : *list)
	{
		cout << p.uniqId << " | " << p.productName << endl;
	}
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

template <typename T, typename Comparator>
void insertionSort(vector<T>& vec, Comparator comp)
{
	for (size_t i = 1; i < vec.size(); ++i)
	{
		T key = vec[i];
		int j = i - 1;
		while (j >= 0 && comp(key, vec[j]))
		{
			vec[j + 1] = vec[j];
			--j;
		}
		vec[j+1] = key;
	}
}

template <typename T, typename Comparator>
void merge(vector<T>& vec, int left, int mid, int right, Comparator comp)
{
	vector<T> leftVec(vec.begin() + left, vec.begin() + mid + 1);
	vector<T> rightVec(vec.begin() + mid + 1, vec.begin() + right + 1);
	int i = 0, j = 0, k = left;
	while (i < leftVec.size() && j < rightVec.size())
	{
		if (comp(leftVec[i], rightVec[j]))
		vec[k++] = leftVec[i++];
		else
		vec[k++] = rightVec[j++];
	}
	while (i < leftVec.size()) vec[k++] = leftVec[i++];
	while (j < rightVec.size()) vec[k++] = leftVec[j++];
}

template <typename T, typename Comparator>
void mergeSort(vector<T>& vec, int left, int right, Comparator comp)
{
	if (left >= right) return;
	int mid = left + (right - left) / 2;
	mergeSort(vec, left, mid, comp);
	mergeSort(vec, mid + 1, right, comp);
	merge(vec, left, mid, right, comp);
}

template <typename T, typename Comparator>
void mergeSort(vector<T>& vec, Comparator comp)
{
	if (vec.empty()) return;
	mergeSort(vec, 0, vec.size() - 1, comp);
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
