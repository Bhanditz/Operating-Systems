#ifndef Process_h
#define Process_h

#include<iostream>
using namespace std;
#define STATIC_PRIORITY 4
#define CREATED 1
#define READY 2
#define RUNNING 3
#define BLOCKED 4
#define FINISH 5
#define PREEMPT 6

class Process
{

public:

    int ArrivalTime;
    int TotalCPUTime;
    int CPUBurst;
    int IOBurst;
    int state;
    int PID;
    int staticPriority;
    int dynamicPriority;
    int remainingTime;
    int latestCPUBurst;
    int latestIOBurst;
    int TimeInLastState;
    int LastStateTimeStamp;
    int remainingCPUBurst;
    int finishingTime;
    int priority;
    int TotalIOTime;
    int TotalCPUWaitingTime;
    int SchedulerID;
    Process* next;
    void readCurrentProcess();
    Process(int,int,int,int,int,int);

};
#endif
