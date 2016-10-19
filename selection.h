#ifndef selection_h
#define selection_h

float fitness_func(short x);

void bubblesort(float table[], short table2[], int size);
void aggregation(float table[], float aggredated[], int size);
void fitness(short population[], float fitness_val[], int size);
void roulette(short population[], float roulette_agg[], int size);

void crossover1(short * chrom1, short * chrom2, int k);
void crossover2(short * chrom1, short * chrom2, int k);
void mutation1(short *chrom,int k);

void new_population(short population[], float roulette_val[], int size);
short new_chromosome(short population[], float roulette_val[], int size, int num);

#endif
