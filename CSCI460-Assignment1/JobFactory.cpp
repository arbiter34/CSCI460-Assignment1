#include "stdafx.h"
#include "JobFactory.h"


Job **JobFactory::buildJobList(int num) {
	Job **jobList = new Job*[num];
	for (int i = 0; i < num; i++) {
		jobList[i] = new Job(1, (rand() % 500) + 1);
	}
	return jobList;
}


Job **JobFactory::getSetJobList() {
	return new Job*[12] {
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
}
Job *JobFactory::jobList[12] = {
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