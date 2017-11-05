#include<iostream>
#include "Event.h"
using namespace std;


    Event::Event(Process* currentProcess, int time, int nextState, int currentState,int previousStateTime)
    {
        EventProcess = currentProcess;
        TimeStamp = time;
        next = NULL;
        TimeInLastState = previousStateTime;
        //PID = pid;
        StateBefore = currentState;
        StateAfter = nextState;
    }
