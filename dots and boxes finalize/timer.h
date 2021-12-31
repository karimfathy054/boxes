#ifndef TIMER_INCLUDED_H
#define TIMER_INCLUDED_H
#include <time.h>
#include <stdio.h>

time_t getTime(){
    //to record start time or any time
    time_t t = time(0);
    return t;
}

int getTimeSince(time_t initialTime){
    double diff = difftime(time(0), initialTime);
    return (int)diff;
}

int* convertTime(int t){
    //C doesnt allow returning the adress of a local variable
    static int timeArray[3];
    //hrs
    timeArray[0] = (t/3600);
    //mins
    timeArray[1] = (t%3600)/60;
    //secs
    timeArray[2] = (t%3600)%60;
    return timeArray;
}

void printTime(time_t start){
    int *tA = convertTime(getTimeSince(start));
    printf("Time since start: %02d:%02d:%02d\n", *(tA), *(tA+1), *(tA+2));
}


#endif