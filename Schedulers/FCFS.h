
#ifndef FCFS_h
#define FCFS_h

#include<iostream>
#include<queue>
#include "Process.h"
#include "Scheduler.h"
using namespace std;

class FCFS: public Scheduler
{

public:

   // string schedulerType;
    queue<Process*> ReadyQueue;
   // Process* currentRunningProcess;
   // int timeQuantum;
   // int ProcessesInReadyQueue;
    FCFS(string,int);
    void addProcessToQueue(Process*);
    Process* getNextProcess();
    //void addProcess();

};
#endif
