#ifndef VECTORMYJOSEPHUS_HPP
#define VECTORMYJOSEPHUS_HPP
#include <vector>
#include "Destination.hpp"

class VectorMyJosephus
{
private:
	int M, N, index;
	std::vector<Destination> circle;

public:
	VectorMyJosephus(int m, int n, const std::vector<std::string>& cities);
	~VectorMyJosephus();
	void clear();
	int currentSize() const;
	bool isEmpty() const;
	Destination eliminateDestination();
	void printAllDestinations() const;
};

#endif
