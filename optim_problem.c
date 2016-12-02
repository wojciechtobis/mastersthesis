#include "simulation.h"
#include "optim_problem.h"
#include <math.h>
#include <stdlib.h>
#include <float.h>



/*float fitness_func(long long x)
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
}*/

float fitness_func(long long x_long)
{
	short k1,k2;
	float k_1,k_2,result;
	
	decode(x_long,&k1,&k2);
	k_1 = (1.0*(unsigned short)k1/(1 << (SHORT_BITS)))*(X_MAX-X_MIN) + X_MIN;
	k_2 = (1.0*(unsigned short)k2/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;

	ControllerLQR LQR;
	LQR.k1 = k_1;
	LQR.k2 = k_2;

	
	int i;
	float temp = 1.0*T/N;

	float tau[N+1];

	for(i=0;i<N+1;++i)
		tau[i] = temp*i;

	float dtau[N];
	for(i=0;i<N;++i)
		dtau[i] = tau[i+1]-tau[i];
	
	int n[N];
	for(i=0;i<N;++i)
		n[i] = (int)ceil(dtau[i]/h0);

	int cn[N+1];
	cn[0]=0;
	for(i=0;i<N;++i)
		cn[i+1] = cn[i]+n[i];

	int x_size = cn[N];

	State* x = (State*)malloc(sizeof(State)*x_size);
	float* t = (float*)malloc(sizeof(float)*x_size);

	t[0] = 0;

	x[0].x1 = 0.0;
	x[0].x2 = 0.0;

	State x_zad;
	x_zad.x1 = 5.0;
	x_zad.x2 = 0.0;

	
	float u[N];
	for(i=0;i<N;++i)
		u[i] = 0.0;
	
	int j;
	float h,h2,h3,h6;
	State dx1,dx2,dx3,dx4,x1,x2,x3;

	for(j=0;j<N;++j)
	{
		h = dtau[j]/n[j];
		h2 = h/2;
		h3 = h/3;
		h6 = h/6;

		u[j] = -LQR.k1*(x[cn[j]-1].x1-x_zad.x1) - LQR.k2*(x[cn[j]-1].x2-x_zad.x2);

		for(i=cn[j]-1;i<(cn[j+1]-1);++i)
		{
			dx1 = rhs(x[i],u[j]);
			x1 = add_states(x[i],multiply_states(dx1,h2));
			dx2 = rhs(x1,u[j]);
			x2 = add_states(x[i],multiply_states(dx2,h2));
			dx3 = rhs(x2,u[j]);
			x3 = add_states(x[i],multiply_states(dx3,h));
			dx4 = rhs(x3,u[j]);
			
			x[i+1].x1 = x[i].x1 + h3*(dx2.x1+dx3.x1) + h6*(dx1.x1+dx4.x1);
			x[i+1].x2 = x[i].x2 + h3*(dx2.x2+dx3.x2) + h6*(dx1.x2+dx4.x2);

			t[i+1] = t[i] + h;
		}
	}

	float sum = 0.0;
	for(i=0 ; i<x_size ; ++i)
	{
		sum = sum + h0*((x[i].x1-x_zad.x1)*(x[i].x1-x_zad.x1) + (x[i].x2-x_zad.x2)*(x[i].x2-x_zad.x2));
		if(sum==INFINITY || sum==NAN)
			return FLT_MAX;
	}
	
	for(i=0 ; i<N ; ++i)
	{
		sum = sum + u[i]*u[i];
		if(sum==INFINITY || sum==NAN)
			return FLT_MAX;
	}

	result = sum;

	free(x);
	free(t);

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
