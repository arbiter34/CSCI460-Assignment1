#include "stdafx.h"
#include "JobList.h"


Job *JobList::jobList[NUM_JOBS] = {
	new Job(4, 9),
	new Job(15, 2),
	new Job(18, 16),
	new Job(20, 3),
	new Job(26, 29),
	new Job(29, 198),
	new Job(35, 7),
	new Job(45, 170),
	new Job(57, 180),
	new Job(83, 178),
	new Job(88, 73),
	new Job(95, 8)
};