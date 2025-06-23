#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include "USCity.hpp"
#include "avl_map.hpp"

int main()
{
	std::ifstream file("uszips.csv");
	if (!file.is_open())
	{
        	std::cerr << "Failed to open uszips.csv" << std::endl;
		return 1;
	}
	std::map<int, USCity> stdMap;
	avl_map<int, USCity> avlMap;
	std::list<int> zipList;
	std::vector<int> zipVec;
	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string token;
		std::vector<std::string> fields;

		bool inQuotes = false;
		std::string field;
		char c;
		while (ss.get(c))
		{
			if (c == '"' && (field.empty() || field.back() != '\\'))
			{
				inQuotes = !inQuotes;
			}
			else if (c == ',' && !inQuotes)
			{
				fields.push_back(field);
				field.clear();
			}
			else
			{
				field += c;
			}
		}
		fields.push_back(field);

		if (fields.size() < 18 || fields[0].empty()) continue;

		int zip;
		try
		{
			zip = std::stoi(fields[0]);
        	}
		catch (...)
		{
			continue;
		}

		USCity city;
		city.lat = fields[1];
		city.lng = fields[2];
		city.city = fields[3];
		city.state_id = fields[4];
		city.state_name = fields[5];
		city.zcta = fields[6];
		city.parent_zcta = fields[7];
		city.population = fields[8];
		city.density = fields[9];
		city.timezone = fields[17];

		zipList.push_back(zip);
		zipVec.push_back(zip);

		stdMap[zip] = city;
		avlMap.insert(zip, city);
	}
	file.close();

	std::cout << "Parsed " << zipList.size() << " ZIP codes.\n";

	if (zipVec.empty())
	{
		std::cerr << "No ZIP codes available for lookup. Exiting.\n";
		return 1;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, zipVec.size() - 1);



	std::vector<int> randomZips;
	for (int i = 0; i < 1000; ++i)
	{
		randomZips.push_back(zipVec[dis(gen)]);
	}

	auto start1 = std::chrono::high_resolution_clock::now();
	for (int z : randomZips)
	{
		auto it = stdMap.find(z);
	}
	auto end1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedStd = end1 - start1;

	auto start2 = std::chrono::high_resolution_clock::now();
	for (int z : randomZips)
	{
		auto it = avlMap.find(z);
	}
	auto end2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedAVL = end2 - start2;

	std::cout << "std::map lookup time: " << elapsedStd.count() << " seconds\n";
	std::cout << "avl_map lookup time: " << elapsedAVL.count() << " seconds\n";

	return 0;
}
