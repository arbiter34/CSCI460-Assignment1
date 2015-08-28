#include "stdafx.h"
#include "Processor.h"

volatile bool Processor::running = false;
HANDLE Processor::hMutex = CreateMutex(NULL, FALSE, NULL);

Processor::Processor()
{
	//Set number of cores
	//numCores = (7084 % 3) + 2;
	numCores = 5;
}


Processor::~Processor()
{
}

void Processor::Init() {
	//Create process queues
	coreQueues = new std::queue<Job*>[numCores];

	//Init vars
	jobCount = 0;
	optimalTime = 0;
	tickCount = 0;
}

/*  
 *  LoadBinary - Pushes job object into next core queue  
 */
void Processor::LoadBinary(Job *job)
{
	//Running Total of Ticks for Jobs
	optimalTime += job->jobTime;

	//Lock Mutex
	WaitForSingleObject(hMutex, INFINITE);
	//Push Job object into next core's queue
	(coreQueues[jobCount % numCores]).push(job);

	//Reset Tick Counter
	if (jobCount == 0) {
		tickCount = 0;
	}

	if (jobCount % numCores == 3) {
		numCores = numCores;
	}

	//Unlock Mutex
	ReleaseMutex(hMutex);
	//Increment job counter
	jobCount++;
}

/*
 *  odprintf - printf like debug printer
 */
void __cdecl odprintf(const char *format, ...)
{
	char    buf[4096], *p = buf;
	va_list args;
	int     n;

	va_start(args, format);
	n = _vsnprintf(p, sizeof buf - 3, format, args); // buf-3 is room for CR/LF/NUL
	va_end(args);

	p += (n < 0) ? sizeof buf - 3 : n;

	while (p > buf  &&  isspace(p[-1]))
		*--p = '\0';

	*p++ = '\r';
	*p++ = '\n';
	*p = '\0';

	OutputDebugStringA(buf);
}

/* 
 *  RunProcessor - Emulates at high level a processor - Not Accurate
 *  Note:  Meant to be run as a thread
 */
int Processor::RunProcessor()
{
	//Declare/Init Vars
	int sleepTime = 0;
	bool queuesEmpty = true, jobStarted = false;
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, Frequency;

	//High-Res Time-Stamp Functions
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	//Main Control Loop
	while (running || !queuesEmpty) {
		//Lock Mutex
		WaitForSingleObject(hMutex, INFINITE);
		//Unlock Mutex
		ReleaseMutex(hMutex);

		//Start assuming queues are empty
		queuesEmpty = true;

		//Iterate over cores
		for (int i = 0; i < numCores; i++) {

			//Lock mutex
			WaitForSingleObject(hMutex, INFINITE);

			//Check if current queue is empty - skip if so
			if (coreQueues[i].empty()) {
				ReleaseMutex(hMutex);
				continue;
			}

			//if (!jobStarted) {
			//	jobStarted = true;
			//	//Hack to start tickCount correctly - 1 tick per job load
			//	tickCount = jobCount;
			//}
			//Get reference to job at front of current queue
			Job *job = (coreQueues[i].front());
			//Unlock Mutex
			ReleaseMutex(hMutex);

			
			if (job != NULL) {
				//A queue had a process running - mark as such
				queuesEmpty = false;

				//Decrement Ticks left for current Job
				job->jobTime--;

				//If Ticks left == 0 - Move to Next Job
				if (job->jobTime <= 0) {
					coreQueues[i].pop();
				}
			}
		}

		//Increment Tick Counter
		tickCount++;
		Sleep(0);
	}

	//High-Res Time-Stamp Functions
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 100000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	//Debug Print Results
	odprintf("Runtime: %lld microseconds", ElapsedMicroseconds.QuadPart);
	odprintf("Virtual Runtime: %ld", tickCount);
	odprintf("Perfect Runtime: %ld", (optimalTime / numCores));

	return 0;
}
