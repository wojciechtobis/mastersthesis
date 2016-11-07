#include "optim_problem.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>



float fitness_func(long long x)
{
	short k1,k2;
	float k_1,k_2;
	
	decode(x,&k1,&k2);
	k_1 = (1.0*k1/(1 << (SHORT_BITS-1)))*(X_MAX-X_MIN) + X_MIN;
	k_2 = (1.0*k2/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;
	return (k_1-15.3)*(k_1-15.3) + (k_2-9.8)*(k_2-9.8);
}

long long code(short x, short y)
{
	return x + (y << SHORT_BITS);
}

void decode(long long code, short * x, short * y)
{
	(*x) = (short)code;
	(*y) = (short)(code >> SHORT_BITS);
}

void init_population(long long population[], int size)
{
	int i;
	for(i=0 ; i<size ; ++i)
	{
		population[i] = rand()%(1ULL<<PROC_BITS);
	}
}