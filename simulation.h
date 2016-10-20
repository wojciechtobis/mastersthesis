#ifndef simulation_h
#define simulation_h

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define N 100
#define T 10
#define h0 0.01

struct State
{
	float x1;
	float x2;
};

void simulation();
void RK4(struct State x[], float u[], float* t, float dtau[], int n[], int cn[], struct State x0, float P);
struct State rhs(struct State x, float u);

#endif
