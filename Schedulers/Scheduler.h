/**
Base Scheduler class for all types of schedulers
*/

#ifndef Scheduler_h
#define Scheduler_h

#include<iostream>
#include<vector>
#include "Process.h"
using namespace std;

class Scheduler
{

public:

    string schedulerType;
    Process* currentRunningProcess;
    int timeQuantum;
    int ProcessesInReadyQueue;
    Scheduler();
    virtual void addProcessToQueue(Process*) = 0;
    virtual Process* getNextProcess() = 0;
    //void addProcess();

};
#endif
