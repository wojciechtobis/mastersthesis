#include "simulation.h"

#define N 100
#define T 10
#define h0 0.01

int main()
{
	printf("Hello world\n");
	
	/* N = 100;
	T = 100;
	tau = linspace(0,T,N+1);
	h0 = 0.01;
	dtau = diff(tau);
	n = ceil(dtau/h0);
	cn = cumsum([1,n]);


	x0 = [0; 0];
	x = zeros(cn(end),2);
	psi = zeros(cn(end),2);
	x(1,:) = x0;
	t = zeros(cn(end),1);
	t = czas(t,dtau,n,cn);

	u = zeros(N,1); */


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

	float* x1 = (float*)malloc(sizeof(float)*x_size);
	float* x2 = (float*)malloc(sizeof(float)*x_size);
	float* t = (float*)malloc(sizeof(float)*x_size);
	for(i=0;i<x_size;++i)
	{
		x1[i] = 0.0;
		x2[i] = 0.0;
		t[i] = 0.0;
	}

	float u[N];
	for(i=0;i<N;++i)
		u[i] = 0.0;
	

	for(i=0;i<N;++i)
		printf("%.2f,\t%.2f,\t%d,\n",tau[i],dtau[i],cn[i+1]);

	RK4(x1,x2,u,t,dtau,n,cn,1,1,1);

	free(x1);
	free(x2);
	free(t);
}

//[x,t,u] = RK4(x,u,t,dtau,n,cn,x_zad,reg);
void RK4(float* x1, float* x2, float u[], float* t, float dtau[], int n[], int cn[], float x_zad1, float x_zad2, float P)
{
	/*for j=1:length(n)
   h = dtau(j)/n(j);
   h2 = h/2;
   h3 = h/3;
   h6 = h/6;
 
   u(j) = -reg(1)*(x(cn(j),1)-x_zad(1));
   
   for i=cn(j):(cn(j+1)-1)
       dx1 = rhs(x(i,:), u(j));
       x1 = x(i,:) + h2*dx1;
       dx2 = rhs(x1, u(j));
       x2 = x(i,:) +h2*dx2;
       dx3 = rhs(x2,u(j));
       x3 = x(i,:) +h*dx3;
       dx4 = rhs(x3,u(j));
       x(i+1,:) = x(i,:) +h3*(dx2+dx3)+h6*(dx1+dx4);
       t(i+1) = t(i)+h;
   end
end*/

	int i,j;
	float h,h2,h3,h6;
	float dx1[2],dx2[2],dx3[2],dx4[2];

	for(j=0;j<N;++j)
	{
		h = dtau[j]/n[j];
		h2 = h/2;
		h3 = h/3;
		h6 = h/6;

		u[j] = -P*(x1[cn[j]]-x_zad1);

		for(i=cn[j];i<(cn[j+1]-1);++i)
		{
			dx1 = rhs(1,2);
		}

	}


}

float* rhs(float x1, float x2)
{

	float temp[2] = {x1,x2};

	return temp;
} 





