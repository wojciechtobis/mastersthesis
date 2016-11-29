#include "simulation.h"
#include "optim_problem.h"
#include <math.h>
#include <stdlib.h>



float fitness_func(long long x)
{
	short k1,k2;
	float k_1,k_2,result;
	
	decode(x,&k1,&k2);
	k_1 = (1.0*(unsigned short)k1/(1 << (SHORT_BITS)))*(X_MAX-X_MIN) + X_MIN;
	k_2 = (1.0*(unsigned short)k2/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;

	ControllerLQR LQR;
	LQR.k1 = k_1;
	LQR.k2 = k_2;

	result = simulation_LQR(LQR);

	return result;
}

long long code(short x, short y)
{
	return x + (y << SHORT_BITS);
}

void decode(long long code, short * x, short * y)
{
	(*x) = (short)code;
	(*y) = (short)(code >> (SHORT_BITS));
}

void init_population(long long population[], int size)
{
	int i;
	for(i=0 ; i<size ; ++i)
	{
		population[i] = rand()%(1ULL<<(PROC_BITS));
	}
}
