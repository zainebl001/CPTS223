#include "data.hpp"

Data::Data() 
{
	command = "";
	description = "";
	points = 0;
}

Data::Data(const std::string& cmd, const std::string& desc, int pts)
{
	command = cmd;
	description = desc;
	points = pts;
}

Data::Data(const Data& other)
{
	command = other.command;
	description = other.description;
	points = other.points;
}

Data& Data::operator=(const Data& other)
{
	if (this != &other)
	{
		command = other.command;
		description = other.description;
		points = other.points;
	}
	return *this;
}

Data::~Data()
{
}

std::string Data::getCommand() const
{
	return command;
}

std::string Data::getDescription() const
{
	return description;
}

int Data::getPoints() const
{
	return points;
}

void Data::setCommand(const std::string& cmd)
{
	command = cmd;
}

void Data::setDescription(const std::string& desc)
{
	description = desc;
}

void Data::setPoints(int pts)
{
	points = pts;
}

bool Data::operator==(const Data& other) const
{
	return (command == other.command);
}

bool Data::operator!=(const Data& other) const
{
	return !(*this == other);
}

void Data::display() const
{
	std::cout << "Command: " << command
		<< ", Description: " << description
		<< ", Points: " << points << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Data& data)
{
	os << data.command << " - " << data.description << " (Points: " << data.points << ")";
	return os;
}
