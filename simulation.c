#include "simulation.h"
#include "report.h"
#include <float.h>
#include <math.h>


/*int main()
{
	printf("Hello world\n");

	ControllerPID PID;
	PID.P = 1.0;
	PID.I = 0.0;
	PID.D = 0.0;

	ControllerLQR LQR;
	LQR.k1 = 1.0;
	LQR.k2 = 1.0;

	
	//simulation_PID(PID);
	float sim_val = simulation_LQR(LQR);

	printf("Val = %f\n",sim_val);

	return 0;
}*/

float simulation_PID(ControllerPID PID)
{
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

	State x0;
	x0.x1 = 5.0;
	x0.x2 = 0.0;

	
	float u[N];
	for(i=0;i<N;++i)
		u[i] = 0.0;
	
	RK4_PID(x,u,t,dtau,n,cn,x0,PID);

	printStates(x,x_size,t);

	free(x);
	free(t);

	return fit_func(x,u,x0,x_size,N);
	
}

float simulation_LQR(ControllerLQR LQR)
{
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

	State x0;
	x0.x1 = 5.0;
	x0.x2 = 0.0;

	
	float u[N];
	for(i=0;i<N;++i)
		u[i] = 0.0;
	
	RK4_LQR(x,u,t,dtau,n,cn,x0,LQR);

	//printStates(x,x_size,t);

	free(x);
	free(t);

	return fit_func(x,u,x0,x_size,N);
	
}

void RK4_PID(State x[], float u[], float* t, float dtau[], int n[], int cn[], State x_zad, ControllerPID PID)
{
	int i,j;
	float h,h2,h3,h6;
	State dx1,dx2,dx3,dx4,x1,x2,x3;

	for(j=0;j<N;++j)
	{
		h = dtau[j]/n[j];
		h2 = h/2;
		h3 = h/3;
		h6 = h/6;

		u[j] = -PID.P*(x[cn[j]-1].x1-x_zad.x1);

		for(i=cn[j]-1;i<(cn[j+1]-1);++i)
		{
			dx1 = rhs(x[i],u[j]);
			x1 = add_states(x[i],multiply_states(dx1,h2));
			dx2 = rhs(x1,u[j]);
			//x2.x1 = x[i].x1 + h2*dx2.x1;
			//x2.x2 = x[i].x2 + h2*dx2.x2;
			x2 = add_states(x[i],multiply_states(dx2,h2));
			dx3 = rhs(x2,u[j]);
			//x3.x1 = x[i].x1 + h*dx3.x1;
			//x3.x2 = x[i].x2 + h*dx3.x2;
			x3 = add_states(x[i],multiply_states(dx3,h));
			dx4 = rhs(x3,u[j]);
			
			x[i+1].x1 = x[i].x1 + h3*(dx2.x1+dx3.x1) + h6*(dx1.x1+dx4.x1);
			x[i+1].x2 = x[i].x2 + h3*(dx2.x2+dx3.x2) + h6*(dx1.x2+dx4.x2);

			t[i+1] = t[i] + h;
		}
	}


}

void RK4_LQR(State x[], float u[], float* t, float dtau[], int n[], int cn[], State x_zad, ControllerLQR LQR)
{
	int i,j;
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
			//x2.x1 = x[i].x1 + h2*dx2.x1;
			//x2.x2 = x[i].x2 + h2*dx2.x2;
			x2 = add_states(x[i],multiply_states(dx2,h2));
			dx3 = rhs(x2,u[j]);
			//x3.x1 = x[i].x1 + h*dx3.x1;
			//x3.x2 = x[i].x2 + h*dx3.x2;
			x3 = add_states(x[i],multiply_states(dx3,h));
			dx4 = rhs(x3,u[j]);
			
			x[i+1].x1 = x[i].x1 + h3*(dx2.x1+dx3.x1) + h6*(dx1.x1+dx4.x1);
			x[i+1].x2 = x[i].x2 + h3*(dx2.x2+dx3.x2) + h6*(dx1.x2+dx4.x2);

			t[i+1] = t[i] + h;
		}
	}


}

State rhs(const State x, float u)
{
	State dx;
	
	dx.x1 = x.x2;
	dx.x2 = -1.25*x.x2 + 1.3625*u;
	
	return dx;
} 

State add_states(const State s1, const State s2)
{
	State result;
	result.x1 = s1.x1 + s2.x1;
	result.x2 = s1.x2 + s2.x2;

	return result;
}

State multiply_states(const State s1, float s2)
{
	State result;
	result.x1 = s2*s1.x1;
	result.x2 = s2*s1.x2;

	return result;
}

float fit_func(State x[], float u[], State x_zad, int x_size, int u_size)
{
	int i;
	float sum = 0.0;
	for(i=0 ; i<x_size ; ++i)
	{
		sum = sum + h0*((x[i].x1-x_zad.x1)*(x[i].x1-x_zad.x1) + (x[i].x2-x_zad.x2)*(x[i].x2-x_zad.x2));
		if(sum==INFINITY || sum==NAN)
			return FLT_MAX;
	}
	
	for(i=0 ; i<u_size ; ++i)
	{
		sum = sum + u[i]*u[i];
		if(sum==INFINITY || sum==NAN)
			return FLT_MAX;
	}

	return sum;

}

