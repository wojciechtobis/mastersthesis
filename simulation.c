#include "simulation.h"

int main()
{
	printf("Hello world\n");

	simulation();

	return 0;
}

void simulation()
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
		//n[i] = (int)(dtau[i]/h0)+1;
		n[i] = (int)ceil(dtau[i]/h0);

	

	int cn[N+1];
	cn[0]=0;
	for(i=0;i<N;++i)
		cn[i+1] = cn[i]+n[i];

	int x_size = cn[N];

	State* x = (State*)malloc(sizeof(State)*x_size);
	float* t = (float*)malloc(sizeof(float)*x_size);
	
	t[0] = 0;

	State x0;
	x0.x1 = 5.0;
	x0.x2 = 0.0;

	float u[N];
	for(i=0;i<N;++i)
		u[i] = 0.0;
	

	//for(i=0;i<N;++i)
		//printf("%.2f,\t%.2f,\t%d,\n",tau[i],dtau[i],cn[i+1]);

	RK4(x,u,t,dtau,n,cn,x0,1);

	free(x);
	free(t);
	
	printf("Hello world2 %f\n\n\n",x[x_size-1].x1);

	for(i=0;i<x_size;++i)
	{
		printf("%f\t%f\n",x[i].x1,x[i].x2);
	}

	/*for(i=0;i<N;++i)
	{
		printf("%f\t\n",u[i]);
	}*/


	
}

void RK4(State x[], float u[], float* t, float dtau[], int n[], int cn[], State x_zad, float P)
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

		u[j] = -P*(x[cn[j]-1].x1-x_zad.x1);

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

State rhs(State x, float u)
{
	State dx;
	
	dx.x1 = x.x2;
	dx.x2 = -1.25*x.x2 + 1.3625*u;
	
	return dx;
} 

State add_states(State s1, State s2)
{
	State result;
	result.x1 = s1.x1 + s2.x1;
	result.x2 = s1.x2 + s2.x2;

	return result;
}

State multiply_states(State s1, float s2)
{
	State result;
	result.x1 = s2*s1.x1;
	result.x2 = s2*s1.x2;

	return result;
}
