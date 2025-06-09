#include "VectorMyJosephus.hpp"
#include <iostream>

VectorMyJosephus::VectorMyJosephus(int m, int n, const std::vector<std::string>& cities) : M(m), N(n), index(0)
{
	for (int i = 0; i < N; ++i)
	{
		circle.push_back(Destination(i, cities[i]));
	}
}

VectorMyJosephus::~VectorMyJosephus() { clear(); }
void VectorMyJosephus::clear()
{
	circle.clear();
}
int VectorMyJosephus::currentSize() const { return circle.size(); }

bool VectorMyJosephus::isEmpty() const { return circle.empty(); }

Destination VectorMyJosephus::eliminateDestination()
{
	index = (index + M) % circle.size();
	Destination eliminated = circle[index];
	circle.erase(circle.begin() + index);
	if (index >= circle.size()) index = 0;
	return eliminated;
}

void VectorMyJosephus::printAllDestinations() const
{
	for (const auto& d : circle)
	{
		d.printDestinationName();
	}
	std::cout << std::endl;
}
