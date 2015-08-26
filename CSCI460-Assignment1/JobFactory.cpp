#include "stdafx.h"
#include "JobFactory.h"


Job **JobFactory::buildJobList(int num) {
	Job **jobList = new Job*[num];
	for (int i = 0; i < num; i++) {
		jobList[i] = new Job(1, (rand() % 500) + 1);
	}
	return jobList;
}