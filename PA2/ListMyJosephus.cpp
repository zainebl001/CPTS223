#include "ListMyJosephus.hpp"
#include <iostream>

ListMyJosephus::ListMyJosephus(int m, int n, const std::vector<std::string>& cities) : M(m), N(n)
{
	for (int i = 0; i < N; i++)
	{
		circle.push_back(Destination(i, cities[i]));
	}
	cursor = circle.begin();
}
ListMyJosephus::~ListMyJosephus() { clear(); }

void ListMyJosephus::clear() { circle.clear(); }

int ListMyJosephus::currentSize() const
{
	return circle.size();
}

bool ListMyJosephus::isEmpty() const { return circle.empty(); }

Destination ListMyJosephus::eliminateDestination()
{
	for (int i = 0; i < M; ++i)
	{
		++cursor;
		if (cursor == circle.end()) cursor = circle.begin();
	}
	Destination eliminated = *cursor;
	cursor = circle.erase(cursor);
	if (cursor == circle.end()) cursor =  circle.begin();
	return eliminated;
}

void ListMyJosephus::printAllDestinations() const
{
	for (const auto& d : circle)
	{
		d.printDestinationName();
	}
	std::cout << std::endl;
}
