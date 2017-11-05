

#ifndef SJF_h
#define SJF_h

#include<iostream>
#include<queue>
#include "Process.h"
#include "Scheduler.h"
using namespace std;

class SJF: public Scheduler
{

public:

  //  string schedulerType;
    vector<Process*> ReadyQueue;
  //  Process* currentRunningProcess;
   // int timeQuantum;
    //int ProcessesInReadyQueue;
    SJF(string,int);
    void addProcessToQueue(Process*);
    Process* getNextProcess();
    //void addProcess();

};
#endif
