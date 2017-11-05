
#include "Process.h"
#include "RRS.h"
#include "Scheduler.h"
#include<iostream>
#include<string>
using namespace std;

    RRS::RRS(string SchedulerName, int timeQ): Scheduler()
    {
        schedulerType = "RR";
        ProcessesInReadyQueue = 0;
        currentRunningProcess = NULL;
        timeQuantum = timeQ;
    }

    void RRS::addProcessToQueue(Process *p)
    {
        ReadyQueue.push(p);
        ProcessesInReadyQueue++;
    }

    Process* RRS::getNextProcess()
    {
        if(ReadyQueue.empty())
            return(NULL);
        Process* ans = ReadyQueue.front();
        ReadyQueue.pop();
        return(ans);
    }

//    void Scheduler::addProcess()
//    {
//
//    }

