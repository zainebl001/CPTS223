#ifndef LISTMYJOSEPHUS_HPP
#define LISTMYJOSEPHUS_HPP
#include <list>
#include <string>
#include "Destination.hpp"

class ListMyJosephus
{
private:
	int m, n;
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
