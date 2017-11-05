#include "Process.h"
#include "SJF.h"
#include<iostream>
#include<string>
#include<stack>
#include "Scheduler.h"
using namespace std;



    SJF::SJF(string SchedulerName, int timeQ): Scheduler()
    {
        schedulerType = "SJF";
        ProcessesInReadyQueue = 0;
        currentRunningProcess = NULL;
        timeQuantum = timeQ;
    }

    void SJF::addProcessToQueue(Process *p)
    {
        p->SchedulerID = ProcessesInReadyQueue + 1;
        ReadyQueue.push_back(p);
        ProcessesInReadyQueue++;
    }

    Process* SJF::getNextProcess()
    {
        if(ProcessesInReadyQueue == 0)
        {
            return(NULL);
        }
        int winner = 0;
        Process* ans = ReadyQueue[0];
        for(int i = 1 ; i < ProcessesInReadyQueue ; i++)
        {
            if(ReadyQueue[i]->remainingTime < ans->remainingTime)
            {
                ans = ReadyQueue[i];
                winner = i;
            }
            else if(ReadyQueue[i]->remainingTime == ans->remainingTime)
            {
                if(ReadyQueue[i]->SchedulerID < ans->SchedulerID)
                {
                    winner = i;
                    ans = ReadyQueue[i];
                }
            }
        }
        ReadyQueue.erase(ReadyQueue.begin()+winner);
        ProcessesInReadyQueue--;
        return(ans);
    }

