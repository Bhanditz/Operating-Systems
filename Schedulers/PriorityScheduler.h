
#ifndef PriorityScheduler_h
#define PriorityScheduler_h

#include<iostream>
#include<queue>
#include "Process.h"
#include "Scheduler.h"
using namespace std;

class Comparator
{
public:
    bool operator() (Process*, Process*);
};

class PriorityScheduler: public Scheduler
{

public:

  //  string schedulerType;
    vector<Process*> ReadyQueue;
  //  Process* currentRunningProcess;
  int ProcessCount;
   // int timeQuantum;
    //int ProcessesInReadyQueue;
    PriorityScheduler(string,int);
    void addProcessToQueue(Process*);
    Process* getNextProcess();
    //void addProcess();
    std::priority_queue<Process*, std::vector<Process*>, Comparator> *run_queue;
    std::priority_queue<Process*, std::vector<Process*>, Comparator> *expired_queue;

};
#endif
