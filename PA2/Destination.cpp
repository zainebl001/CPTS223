#include "Destination.hpp"

Destination::Destination(int pos, std::string city) : position(pos), name(city) {}
Destination::~Destination()
{
}

void Destination::printPosition() const
{
	std::cout << position << " ";
}

void Destination::printDestinationName() const
{
	srd::cout << name << " ";
}

int Destination::getPosition() const { return position; }
std::string Destination::getName() const
{
	return name;
}
