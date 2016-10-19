#ifndef genetic_algorithm_h
#define genetic_algorithm_h

void bubblesort(float table[], long long table2[], int size);
void aggregation(float table[], float aggredated[], int size);
void fitness(long long population[], float fitness_val[], int size);
void roulette(long long population[], float roulette_agg[], int size);

void crossover1(long long * chrom1, long long * chrom2, int k);
void crossover2(long long * chrom1, long long * chrom2, int k);
void mutation1(long long *chrom,int k);

void new_population(long long population[], float roulette_val[], int size, int mut_prob);
long long new_chromosome(long long population[], float roulette_val[], int size, int num);

#endif
