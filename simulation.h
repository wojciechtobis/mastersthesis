#ifndef simulation_h
#define simulation_h

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void simulation();
void RK4(float* x1, float* x2, float u[], float* t, float dtau[], int n[], int cn[], float x_zad1, float x_zad2, float P);
float* rhs(float x1, float x2);

#endif
