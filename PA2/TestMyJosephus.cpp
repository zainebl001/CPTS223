#include "ListMyJosephus.hpp"
#include "VectorMyJosephus.hpp"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<string> loadCities(const string& filename)
{
	ifstream file(filename);
	vector<string> cities;
	string line;
	if (getline(file, line))
	{
		stringstream ss(line);
		string city;
		while (getline(ss, city, ',')) cities.push_back(city);
	}
	return cities;
}

int main(int argc, char* argv[])
{
	bool useList = true;
	if (argc > 1 && string(argv[1]) == "vector") useList = false;
	vector<string>  allCities = loadCities("destinations-1.csv");

	int maxN = allCities.size();

	ofstream log("results.log", ios::app);
	vector<double> times;

	for (int N = 1; N <= maxN; ++N)
	{
		int M = rand() % N + 1;
		vector<string> subset(allCities.begin(), allCities.begin() + N);

		clock_t start = clock();
		if (useList)
		{
			ListMyJosephus game(M, N, subset);
			while (game.currentSize() > 1) game.eliminateDestination();
			cout << (useList ? "List" : "Vector") << " N=" << N << ", M=" << M << ", Winner: ";
			game.printAllDestinations();
		}
		else
		{
			VectorMyJosephus game(M, N, subset);
			while (game.currentSize() > 1) game.eliminateDestination();
			cout << (useList ? "List" : "Vector") << " N=" << N << ", M=" << M << ", Winner: ";
			game.printAllDestinations();

		}
		clock_t end = clock();

		double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
		times.push_back(elapsed);
		log << (useList ? "List" : "Vector") << " N=" << N << ", M=" << M << ", Time=" << elapsed << "\n";
	}

	double avg = 0;
	for (double t : times) avg += t;
	avg /= times.size();
	cout << (useList ? "List" : "Vector") << " Average Time: " << avg << " seconds" << endl;
	log << (useList ? "List" : "Vector") << " Average Time: " << avg << " seconds\n";

	return 0;
}
