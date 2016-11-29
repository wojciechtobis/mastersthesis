#include "genetic_algorithm.h"
#include "optim_problem.h"
#include "simulation.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>


void bubblesort(float table[], long long table2[], int size)
{
	int i, j;
    	float temp;
    	long long temp2;
    	for (i = 0; i<size-1; i++)
    	{
    		for (j=0; j<size-1-i; j++)
        	{
            		if (table[j] > table[j+1])
            		{
                		temp = table[j+1];
                		table[j+1] = table[j];
                		table[j] = temp;

                		temp2 = table2[j+1];
                		table2[j+1] = table2[j];
                		table2[j] = temp2;
            		}
        	}
    	}
}

void aggregation(float table[], float aggredated[], int size)
{
    int i;
    aggredated[0] = 1000*table[0];
    for(i=1 ; i<size ; ++i)
    {
        aggredated[i] = aggredated[i-1] + 1000*table[i];
    }
}

void fitness(long long population[], float fitness_val[], int size)
{
	int i;
	#pragma omp parallel for default(none) shared(fitness_val,population,size) private(i)
	for(i=0 ; i<size ; ++i)
    	{
        	fitness_val[i] = fitness_func(population[i]);
    	}
}

void roulette(long long population[], float roulette_agg[], int size)
{
	int i;
	float sum = 0.0,sum_roulette = 0.0;
	float roulette_val[size], roulette_norm[size], fitness_val[size];

	fitness(population,fitness_val,size);

	for(i=0 ; i<size ; ++i)
    	{
        	/*sum += fitness_val[i];
		if(sum==INFINITY || sum==NAN)
			sum = FLT_MAX;*/
		if(fitness_val[i]!=FLT_MAX)
			sum += fitness_val[i];
    	}
   
    	for(i=0 ; i<size ; ++i)
    	{
		if(fitness_val[i]!=FLT_MAX)
        		roulette_val[i] = sum/fitness_val[i];
		else
			roulette_val[i] = 0;
    	}
   
    	for(i=0 ; i<size ; ++i)
    	{
        	sum_roulette += roulette_val[i];
    	}

    	for(i=0 ; i<size ; ++i)
    	{
    		roulette_norm[i] = roulette_val[i]/sum_roulette;
    	}

    	bubblesort(roulette_norm, population, size);

    	aggregation(roulette_norm, roulette_agg, size);
}

void crossover1(long long * chrom1, long long * chrom2,int k)
{
    int i;
    long long temp_num1,temp1[LONG_LONG_BITS],temp_num2,temp2[LONG_LONG_BITS],tmp;
    temp_num1 = (*chrom1);
    temp_num2 = (*chrom2);

    for(i=LONG_LONG_BITS-1; i>=0 ; --i)
    {
        temp1[i] = temp_num1%2;
        temp2[i] = temp_num2%2;
        temp_num1 /= 2;
        temp_num2 /= 2;
    }

    for(i=k ; i<16 ; ++i)
    {
        tmp = temp1[i];
        temp1[i] = temp2[i];
        temp2[i] = tmp;
    }
   
    temp_num1 = 0;
    temp_num2 = 0;

    for(i=0 ; i<LONG_LONG_BITS ; ++i)
    {
        temp_num1 *= 2;
        temp_num2 *= 2;
        temp_num1 += temp1[i];
        temp_num2 += temp2[i];
    }

    (*chrom1) = temp_num1;
    (*chrom2) = temp_num2;
}   

void crossover2(long long * chrom1, long long * chrom2, int k)
{
    int i;
    long long dziel;
    long long temp_num1,temp_num2,tmp1=0,tmp2=0;
    temp_num1 = (*chrom1);
    temp_num2 = (*chrom2);

    dziel = 1ULL << (LONG_LONG_BITS-1);
    for(i=0 ; i<LONG_LONG_BITS ; ++i)
    {
        if(i<k)
        {
            tmp1 += dziel*(temp_num1/dziel);
            tmp2 += dziel*(temp_num2/dziel);
        }
        else
        {
            tmp2 += dziel*(temp_num1/dziel);
            tmp1 += dziel*(temp_num2/dziel);
        }
        temp_num1 %= dziel;
        temp_num2 %= dziel;
        dziel /= 2;
    }

    (*chrom1) = tmp1;
    (*chrom2) = tmp2;
}

void mutation1(long long *chrom,int k)
{
    long long temp = (*chrom);
    long long i = 1<<k;

    temp |= i;
    if((*chrom)==temp)
        temp &= (~i);
    (*chrom)=temp;
}

void new_population(long long population[], float roulette_val[], int size, int mut_prob)
{
	long long new_pop[size],temp1,temp2;
	int i,num;

	for(i=0 ; i<size ; ++i)
	{
		new_pop[i] = new_chromosome(population,roulette_val,size,rand()%1000+1);
	}
	
	for(i=0 ; i<size/2 ; ++i)
	{
		//num = rand()%4 + (LONG_LONG_BITS-4);
		num = rand()%PROC_BITS + (LONG_LONG_BITS-PROC_BITS);
		temp1 = new_pop[2*i];
		temp2 = new_pop[2*i+1];
		crossover2(&temp1,&temp2,num);
		new_pop[2*i] = temp1;
		new_pop[2*i+1] = temp2;
	}
	
	for(i=0 ; i<size ; ++i)
	{
		num = rand()%100;
		if(num<mut_prob)
		{
			temp1 = new_pop[i];
			mutation1(&temp1,rand()%PROC_BITS);
			population[i] = temp1;
		}
		else
			population[i] = new_pop[i];
	}
}

long long new_chromosome(long long population[], float roulette_val[], int size, int num)
{
	int i;

	for(i=0 ; i<size ; ++i)
	{
		if(num <= roulette_val[i])
			return population[i];
	}
	return -1;
}

