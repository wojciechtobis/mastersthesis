#ifndef report_h
#define report_h

#include"simulation.h"
#include <time.h>
#include <string.h>

void getDate(char* date);
void getStatesFileName(char* filename);
void printStates(const State* x,int x_size,float* t);

#endif
