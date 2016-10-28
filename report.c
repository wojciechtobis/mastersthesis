#include "report.h"
#include "simulation.h"

void printStates(const State* x,int x_size,float* t)
{
	int i;
	FILE *fpt;
	char filename[40];
	getStatesFileName(filename);
	if((fpt=fopen(filename,"w"))!=NULL)
	{
		for(i=0;i<x_size;++i)
		{
			fprintf(fpt,"%f\t%f\t%f\n",t[i],x[i].x1,x[i].x2);
		}
	}

	fclose(fpt);
}	

void getDate(char * date)
{
	time_t tm_t;
    	struct tm * ptr;
    	time(&tm_t);
    	ptr = localtime(&tm_t);
    	strftime(date,32,"%d-%m-%Y %H:%M:%S",ptr); 
}

void getStatesFileName(char* filename)
{
	char date[20];	
	strcpy(filename,"States: ");
	getDate(date);
	strcat(filename,date);
	strcat(filename,".txt");
}
