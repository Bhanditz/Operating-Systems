#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include <algorithm>
#include<iomanip>
#include<stdlib.h>
#include "Event.h"
#include "Process.h"
#include "UtilityFunctions.h"

using namespace std;


    UtilityFunctions::UtilityFunctions(string randomNumberFile)
    {
        randomNumberFileName = randomNumberFile;
        randNumFile.open(randomNumberFile);
        if(randNumFile.is_open())
        {
            randNumFile>>randNumCount;
            offset = 0;
        }
        else
        {
            cout<<"Unable to open Random number file!"<<endl;
        }
        randFileIteration = 1;
    }

    int UtilityFunctions::getRandomNumber(int burst)
    {
        int ans;
        randNumFile>>ans;
        ans = ans % burst;
        offset = offset + 1;
        if(offset == randNumCount)
        {
            randNumFile.close();
            randNumFile.open(randomNumberFileName);
            randNumFile>>randNumCount;
            offset = 0;
            randFileIteration++;
        }
        ans = ans+1;
   //     cout<<"r: "<<ans<<endl;
        return(ans);
    }

    int UtilityFunctions::convertStringToInteger(string s)
    {
        stringstream convert(s);
        int ans;
        convert >> ans;
        return(ans);
    }

    void UtilityFunctions::sortedInsert(Event*& head, Event*& newEvent)
    {
        if(head == NULL)
            head = newEvent;
        else
        {
            Event* iter = head;
            Event* prev = head;
            int newTimeStamp = newEvent->TimeStamp;
            while(iter && iter->TimeStamp <= newTimeStamp)
            {
    //            cout<<iter->PID<<endl;
                prev = iter;
                iter = iter->next;
            }
            if(iter == head)
            {
                newEvent->next = head;
                head = newEvent;
            }
            else
            {
                newEvent->next = iter;
                prev->next = newEvent;
            }
        }
    }

    void UtilityFunctions::printEventQueue(Event* head)
    {
        cout<<endl;
        while(head)
        {
            cout<<head->EventProcess->PID<<" "<<head->StateBefore<<" "<<head->StateAfter<<endl;
            head = head->next;
        }
    }

    void UtilityFunctions::verboseOutput(Event* e)
    {
        if(e->StateAfter == 6)
        {
            cout<<e->TimeStamp<<" "<<e->EventProcess->PID<<" "<<e->EventProcess->TimeInLastState<<": ";
            printState(e->StateBefore);
            cout<<" -> "<<READY<<" ";
            cout<<"cb="<<e->EventProcess->latestCPUBurst<<" rem="<<e->EventProcess->remainingTime<<" prio="<<e->EventProcess->dynamicPriority;
            cout<<endl;
            return;
        }
        if(e->StateAfter == 5)
        {
            cout<<e->TimeStamp<<" "<<e->EventProcess->PID<<" "<<e->EventProcess->TimeInLastState<<": Done"<<endl;
            return;
        }
        cout<<e->TimeStamp<<" "<<e->EventProcess->PID<<" "<<e->EventProcess->TimeInLastState<<": ";
        printState(e->StateBefore);
        cout<<" -> ";
        printState(e->StateAfter);
        cout<<" ";
        if(e->StateBefore == 2)
        {
            cout<<"cb="<<e->EventProcess->latestCPUBurst<<" rem="<<e->EventProcess->remainingTime<<" prio="<<e->EventProcess->dynamicPriority;
        }
        else if(e->StateBefore == 3)
        {
            cout<<"ib="<<e->EventProcess->latestIOBurst<<" rem="<<e->EventProcess->remainingTime;
        }
        cout<<endl;
    }

    void UtilityFunctions::finalOutput(Process* p)
    {
        printf("%04d: %4d %4d %4d %4d %1d | %5d %5d %5d %5d\n",
        p->PID,p->ArrivalTime,p->TotalCPUTime,p->CPUBurst,p->IOBurst, p->staticPriority,
        p->finishingTime, p->finishingTime - p->ArrivalTime, p->TotalIOTime, p->TotalCPUWaitingTime);
     //   cout<<setfill('0')<<setw(4)<<p->staticPriority<<":\t"<<p->ArrivalTime<<"\t"<<p->TotalCPUTime<<"\t"<<p->CPUBurst<<"\t"<<p->IOBurst<<" "<<p->priority<<" |\t";
      //  cout<<p->finishingTime<<"\t"<<(p->finishingTime - p->ArrivalTime)<<"\t"<<p->TotalIOTime<<"\t"<<p->TotalCPUWaitingTime<<endl;
    }

    void UtilityFunctions::printState(int state)
    {
        if(state == CREATED)
            cout<<"CREATED";
        else if(state == RUNNING)
            cout<<"RUNNING";
        else if(state == READY)
            cout<<"READY";
        else if(state == BLOCKED)
            cout<<"BLOCKED";
        else if(state == FINISH)
            cout<<"FINISH";

    }

