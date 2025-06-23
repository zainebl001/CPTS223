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
		std::cerr << "Failed to open file." << std::endl;
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
		USCity city;
		int zip;

		std::getline(ss, token, ',');
		if (token.empty()) continue;
		zip = std::stoi(token);
		zipList.push_back(zip);
		zipVec.push_back(zip);

		std::getline(ss, city.lat, ',');
		std::getline(ss, city.lng, ',');
		std::getline(ss, city.city, ',');
		std::getline(ss, city.state_id, ',');
		std::getline(ss, city.state_name, ',');
		std::getline(ss, city.zcta, ',');
		std::getline(ss, city.parent_zcta, ',');
		std::getline(ss, city.population, ',');
		std::getline(ss, city.density, ',');

		for (int i = 0; i < 7; ++i) std::getline(ss, token, ',');
		std::getline(ss, city.timezone, ',');
		stdMap[zip] = city;
		avlMap.insert(zip, city);
	}
	file.close();
	std::cout << "Parsed " << zipList.size() << " ZIP codes.\n" << std::endl;

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

	std::cout << "std map lookup time: " << elapsedStd.count() << " seconds." << std::endl;
	std::cout << "avl map lookup time: " << elapsedAVL.count() << " seconds." << std::endl;

	return 0;
}
