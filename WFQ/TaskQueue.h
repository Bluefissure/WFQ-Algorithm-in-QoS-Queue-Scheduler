#pragma once
#ifndef TaskQueue_
#define TaskQueue_
#include<vector>
#include"Task.h"
#include"Random.h"
using namespace std;
class TaskQueue
{
private:
	const int BUFSZ = 500;
public:
	int TQID;	//taskqueue ID
	vector <Task> vc,	//to store tasks
		buf;	//to store generated tasks which is should not be add to vc
	double bufTime = 0,	//time of last task's generated time in buf
		lastVirFinish = 0,	//last vitrual finish time
		weight,	//
		packetNumSend = 0,
		packetNumReceived = 0,
		totLength = 0,
		totWait = 0,
		dropPacketNum = 0,
		pongNum = 0,
		sendAttemptNum = 0; 
	double avgLen() { return totLength / packetNumReceived; }
	double avgWait() { return totWait / packetNumSend; }
	TaskQueue() {};
	bool IsEmpty() { return vc.size() == 0; }
	void receive();	//generate tasks in taskqueue
	void fillbuf();	//fill buf to BUFSZ to ensure enough valid tasks 
	Task enqueue(Task task);	//Task enqueue
	Task Pop();
};
Task TaskQueue::Pop()
{
	Task t = vc[0];
	vc.erase(vc.begin());
	return t;
}
void TaskQueue::fillbuf()
{
	while (buf.size() < BUFSZ) {
		bufTime += expntl(lambda_arrive);	//possion process
		Task t(bufTime);
		buf.push_back(t);
	}
}
Task TaskQueue::enqueue(Task task)
{
	/*WFQ Algorithm*/
	double virStart = max(Time, lastVirFinish);
	double Ri = weight / totWeight * serveRate;
	task.virFinish = virStart + task.size / Ri;
	task.TID = ++taskNum;
	lastVirFinish = task.virFinish;
	packetNumReceived++;
	totLength += vc.size();

	if (TQID == 0) 
		fprintf(tq0l, "%d\n", vc.size());
	else if (TQID == 1) 
		fprintf(tq1l, "%d\n", vc.size());
	else if (TQID == 2) 
		fprintf(tq2l, "%d\n", vc.size());
	vc.push_back(task);
	return task;
}
void TaskQueue::receive()
{
	do {
		fillbuf();
		//transport tasks from buf_generate to taskqueue.
		while (buf.size()>0 && buf[0].timeGenerated <= Time) {
			int tmpSize = vc.size();
			Task t = enqueue(buf[0]);
//			printf("Task.%d is added to TaskQueue.%d with %d tasks ahead at %.2f\n", t.TID, TQID, tmpSize, t.timeGenerated);

//			cin.get();
			buf.erase(buf.begin());
		}
	} while (buf.size() == 0);
}


#endif
