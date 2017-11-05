#include<iostream>
#include "Process.h"
using namespace std;


    Process::Process(int AT, int CT,int CB, int IB, int staticPriorityInput, int pid)
    {
        ArrivalTime = AT;
        TotalCPUTime = CT;
        CPUBurst = CB;
        IOBurst = IB;
        state = CREATED;
        staticPriority = staticPriorityInput;
        dynamicPriority = staticPriority;
        PID = pid;
        remainingTime = TotalCPUTime;
        next = NULL;
        latestCPUBurst = 0;
        latestIOBurst = 0;
        TimeInLastState = 0;
        LastStateTimeStamp = AT;
        remainingCPUBurst = 0;
        finishingTime = 0;
        priority = 0;
        TotalIOTime = 0;
        TotalCPUWaitingTime = 0;
    }

    void Process::readCurrentProcess()
    {
        cout<<ArrivalTime<<"\t"<<TotalCPUTime<<"\t"<<CPUBurst<<"\t"<<IOBurst<<"\t"<<state<<endl;
    }
