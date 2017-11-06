#include "Process.h"
#include "FCFS.h"
#include "Scheduler.h"
#include<iostream>
#include<string>
using namespace std;

    FCFS::FCFS(string SchedulerName,int timeQ): Scheduler()
    {
        schedulerType = "FCFS";
        ProcessesInReadyQueue = 0;
        currentRunningProcess = NULL;
        timeQuantum = timeQ;
    }

    void FCFS::addProcessToQueue(Process *p)
    {
        ReadyQueue.push(p);
        ProcessesInReadyQueue++;
    }

    Process* FCFS::getNextProcess()
    {
        if(ReadyQueue.empty())
            return(NULL);
        Process* ans = ReadyQueue.front();
        ReadyQueue.pop();
        return(ans);
    }

