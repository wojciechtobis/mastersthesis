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

typedef struct ControllerPID
{
	float P;
	float I;
	float D;
} ControllerPID;

typedef struct ControllerLQR
{
	float k1;
	float k2;
} ControllerLQR;

void simulation_PID(ControllerPID PID);
void simulation_LQR(ControllerLQR LQR);
void RK4_PID(State x[], float u[], float* t, float dtau[], int n[], int cn[], State x_zad, ControllerPID PID);
void RK4_LQR(State x[], float u[], float* t, float dtau[], int n[], int cn[], State x_zad, ControllerLQR LQR);
State rhs(const State x, float u);
State add_states(const State s1, const State s2);
State multiply_states(const State s1, float s2);

#endif
