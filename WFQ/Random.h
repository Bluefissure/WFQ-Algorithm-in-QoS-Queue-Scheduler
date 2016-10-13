#pragma once
#ifndef Random_
#define Random_
#include<cmath>
double Time;
double lambda_arrive, lambda_serve, p, q, totWeight, serveRate;
FILE *tq0l, *tq0w, *tq1l, *tq1w, *tq2l, *tq2w;
int taskNum, taskQueueNum, eventNum;
double expntl(double lambda)
{
	double u; // used to store a random number. 
	do{
		u=rand()*1.0/RAND_MAX;//uniform number in the interval [0.0, 1.0]
	}while((u==0)||(u==1)); //special cases that we want to avoid
	double ans = -log(1 - u) / lambda;
	return ans;
}
#endif
