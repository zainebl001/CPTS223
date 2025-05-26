#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <iostream>

class Data
{
private:
	std::string command;
	std::string description
	int points;

public:
	Data();
	Data(const std::string& cmd, const std::string& desc, int pts);

	Data(const Data& other);

	Data& operator=(const Data& other);

	~Data();

	std::string getCommand const;
	std::string getDescription() const;
	int getPoints() const;

	void setCommand(const std::string& cmd);
	void setDescription(const std::string& desc);
	void setPoints(int pts);

	bool operator==(const Data& other) const;
	bool operator!=(const Data& other) const;

	void display() const;

	friend std::ostream& operator<<(std::ostream& os, const Data& data);
};

#endif
