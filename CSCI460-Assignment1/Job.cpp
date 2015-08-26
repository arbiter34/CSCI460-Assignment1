#include "stdafx.h"
#include "Job.h"


Job::Job(int arrivalTime, int jobTime)
{
	this->arrivalTime = arrivalTime;
	this->jobTime = jobTime;
}


Job::~Job()
{
}
