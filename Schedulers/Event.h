#ifndef Event_h
#define Event_h

#include<iostream>
#include "Process.h"
using namespace std;

class Event
{

public:

    Process* EventProcess;
    int StateBefore;
    int StateAfter;
    int TimeStamp;
   // int PID;
    int TimeInLastState;
    Event* next;

    Event(Process*,int,int,int,int);
};
#endif
