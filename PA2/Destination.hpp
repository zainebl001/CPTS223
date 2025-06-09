#ifndef DESTINATION_HPP
#define DESTINATION_HPP
#include <string>
#include <iostream>

class Destination
{
public:
	Destination(int pos, std::string city);
	~Destination();
	void printPosition() const;
	void printDestinationName() const;
	int getPosition() const;
	std::string getName() const;

private:
	int position;
	std::string name;
};

#endif
