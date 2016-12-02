#include <stdio.h>
#include "genetic_algorithm.h"
#include "optim_problem.h"
#include "report.h"
#include "simulation.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_POP 100
#define MUT_PROB 50
#define MAX_ITER 200

int main()
{
	int j,j_best;
    	long long populacja[MAX_POP],global_best;
    	float roulette_val[MAX_POP],fitness_val[MAX_POP],fitness_sum,fitness_sum_best=1000.0;
    	srand(time(NULL));

	initTime();

	init_population(populacja,MAX_POP);
	global_best = populacja[0];
	
	for(j=0, j_best=0 ; j<MAX_ITER ; ++j)
	{
	    	roulette(populacja,roulette_val,MAX_POP);

		new_population(populacja,roulette_val,MAX_POP,MUT_PROB); //may be parallelised
		fitness(populacja,fitness_val,MAX_POP);

		//global_best=printPopulation(populacja,fitness_val,MAX_POP,j+1,global_best);
		global_best = getBest(populacja,fitness_val,MAX_POP,j+1,global_best);
		fitness_sum = 0;
		if(fitness_sum_best>fitness_sum)
		{
			fitness_sum_best = fitness_sum;
			j_best = j;
		}

	}
	short x,y;
	float x1,y1;
	printf("\n\n");
	decode(global_best,&x,&y);
	x1 = (1.0*(unsigned short)x/(1 << (SHORT_BITS)))*(X_MAX-X_MIN) + X_MIN;
	y1 = (1.0*(unsigned short)y/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;

	printf("\nGlobal best:\n");
	printf("%hu\t->\t%.4f\n",x,x1);
	printf("%hu\t->\t%.4f\n",y,y1);
	printf("fitness value: %.15f\n",fitness_func(global_best));
	printf("\n\n");
	printTime();
	printf("\n\n");


    	return 0;

}
