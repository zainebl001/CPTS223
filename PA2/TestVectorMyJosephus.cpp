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

int main()
{
	vector<string> allCities = loadCities("destinations-1.csv");
	int maxN = allCities.size();

	ofstream log("results.log", ios::app);
	vector<double> times;

	for (int N = 1; N <= maxN; ++N)
	{
		int M = rand() % N + 1;
		vector<string> subset(allCities.begin(), allCities.begin() + N);

		VectorMyJosephus game(M, N, subset);

		clock_t start = clock();
		while (game.currentSize() > 1)
		{
			Destination eliminated = game.eliminateDestination();
			cout << "Eliminated: ";
			eliminated.printDestinationName();
			cout << endl;
		}
		cout << "Winner: ";
		game.printAllDestinations();

		clock_t end = clock();
		double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
		times.push_back(elapsed);
		log << "Vector N=" << N << ", M=" << M << ", Time=" << elapsed << "\n";
	}

	double avg = 0;
	for (double t : times) avg += t;
	avg /= times.size();
	cout << "Vector Average Time: " << avg << " seconds" << endl;
	log << "Vector Average Time: " << avg << " seconds\n";

	return 0;
}
