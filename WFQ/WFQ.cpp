// WFQ.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdlib>
#include<ctime>

#include"Random.h"
#include"Task.h"
#include"TaskQueue.h"
#include"Server.h"
Server s0;
TaskQueue tq[3];
void init()
{
	srand(time(NULL));
	totWeight = 0;
	for (int i = 0; i < 3; i++) {
		tq[i].TQID = i;
		tq[i].bufTime = 0;
		tq[i].weight = i+1;
		totWeight += tq[i].weight;
		s0.listen[i] = &tq[i];
	}
	serveRate = 1;
	s0.N = 3;
	Time = 0;


	tq0l = fopen("tq0l.txt", "w");//Queue length distribution of TaskQueue.0
	tq0w = fopen("tq0w.txt", "w");//Wait time distribution of TaskQueue.0
	tq1l = fopen("tq1l.txt", "w");
	tq1w = fopen("tq1w.txt", "w");
	tq2l = fopen("tq2l.txt", "w");
	tq2w = fopen("tq2w.txt", "w");
}
void simulate()
{
	s0.BeginServe();
}
using namespace std;
int main()
{
	init();
	printf("Please input lambda_arrive and lambda_serve:\n");
	cin >> lambda_arrive >> lambda_serve;
	simulate();
    return 0;
}

