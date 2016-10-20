#include "simulation.h"

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

	struct State* x = (struct State*)malloc(sizeof(struct State)*x_size);
	float* t = (float*)malloc(sizeof(float)*x_size);

	struct State x0;
	x0.x1 = 0.0;
	x0.x2 = 0.0;

	float u[N];
	for(i=0;i<N;++i)
		u[i] = 0.0;
	

	//for(i=0;i<N;++i)
		//printf("%.2f,\t%.2f,\t%d,\n",tau[i],dtau[i],cn[i+1]);

	RK4(x,u,t,dtau,n,cn,x0,1);

	free(x);
	free(t);
	
	printf("Hello world2\n");
	
}

void RK4(struct State x[], float u[], float* t, float dtau[], int n[], int cn[], struct State x0, float P)
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
	struct State dx1,dx2,dx3,dx4,x1,x2,x3;

	for(j=0;j<N;++j)
	{
		h = dtau[j]/n[j];
		h2 = h/2;
		h3 = h/3;
		h6 = h/6;

		u[j] = -P*(x[cn[j]].x1-x0.x1);

		for(i=cn[j];i<(cn[j+1]-1);++i)
		{
			dx1 = rhs(x[i],u[j]);
			x1.x1 = x[i].x1 + h2*dx1.x1;
			x1.x2 = x[i].x2 + h2*dx1.x2;
			dx2 = rhs(x1,u[j]);
			x2.x1 = x[i].x1 + h2*dx2.x1;
			x2.x2 = x[i].x2 + h2*dx2.x2;
			dx3 = rhs(x2,u[j]);
			x3.x1 = x[i].x1 + h*dx3.x1;
			x3.x2 = x[i].x2 + h*dx3.x2;
			dx4 = rhs(x3,u[j]);
			
		}

	}


}

struct State rhs(struct State x, float u)
{
	struct State dx;
	
	dx.x1 = x.x2;
	dx.x1 = x.x2 + u;
	
	return dx;
} 





