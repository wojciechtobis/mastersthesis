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

void getPopulationsFileName(char* filename)
{
	char date[20];	
	strcpy(filename,"Populations: ");
	getDate(date);
	strcat(filename,date);
	strcat(filename,".txt");
}

/*long long printPopulation(const long long population[],const float fitness_val[],int population_size, int population_number,long long global_best)
{
	int i,i_best=population_size+1;	
	short x,y;
	float x1,y1,fitness_sum=0.0,fitness_best=1000.0;
	FILE *fpt;
	char filename[40];
	getPopulationsFileName(filename);
	if((fpt=fopen(filename,"a"))!=NULL)
	{
		fprintf(fpt,"Popation number: %d\n",population_number);
		fprintf(fpt,"%10s%10s%15s%15s%25s\n","x","y","x1","y1","fitness");
		for(i=0 ; i<population_size ; ++i)
	    	{

			decode(population[i],&x,&y);
			x1 = (1.0*x/(1 << (SHORT_BITS-1)))*(X_MAX-X_MIN) + X_MIN;
			y1 = (1.0*y/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;
	    	//printf("(%hi,%hi) ",x,y);
			fprintf(fpt,"%10hu%10hu%15.4f%15.4f%25.15f\n",x,y,x1,y1,fitness_val[i]);
			fitness_sum += fitness_val[i];
			if(fitness_val[i]<fitness_best)
			{
				fitness_best = fitness_val[i];
				i_best = i;
			}
	    	}

		decode(population[i_best],&x,&y);
		x1 = (1.0*x/(1 << (SHORT_BITS-1)))*(X_MAX-X_MIN) + X_MIN;
		y1 = (1.0*y/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;

		fprintf(fpt,"\nBest in population:\n");
		fprintf(fpt,"%hu\t->\t%.4f\n",x,x1);
		fprintf(fpt,"%hu\t->\t%.4f\n",y,y1);
		fprintf(fpt,"fitness value: %.15f\n",fitness_val[i_best]);
		fprintf(fpt,"fittness sum: %.15f\n",fitness_sum);

		if(fitness_func(global_best)>fitness_val[i_best])
		{
			global_best=population[i_best];
		}

		decode(global_best,&x,&y);
		x1 = (1.0*x/(1 << (SHORT_BITS-1)))*(X_MAX-X_MIN) + X_MIN;
		y1 = (1.0*y/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;

		fprintf(fpt,"\nGlobal best:\n");
		fprintf(fpt,"%hu\t->\t%.4f\n",x,x1);
		fprintf(fpt,"%hu\t->\t%.4f\n",y,y1);
		fprintf(fpt,"fitness value: %.15f\n",fitness_func(global_best));

		fprintf(fpt,"\n\n\n\n");
	}
	return global_best;
}*/


long long printPopulation(const long long population[],const float fitness_val[],int population_size, int population_number,long long global_best)
{
	int i,i_best=0;	
	short x,y;
	float x1,y1,fitness_sum=0.0,fitness_best=fitness_val[0];

	printf("Popation number: %d\n",population_number);
	printf("%10s%10s%15s%15s%57s\n","x","y","x1","y1","fitness");
	for(i=0 ; i<population_size ; ++i)
    	{

		decode(population[i],&x,&y);
		x1 = (1.0*(unsigned short)x/(1 << (SHORT_BITS)))*(X_MAX-X_MIN) + X_MIN;
		y1 = (1.0*(unsigned short)y/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;
    	//printf("(%hi,%hi) ",x,y);
		printf("%10llu%10hu%10hu%15.4f%15.4f%57.15f\n",population[i],x,y,x1,y1,fitness_val[i]);
		fitness_sum += fitness_val[i];
		if(fitness_val[i]<fitness_best)
		{
			fitness_best = fitness_val[i];
			i_best = i;
		}
    	}

	decode(population[i_best],&x,&y);
	x1 = (1.0*(unsigned short)x/(1 << (SHORT_BITS)))*(X_MAX-X_MIN) + X_MIN;
	y1 = (1.0*(unsigned short)y/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;

	printf("\nBest in population:\n");
	printf("%hu\t->\t%.4f\n",x,x1);
	printf("%hu\t->\t%.4f\n",y,y1);
	printf("fitness value: %.15f\n",fitness_val[i_best]);
	printf("fittness sum: %.15f\n",fitness_sum);

	if(fitness_func(global_best)>fitness_val[i_best])
	{
		global_best=population[i_best];
	}

	decode(global_best,&x,&y);
	x1 = (1.0*(unsigned short)x/(1 << (SHORT_BITS)))*(X_MAX-X_MIN) + X_MIN;
	y1 = (1.0*(unsigned short)y/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;

	printf("\nGlobal best:\n");
	printf("%hu\t->\t%.4f\n",x,x1);
	printf("%hu\t->\t%.4f\n",y,y1);
	printf("fitness value: %.15f\n",fitness_func(global_best));

	printf("\n\n\n\n");

	return global_best;
}





