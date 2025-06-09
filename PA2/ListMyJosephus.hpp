#ifndef LISTMYJOSEPHUS_HPP
#define LISTMYJOSEPHUS_HPP
#include <list>
#include <string>
#include <vector>
#include "Destination.hpp"

class ListMyJosephus
{
private:
	int M, N;
	std::list<Destination> circle;
	std::list<Destination>::iterator cursor;

public:
	ListMyJosephus(int m, int n, const std::vector<std::string>& cities);
	~ListMyJosephus();
	void clear();
	int currentSize() const;
	bool isEmpty() const;
	Destination eliminateDestination();
	void printAllDestinations() const;
};

#endif
