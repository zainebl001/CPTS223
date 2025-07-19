#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

void insertionSort(vector<int> &arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        int key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

int partition(vector<int> &arr, int low, int high)
{
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSortHelper(vector<int> &arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSortHelper(arr, low, pi - 1);
		quickSortHelper(arr, pi + 1, high);
	}
}

void quickSort(vector<int> &arr)
{
	if (!arr.empty())
	{
		quickSortHelper(arr, 0, arr.size() - 1);
	}
}

void shellSort(vector<int> &arr)
{
	int n = arr.size();
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i++)
		{
			int temp = arr[i];
			int j = i;
			while (j >= gap && arr[j - gap] > temp)
			{
				arr[j] = arr[j - gap];
				j -= gap;
			}
			arr[j] = temp;
		}
	}
}

void heapify(vector<int> &arr, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void heapSort(vector<int> &arr)
{
	int n = arr.size();
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}
	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

void printStatistics(const vector<double> &durations)
{
    double minTime = *min_element(durations.begin(), durations.end());
    double maxTime = *max_element(durations.begin(), durations.end());
    double avgTime = accumulate(durations.begin(), durations.end(), 0.0) / durations.size();

    double variance = 0.0;
    for (double t : durations)
    {
        variance += (t - avgTime) * (t - avgTime);
    }
    double stdDev = sqrt(variance / durations.size());

    cout << "=== Statistics ===\n";
    cout << "Min Time: " << minTime << " ms\n";
    cout << "Max Time: " << maxTime << " ms\n";
    cout << "Average Time: " << avgTime << " ms\n";
    cout << "Standard Deviation: " << stdDev << " ms\n\n";
}

int main()
{
    // Size of the collection
    const int N = 10000;
    // Max limit for the random generation
    const int MAX_VAL = 100000;
    // Total trial (use the same for other sorting algorithms)
    const int TRIALS = 10;

    srand(static_cast<unsigned>(time(nullptr)));

    vector<double> durations;

    for (int trial = 0; trial < TRIALS; ++trial)
    {
        vector<int> data(N);
        // Generate 10,000 random numbers and populate data
        for (int i = 0; i < N; ++i)
        {
            data[i] = rand() % (MAX_VAL + 1);
        }

        auto start = chrono::high_resolution_clock::now();
        insertionSort(data); // sort data
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        durations.push_back(elapsed.count());

        cout << "InsertionTrial " << trial + 1 << ": " << elapsed.count() << " ms\n";
    }
	printStatistics(durations);

	durations.clear();
	for (int trial = 0; trial < TRIALS; ++trial)
	{
		vector<int> data(N);
		for (int i = 0; i < N; ++i)
		{
			data[i] = rand() % (MAX_VAL + 1);
		}
		auto start = chrono::high_resolution_clock::now();
		quickSort(data);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> elapsed = end - start;
		durations.push_back(elapsed.count());
		cout << "QuickSort Trial " << trial + 1 << ": " << elapsed.count() << " ms\n";
	}
    printStatistics(durations);

	durations.clear();
for (int trial = 0; trial < TRIALS; ++trial)
{
	vector<int> data(N);
	for (int i = 0; i < N; ++i)
	{
		data[i] = rand() % (MAX_VAL + 1);
	}
	auto start = chrono::high_resolution_clock::now();
	shellSort(data);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> elapsed = end - start;
	durations.push_back(elapsed.count());
	cout << "ShellSort Trial " << trial + 1 << ": " << elapsed.count() << " ms\n";
}
	printStatistics(durations); 

	durations.clear();
	for (int trial = 0; trial < TRIALS; ++trial)
	{
		vector<int> data(N);
		for (int i = 0; i < N; ++i)
		{
			data[i] = rand() % (MAX_VAL + 1);
		}
		auto start = chrono::high_resolution_clock::now();
		heapSort(data);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> elapsed = end - start;
		durations.push_back(elapsed.count());
		cout << "HeapSort Trial " << trial + 1 << ": " << elapsed.count() << " ms\n";
	}
	printStatistics(durations);
    return 0;
}
