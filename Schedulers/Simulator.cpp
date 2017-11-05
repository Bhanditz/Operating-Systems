/**
Author: Kumar Mehta
Operating Systems: Implementing a scheduler through discrete event simulation

*/


#include<iostream>
#include<vector>
#include "Process.h"
#include "UtilityFunctions.h"
#include "Scheduler.h"
#include "FCFS.h"
#include "PriorityScheduler.h"
#include "LCFS.h"
#include "SJF.h"
#include "RRS.h"
//#include "Enums.h"
#include "Event.h"
#include<fstream>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include<sstream>
#include <iomanip>
#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
using namespace std;

class ProcessList
{

public:

    vector<Process*> inputProcesses;
    ifstream randNumFile;
    int numberOfProcesses;
    UtilityFunctions* functionsObject;

    ProcessList(UtilityFunctions* object)
    {
        numberOfProcesses = 0;
        functionsObject = object;
    }

    void readInput(string inputFileName)
    {
        ifstream inputFile;
        inputFile.open(inputFileName);
        if(!inputFile.is_open())
            cout<<"ERROR! Unable to open file!";
        else
        {
            string token;
            int AT,CT,CB,IB;
            int randNumber;
            while(inputFile>>token)
            {
              //  cout<<"while";
                AT = functionsObject->convertStringToInteger(token);
                inputFile>>token;
                CT = functionsObject->convertStringToInteger(token);
                inputFile>>token;
                CB = functionsObject->convertStringToInteger(token);
                inputFile>>token;
                IB = functionsObject->convertStringToInteger(token);
                randNumber = functionsObject->getRandomNumber(STATIC_PRIORITY);
              //  cout<<"r: "<<randNumber<<" ";
                Process* temp = new Process(AT,CT,CB,IB,randNumber,numberOfProcesses);
                inputProcesses.push_back(temp);
                numberOfProcesses++;
            //    cout<<AT<<" "<<CT<<" "<<CB<<" "<<IB<<endl;
            }

        }
    }

    void traverseProcessList()
    {
        for(int i = 0 ; i < numberOfProcesses ; i++)
        {
            cout<<inputProcesses[i]->PID<<" "<<inputProcesses[i]->ArrivalTime<<endl;
        }
    }



};


int main(int argc, char* argv[])
{
    bool v_flag = 0;
    char *argScheduler = NULL;
    int index;
    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "vs:")) != -1)
    switch (c)
    {
        case 'v':
            {
                v_flag = 1;
                break;
            }
          case 's':
            {
                argScheduler = optarg;
                break;
            }
          case '?':
            {
                if (optopt == 's')
                {
                    std::fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                }
                else if (std::isprint(optopt))
                {
                    std::fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                }
                else
                {
                    std::fprintf(stderr, "Unknown option character `\\x%x'.\n",optopt);
                }
                return 1;
            }
          default:
                exit(1);
    }
    string SchedulerArg(argScheduler);
  //  cout<<argc<<endl;
   // cout<<SchedulerArg<<" "<<argv[optind]<<" "<<argv[optind + 1]<<endl;
    Event* EventQueueTail = NULL;
    string argInputFile = argv[optind];
    string argRandFile = argv[optind + 1];
    UtilityFunctions* functions = new UtilityFunctions(argRandFile);
    int argTimeQuantum = INT_MAX;
    if(argScheduler[0] == 'R' || argScheduler[0] == 'P')
    {
        string timeQ = SchedulerArg.substr(1);
        argTimeQuantum = functions->convertStringToInteger(timeQ);
    }
    //cout<<argTimeQuantum<<endl;
    ProcessList* currentList = new ProcessList(functions);
    Event* EventQueueHead = NULL;
    currentList->readInput(argInputFile);
   // currentList->traverseProcessList();
    for(int i = 0 ; i < currentList->numberOfProcesses ; i++)
    {
    //    cout<<i;
        Event* temp = new Event(currentList->inputProcesses[i],currentList->inputProcesses[i]->ArrivalTime, READY, CREATED, 0);
        functions->sortedInsert(EventQueueHead,temp);
    }

    Event* simulation = EventQueueHead;
    Scheduler* OSschedular;
    if(argScheduler[0] == 'F')
        OSschedular = new FCFS(argScheduler,argTimeQuantum);
    else if(argScheduler[0] == 'S')
        OSschedular = new SJF(argScheduler,argTimeQuantum);
    else if(argScheduler[0] == 'L')
        OSschedular = new LCFS(argScheduler,argTimeQuantum);
    else if(argScheduler[0] == 'R')
        OSschedular = new RRS(argScheduler,argTimeQuantum);
    else
        OSschedular = new PriorityScheduler(argScheduler,argTimeQuantum);
    //cout<<EventQueueHead->next->StateBefore;
    int ProcessesInBlocked = 0;
    int IOStart = 0;
    double TotalIOTime = 0.0;

/**
After creating events given in the input file, Simulation of events starts here
*/
    while(simulation)
    {
    //    functions->printEventQueue(simulation);
       // cout<<simulation->StateBefore;
      //  cout<<"simulation";
        bool CALL_SCHEDULER = false;
        int CURRENT_TIME = simulation->TimeStamp;
        simulation->EventProcess->TimeInLastState = CURRENT_TIME - simulation->EventProcess->LastStateTimeStamp;
        simulation->EventProcess->LastStateTimeStamp = CURRENT_TIME;
       //cout<<simulation->StateAfter;
        switch(simulation->StateAfter)
        { // which state to transition to?

            case READY:
                {
                    if(simulation->StateBefore == BLOCKED)
                    {
                        ProcessesInBlocked--;
                        if(ProcessesInBlocked == 0)
                        {
                            TotalIOTime += (CURRENT_TIME - IOStart);
                        }
                    }
                    if(v_flag)
                        functions->verboseOutput(simulation);
                    OSschedular->addProcessToQueue(simulation->EventProcess);
                    simulation->EventProcess->state = READY;
                    CALL_SCHEDULER = true; // conditional on whether something is run
    //                cout<<"Done";
                    break;
                }
            // must add to run queue

            case RUNNING:
            // create event for either preemption or blocking
            {
                OSschedular->currentRunningProcess = simulation->EventProcess;
         //       cout<<"RUNNING";
                simulation->EventProcess->state = RUNNING;
                int actualBurst,processMaxCPUBurst;
              //  cout<<simulation->EventProcess->remainingCPUBurst<<" ";
                if(simulation->EventProcess->remainingCPUBurst <= 0)
                {
                    processMaxCPUBurst = simulation->EventProcess->CPUBurst;
                    actualBurst = functions->getRandomNumber(processMaxCPUBurst);
                }
                else
                {
                    actualBurst = simulation->EventProcess->remainingCPUBurst;
                }
                simulation->EventProcess->latestCPUBurst = actualBurst;
                simulation->EventProcess->remainingCPUBurst = actualBurst;

                int CPUBurst = OSschedular->timeQuantum;
                bool ProcessWillComplete = false;
                bool preempted = true;
                if(actualBurst <= CPUBurst)
                {
                    preempted = false;
                    CPUBurst = actualBurst;
                }
                if(simulation->EventProcess->remainingTime <= CPUBurst)
                {
                    ProcessWillComplete = true;
                    CPUBurst = simulation->EventProcess->remainingTime;
                }
                simulation->EventProcess->remainingCPUBurst -= CPUBurst;
                simulation->EventProcess->TotalCPUWaitingTime += simulation->EventProcess->TimeInLastState;
                if(v_flag)
                    functions->verboseOutput(simulation);
                Event* temp;
                if(ProcessWillComplete)
                    temp = new Event(simulation->EventProcess,CURRENT_TIME + CPUBurst, FINISH, RUNNING, CPUBurst);
                else if(!preempted)
                    temp = new Event(simulation->EventProcess,CURRENT_TIME + CPUBurst, BLOCKED, RUNNING, CPUBurst);
                else
                    temp = new Event(simulation->EventProcess,CURRENT_TIME + CPUBurst, PREEMPT, RUNNING, CPUBurst);
                functions->sortedInsert(simulation,temp);
                break;
            }
            case BLOCKED:
            //create an event for when process becomes READY again
            {
                if(ProcessesInBlocked == 0)
                    IOStart = CURRENT_TIME;
                ProcessesInBlocked++;
                OSschedular->currentRunningProcess = NULL;
                simulation->EventProcess->state = BLOCKED;
                int processMaxIOBurst = simulation->EventProcess->IOBurst;
                int IOBurst = functions->getRandomNumber(processMaxIOBurst);
                simulation->EventProcess->latestIOBurst = IOBurst;
                simulation->EventProcess->TotalIOTime += IOBurst;
                simulation->EventProcess->dynamicPriority = simulation->EventProcess->staticPriority;
                simulation->EventProcess->remainingTime = simulation->EventProcess->remainingTime - simulation->TimeInLastState;
             //   simulation->EventProcess->remainingCPUBurst -= simulation->TimeInLastState;
                if(v_flag)
                    functions->verboseOutput(simulation);
                Event* temp = new Event(simulation->EventProcess,CURRENT_TIME + IOBurst, READY, BLOCKED, IOBurst);
                functions->sortedInsert(simulation,temp);
                CALL_SCHEDULER = true;
                break;
            }
            case PREEMPT:
            // add to runqueue (no event is generated)
            {
                OSschedular->currentRunningProcess = NULL;
                simulation->EventProcess->remainingTime = simulation->EventProcess->remainingTime - simulation->TimeInLastState;
                OSschedular->addProcessToQueue(simulation->EventProcess);
            //    simulation->EventProcess->remainingCPUBurst -= OSschedular->timeQuantum;
                //simulation->StateAfter = READY;
                if(v_flag)
                    functions->verboseOutput(simulation);
                CALL_SCHEDULER = true;
                break;
            }
            case FINISH:
            {
                OSschedular->currentRunningProcess = NULL;
                simulation->EventProcess->finishingTime = CURRENT_TIME;
                if(v_flag)
                    functions->verboseOutput(simulation);
                //cout<<simulation->EventProcess->PID<<" Done!"<<endl;
                //OSschedular->ProcessesInReadyQueue
                CALL_SCHEDULER = true;
                break;
            }
        }
        //remove current event object from Memory
        Event* current = simulation;
        simulation = simulation->next;
        EventQueueHead = simulation;
        delete current;
        if(CALL_SCHEDULER)
        {
           // cout<<"scheduler";
            if (simulation && simulation->TimeStamp == CURRENT_TIME)
            {
                continue;//process next event from Event queue
            }
            CALL_SCHEDULER = false;
            Process* CURRENT_RUNNING_PROCESS = OSschedular->currentRunningProcess;
            if (CURRENT_RUNNING_PROCESS == NULL)
            {
             //   cout<<"yes";
                CURRENT_RUNNING_PROCESS = OSschedular->getNextProcess();
                if (CURRENT_RUNNING_PROCESS == NULL)
                {
      //              cout<<"continue";
                continue;
                }
        //        cout<<"here";
            //    functions->printEventQueue(simulation);
                Event* temp = new Event(CURRENT_RUNNING_PROCESS, CURRENT_TIME, RUNNING, READY, 0);
                functions->sortedInsert(simulation,temp);
                // create event to make process runnable for same time.
            }
        }
    }
    cout<<OSschedular->schedulerType;
    if(argScheduler[0] == 'R' || argScheduler[0] == 'P')
        cout<<" "<<OSschedular->timeQuantum;
    cout<<endl;
    int LastFinishingTime = 0;
    double TotalTurnaroundTime = 0.0;
    double TotalCPUWaitingTime = 0.0;
    double TotalCPUTimes = 0.0;
    double FinalTotalIOTime = 0.0;
    double noOfProcesses = currentList->numberOfProcesses;
    for(int i = 0 ; i < noOfProcesses ; i++)
    {
        functions->finalOutput(currentList->inputProcesses[i]);
        TotalTurnaroundTime += (currentList->inputProcesses[i]->finishingTime - currentList->inputProcesses[i]->ArrivalTime);
        TotalCPUWaitingTime += currentList->inputProcesses[i]->TotalCPUWaitingTime;
        FinalTotalIOTime = FinalTotalIOTime + currentList->inputProcesses[i]->TotalIOTime;
        TotalCPUTimes += currentList->inputProcesses[i]->TotalCPUTime;
        if(currentList->inputProcesses[i]->finishingTime > LastFinishingTime)
            LastFinishingTime = currentList->inputProcesses[i]->finishingTime;
    }
	double cpuUtil = 0.0;
	double ioUtil  = 0.0;
	ioUtil = (TotalIOTime * 100.0)/LastFinishingTime;
	cpuUtil = (TotalCPUTimes * 100.0)/LastFinishingTime;
	double avgTurnaroundTime = TotalTurnaroundTime/noOfProcesses;
	double avgCPUWaitingTime = TotalCPUWaitingTime/noOfProcesses;
	double Throughput = (noOfProcesses*100.0)/LastFinishingTime;
	cout<<"SUM: "<<LastFinishingTime<<" "<<std::fixed << setprecision(2)<<cpuUtil<<" "<<ioUtil<<" "<<avgTurnaroundTime<<" "<<avgCPUWaitingTime<<std::fixed << setprecision(3)<<" "<<Throughput<<endl;

    return(0);
}
