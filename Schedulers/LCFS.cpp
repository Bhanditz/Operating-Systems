#include "Process.h"
#include "LCFS.h"
#include<iostream>
#include<string>
#include "Scheduler.h"
#include<stack>
using namespace std;

    LCFS::LCFS(string SchedulerName, int timeQ): Scheduler()
    {
        schedulerType = "LCFS";
        ProcessesInReadyQueue = 0;
        currentRunningProcess = NULL;
        timeQuantum = timeQ;
    }

    void LCFS::addProcessToQueue(Process *p)
    {
        ReadyQueue.push(p);
        ProcessesInReadyQueue++;
    }

    Process* LCFS::getNextProcess()
    {

        if(ReadyQueue.empty())
            return(NULL);
        Process* ans = ReadyQueue.top();
        ReadyQueue.pop();
        return(ans);
    }

