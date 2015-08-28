#pragma once
#include "Job.h"

/*
 *  JobFactory - Helper to create Pseudo-Random List of Jobs - Delay Set to 1
 */
class JobFactory
{
public:
	static Job** buildJobList(int num);
	static Job* jobList[];
};

