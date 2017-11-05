
#include "Process.h"
#include "PriorityScheduler.h"
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include "Scheduler.h"
using namespace std;



    PriorityScheduler::PriorityScheduler(string SchedulerName, int timeQ): Scheduler()
    {
        schedulerType = "PRIO";
        ProcessesInReadyQueue = 0;
        ProcessCount = 0;
        currentRunningProcess = NULL;
        timeQuantum = timeQ;
        run_queue = new std::priority_queue<Process*, std::vector<Process*>, Comparator>;
        expired_queue = new std::priority_queue<Process*, std::vector<Process*>, Comparator>;
    }

    void PriorityScheduler::addProcessToQueue(Process *p)
    {
        p->SchedulerID = ProcessCount;
        ProcessCount++;
      //  if(p->TimeInLastState != p->latestCPUBurst)
            p->dynamicPriority = p->dynamicPriority - 1;
        if (p->dynamicPriority == -1)
        {
            p->dynamicPriority = p->staticPriority - 1;
            expired_queue->push(p);
        }
        else
        {
            run_queue->push(p);
        }
    }

    Process* PriorityScheduler::getNextProcess()
    {
        if (run_queue->empty())
        {
            if (expired_queue->empty())
            {
                return NULL;
            }
            else
            {
                delete run_queue;
                run_queue = expired_queue;
                expired_queue = new std::priority_queue<Process*,std::vector<Process*>, Comparator>;
            }
        }
        Process* ans = run_queue->top();
        run_queue->pop();
       // ProcessCount--;
        return(ans);
    }

    bool Comparator::operator() (Process* a, Process* b)
    {
        if (a->dynamicPriority == b->dynamicPriority)
        {
            return a->SchedulerID > b->SchedulerID;
        }
        else
        {
            return a->dynamicPriority < b->dynamicPriority;
        }
    }

