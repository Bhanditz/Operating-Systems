
#ifndef LCFS_h
#define LCFS_h

#include<iostream>
#include<stack>
#include "Process.h"
#include "Scheduler.h"
using namespace std;

class LCFS: public Scheduler
{

public:

  //  string schedulerType;
    stack<Process*> ReadyQueue;
  //  Process* currentRunningProcess;
  //  int timeQuantum;
  //  int ProcessesInReadyQueue;
    LCFS(string,int);
    void addProcessToQueue(Process*);
    Process* getNextProcess();
    //void addProcess();

};
#endif
