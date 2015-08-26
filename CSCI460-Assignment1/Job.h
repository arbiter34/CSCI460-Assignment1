#pragma once
/*
 *  Job Class - Represents Job
 *	Note: Should probably be a struct - oh well
 */
class Job
{
public:
	//  Delay for Job To Start
	int arrivalTime;

	//  Lenght of Job in Ticks
	int jobTime;

	Job(int arrivalTime, int jobTime);
	~Job();

private:
};

