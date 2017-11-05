#include "Process.h"
#include "Scheduler.h"
#include<iostream>
#include<string>
using namespace std;

    Scheduler::Scheduler()
    {
//        schedulerType = SchedulerName;
//        ProcessesInReadyQueue = 0;
//        currentRunningProcess = NULL;
//        timeQuantum = timeQ;
    }

//    void Scheduler::addProcessToQueue(Process *p)
//    {
//        ReadyQueue.push_back(p);
//        ProcessesInReadyQueue++;
//    }
//
//    Process* Scheduler::getNextProcess()
//    {
//        if(ProcessesInReadyQueue == 0)
//            return(NULL);
//        Process* ans = ReadyQueue[0];
//        int position = 0;
//        for(int i = 1 ; i < ProcessesInReadyQueue ; i++)
//        {
//            if(ReadyQueue[i]->PID < ans->PID)
//            {
//                position = i;
//                ans = ReadyQueue[i];
//            }
//        }
//        ProcessesInReadyQueue--;
//        ReadyQueue.erase(ReadyQueue.begin() + position);
//        return(ans);
//    }

//    void Scheduler::addProcess()
//    {
//
//    }
