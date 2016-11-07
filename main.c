#include <stdio.h>
#include "genetic_algorithm.h"
#include "optim_problem.h"
#include "report.h"
#include "simulation.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_POP 100
#define MUT_PROB 40

int main()
{
	int i,j,j_best;
    	long long populacja[MAX_POP],global_best;
    	float roulette_val[MAX_POP],fitness_val[MAX_POP],fitness_sum,fitness_sum_best=1000.0;
    	srand(time(NULL));
	init_population(populacja,MAX_POP);
	global_best = populacja[0];

	for(j=0, j_best=0 ; j<100 && (j<=j_best+100) ; ++j)
	{
	    	roulette(populacja,roulette_val,MAX_POP);

		new_population(populacja,roulette_val,MAX_POP,5); //may be parallelised
		fitness(populacja,fitness_val,MAX_POP);

		global_best=printPopulation(populacja,fitness_val,MAX_POP,j+1,global_best);

		fitness_sum = 0;
		if(fitness_sum_best>fitness_sum)
		{
			fitness_sum_best = fitness_sum;
			j_best = j;
		}

	}


	


    	return 0;

}
