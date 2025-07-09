#include "HeapPriorityQueue.h"
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue()
{
	size = 0;
}

HeapPriorityQueue::~HeapPriorityQueue()
{
}

HeapPriorityQueue::HeapPriorityQueue(const HeapPriorityQueue& other)
{
	size = other.size;
	for (int i = 0; i < size; ++i)
	{
		heap[i] = other.heap[i];
	}
}

HeapPriorityQueue& HeapPriorityQueue::operator=(const HeapPriorityQueue& other)
{
	if (this != &other)
	{
		size = other.size;
		for (int i = 0; i < size; ++i)
		{
			heap[i] = other.heap[i];
		}
	}
	return *this;
}

void HeapPriorityQueue::enqueue(const string& str, int priority)
{
	if (size >= MAX_SIZE)
	{
		cout << "Heap is full.\n";
		return;
	}

	PrinterJob newJob(str, priority);
	heap[size] = newJob;
	percolateUp(size);
	size++;
}

void HeapPriorityQueue::printJobs()
{
	if (size == 0)
	{
		cout << "No jobs found.\n";
	return;
	}

	cout << "Printing jobs in order:\n";
	while (size > 0)
	{
		cout << heap[0].printString << " (Priority: " << heap[0].priority << ")\n";
		heap[0] = heap[size - 1];
		size--;
		percolateDown(0);
	}
}


void HeapPriorityQueue::percolateUp(int index)
{
	while (index > 0)
	{
		int parent = (index - 1) / 2;
		if (heap[index] < heap[parent])
		{
			swap(heap[index], heap[parent]);
			index = parent;
		}
		else
		{
			break;
		}
	}
}

void HeapPriorityQueue::percolateDown(int index)
{
	while (index * 2 + 1 < size)
	{
		int left = index * 2 + 1;
		int right = index * 2 + 2;
		int smallest = left;

		if (right < size && heap[right] < heap[left])
		{
			smallest = right;
		}

		if (heap[smallest] < heap[index])
		{
			swap(heap[index], heap[smallest]);
			index = smallest;
		}
		else
		{
			break;
		}
	}
}
