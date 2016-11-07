#include "selection.h"
#include "optim_problem.h"
#include <stdlib.h>
#include <time.h>

/*float fitness_func(short x)
{
	return 8.0*(x-5.3)*(x-5.3);
}*/

void bubblesort(float table[], short table2[], int size)
{
	int i, j;
    	float temp;
    	short temp2;
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

void fitness(short population[], float fitness_val[], int size)
{
	int i;

	for(i=0 ; i<size ; ++i)
    	{
        	fitness_val[i] = fitness_func(population[i]);
    	}

}

void roulette(short population[], float roulette_agg[], int size)
{
	int i;
	float sum = 0.0,sum_roulette = 0.0;
	float roulette_val[size], roulette_norm[size], fitness_val[size];

	fitness(population,fitness_val,size);

	for(i=0 ; i<size ; ++i)
    	{
        	sum += fitness_val[i];
    	}
   
    	for(i=0 ; i<size ; ++i)
    	{
        	roulette_val[i] = sum/fitness_val[i];
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

void crossover1(short * chrom1, short * chrom2,int k)
{
    int i;
    short temp_num1,temp1[16],temp_num2,temp2[16],tmp;
    temp_num1 = (*chrom1);
    temp_num2 = (*chrom2);

    for(i=15 ; i>=0 ; --i)
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

    for(i=0 ; i<16 ; ++i)
    {
        temp_num1 *= 2;
        temp_num2 *= 2;
        temp_num1 += temp1[i];
        temp_num2 += temp2[i];
    }

    (*chrom1) = temp_num1;
    (*chrom2) = temp_num2;
}   

void crossover2(short * chrom1, short * chrom2, int k)
{
    int i,dziel;
    short temp_num1,temp_num2,tmp1=0,tmp2=0;
    temp_num1 = (*chrom1);
    temp_num2 = (*chrom2);

    dziel = 1 << 15;
    for(i=0 ; i<16 ; ++i)
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

void mutation1(short *chrom,int k)
{
    short temp = (*chrom);
    short i = 1<<k;

    temp |= i;
    if((*chrom)==temp)
        temp &= (~i);
    (*chrom)=temp;
}

void new_population(short population[], float roulette_val[], int size)
{
	short new_pop[size],temp1,temp2;
	int i,num;
	//srand(time(NULL));

	for(i=0 ; i<size ; ++i)
	{
		new_pop[i] = new_chromosome(population,roulette_val,size,rand()%1000+1);
	}
	
	for(i=0 ; i<size/2 ; ++i)
	{
		num = rand()%4 + 12;
		temp1 = new_pop[2*i];
		temp2 = new_pop[2*i+1];
		crossover2(&temp1,&temp2,num);
		new_pop[2*i] = temp1;
		new_pop[2*i+1] = temp2;
	}
	
	for(i=0 ; i<size ; ++i)
	{
		num = rand()%100;
		if(num<50)
		{
			temp1 = new_pop[i];
			mutation1(&temp1,rand()%5);
			population[i] = temp1;
		}
		else
			population[i] = new_pop[i];
	}
}

short new_chromosome(short population[], float roulette_val[], int size, int num)
{
	int i;

	for(i=0 ; i<size ; ++i)
	{
		if(num <= roulette_val[i])
			return population[i];
	}
	return -1;
}

