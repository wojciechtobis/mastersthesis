#include "report.h"
#include "simulation.h"

void printStates(const State* x,int x_size,float* t)
{
	int i;
	FILE *fpt;
	if((fpt=fopen("test.txt","w"))!=NULL)
	{

		printf("Hello world2 in printState %lf\n%lf\n\n",x[0].x1,x[0].x1);
		for(i=0;i<x_size;++i)
		{
			fprintf(fpt,"%f\t%f\t%f\n",t[i],x[i].x1,x[i].x2);
		}
	}

	fclose(fpt);
}	

