
#ifndef RRS_h
#define RRS_h

#include<iostream>
#include<queue>
#include "Process.h"
#include "Scheduler.h"
using namespace std;

class RRS: public Scheduler
{

public:

    //string schedulerType;
    queue<Process*> ReadyQueue;
    //Process* currentRunningProcess;
    //int timeQuantum;
    //int ProcessesInReadyQueue;
    RRS(string,int);
    void addProcessToQueue(Process*);
    Process* getNextProcess();
    //void addProcess();

};
#endif

