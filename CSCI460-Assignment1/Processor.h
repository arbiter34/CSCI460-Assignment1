#pragma once
#include "Job.h"
#include <vector>
#include <mutex>

#define SLEEP_TIME 1

/*
 *  Processor - Abstracts very loose concept of a Multi-Core CPU
 */

class Processor
{
public:
	//Main Control Loop Exit
	static volatile bool running;

	static HANDLE hMutex;
	int numCores;

	//Best Possible RunTime
	long int optimalTime;

	//Achieved RunTime
	long int actualTime;

	Processor();
	~Processor();

	//Load a Job into Next Core Queue - Thread Safe
	void LoadBinary(Job *job);

	//Main Processor Thread Function
	int RunProcessor();

private:
	//Running JobCount
	int jobCount;

	//Process Queue
	std::vector<Job*> *coreQueues;
};

