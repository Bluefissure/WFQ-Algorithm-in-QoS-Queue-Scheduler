#pragma once
#ifndef Task_
#define Task_
class Task {
public:
	int TID;				//Task ID
	double timeGenerated,	//generated time
		size,				//size(length) of task
		virFinish;			//vitrual finish time
	Task() {};
	Task(double time) {
		timeGenerated = time;
		size = expntl(lambda_serve);	//length of packet is subject to an exponential distribution
	}
};



#endif
