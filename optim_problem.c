#include "optim_problem.h"
#include <math.h>
#include <stdlib.h>



float fitness_func(long long x)
{
	//return 8.0*(x-5.3)*(x-5.3);
	short x1,y1;
	float x_1,y_1;
	
	decode(x,&x1,&y1);
	x_1 = (1.0*x1/(1 << (SHORT_BITS-1)))*(X_MAX-X_MIN) + X_MIN;
	y_1 = (1.0*y1/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;
	return (x_1-5.3)*(x_1-5.3) + (y_1-5.8)*(y_1-5.8);
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