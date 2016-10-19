#include <stdio.h>
#include "genetic_algorithm.h"
#include "optim_problem.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_POP 100
#define MUT_PROB 40

int main()
{
	int i,j,j_best;
    	long long populacja[MAX_POP];
    	float roulette_val[MAX_POP],fitness_val[MAX_POP],fitness_sum,fitness_sum_best=1000.0;
	short x,y;
	float x1,y1;
    	srand(time(NULL));
	init_population(populacja,MAX_POP);

	for(j=0, j_best=0 ; j<100 && (j<=j_best+10) ; ++j)
	{
	    	roulette(populacja,roulette_val,MAX_POP);
		new_population(populacja,roulette_val,MAX_POP,5);
		fitness(populacja,fitness_val,MAX_POP);
		fitness_sum = 0;

		for(i=0 ; i<MAX_POP ; ++i)
	    	{
			decode(populacja[i],&x,&y);
			x1 = (1.0*x/(1 << (SHORT_BITS-1)))*(X_MAX-X_MIN) + X_MIN;
			y1 = (1.0*y/(1 << (SHORT_BITS-1)))*(Y_MAX-Y_MIN) + Y_MIN;
	    		//printf("(%hi,%hi) ",x,y);
			printf("(%.3f,%.3f) ",x1,y1);
			fitness_sum += fitness_val[i];
	    	}
		printf("<<%f\t%i>>",fitness_sum/MAX_POP,j);
		if(fitness_sum_best>fitness_sum)
		{
			fitness_sum_best = fitness_sum;
			j_best = j;
		}
		printf("\n\n\n");
	}


	


    	return 0;

}
