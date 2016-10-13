#pragma once
#ifndef Server_
#define Server_
#include"Random.h"
#include"Task.h"
#include"TaskQueue.h"
class Server {
public:
	int N;						//number of listen taskqueue
	TaskQueue* listen[10];		//taskqueues' pointer of witch this server is listening to
	void Serve(TaskQueue *tq);	//serve a TaskQueue
	void BeginServe();			//begin to serve
	TaskQueue* Schedule();		//find next TaskQueue to serve
	void report();				//report status of statistics
	bool checkloop();			//check whether to break loop or not
};
void Server::Serve(TaskQueue *tq)
{
	for (int i = 0; i < 3; i++) listen[i]->receive();
	if (tq->IsEmpty()) {
//		printf("Server nop from %.2f to %.2f\n", Time, tq->buf[0].timeGenerated);
		Time = tq->buf[0].timeGenerated;
		tq->enqueue(tq->buf[0]);
		tq->buf.erase(tq->buf.begin());
	}
	for (int i = 0; i < 3; i++) listen[i]->receive();
	Task t = tq->vc[0];
	double priTime = Time;
	Time += t.size / serveRate;
//	printf("Server serve Task.%d from %.2f to %.2f\n", t.TID, priTime, Time);
//	printf("Task.%d has been waitting for %.2f when begin to serve.\n", t.TID, priTime - t.timeGenerated);
	tq->totWait += priTime - t.timeGenerated;
	//Write Wait time
	if (tq->TQID == 0) 
		fprintf(tq0w, "%.8f\n", priTime - t.timeGenerated);
	else if (tq->TQID == 1) 
		fprintf(tq1w, "%.8f\n", priTime - t.timeGenerated);
	else if (tq->TQID == 2) 
		fprintf(tq2w, "%.8f\n", priTime - t.timeGenerated);
	tq->packetNumSend++;
	tq->Pop();
}
void Server::report()
{
	for (int i = 0; i < 3; i++) {
		printf("Tq.%d avgLen:%.8f avgWait:%.8f \n",
			listen[i]->TQID, listen[i]->avgLen(), listen[i]->avgWait());
	}
}
bool Server::checkloop()
{
	if (abs(listen[0]->avgLen() - listen[1]->avgLen()) < 0.02)
		if (abs(listen[1]->avgLen() - listen[2]->avgLen()) < 0.02)
			if (abs(listen[2]->avgLen() - listen[1]->avgLen()) < 0.02)
				return 1;
	return 0;


}
void Server::BeginServe()
{
	TaskQueue *tq;
	int loop = 0;
	while (1) {
		loop++;
		if (loop % 50000 == 0) {
			printf("loop:%d\n", loop);
			report();
			if(checkloop())
				system("pause");
		}
		tq = Schedule();
		Serve(tq);
	}
}

TaskQueue* Server::Schedule()
{
	/*WFQ Algorithm*/
	int it = 0, selectQueue = -1;
	double minVirFinish = 0x7fffffff;
	for (; it < 3; it++) {
		if (!listen[it]->IsEmpty() && listen[it]->vc[0].virFinish < minVirFinish) {
			minVirFinish = listen[it]->vc[0].virFinish;
			selectQueue = it;
		}
	}
	if (selectQueue == -1) {
//		printf("Did not schedule\n");
		int rr = rand() % (int)(totWeight + 0.5) + 1, sum = 0;
		for (int i = 0; i < 3; i++) {
			sum += listen[i]->weight;
			if (rr <= sum) return listen[i];
		}
		return listen[rand()%3];
	}
//	printf("Choose tq:%d\n", selectQueue);
	return listen[selectQueue];
}



#endif
