#ifndef UtilityFunctions_h
#define UtilityFunctions_h

#include "Event.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>

using namespace std;

class UtilityFunctions
{
public:

    ifstream randNumFile;
    int offset;
    int randNumCount;
    int PID;
    int* randomValueArray;
    string randomNumberFileName;
    UtilityFunctions(string);
    int convertStringToInteger(string);
    int getRandomNumber(int);
    void sortedInsert(Event*&,Event*&);
    void printEventQueue(Event*);
    void verboseOutput(Event*);
    void finalOutput(Process*);
    void printState(int);
    int randFileIteration;
};

#endif
