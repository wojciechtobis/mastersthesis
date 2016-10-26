#ifndef simulation_h
#define simulation_h

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define N 200
#define T 20
#define h0 0.01

typedef struct State
{
	float x1;
	float x2;
} State;

typedef struct Controller
{
	float P;
	float I;
	float D;
} Controller;

void simulation();
void RK4(State x[], float u[], float* t, float dtau[], int n[], int cn[], State x_zad, Controller PID);
State rhs(const State x, float u);
State add_states(const State s1, const State s2);
State multiply_states(const State s1, float s2);

#endif
