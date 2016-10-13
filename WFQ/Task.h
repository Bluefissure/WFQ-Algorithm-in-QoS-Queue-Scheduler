#pragma once
#ifndef Task_
#define Task_
class Task {
public:
	int TID;//Task ID
	double timeGenerated, //generated time
		size,	//size of task
		virFinish;	//vitrual finish time
	Task() {};
	Task(double time) {
		timeGenerated = time;
		size = expntl(lambda_serve);
	}
};



#endif
