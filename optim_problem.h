#ifndef optim_problem_h
#define optim_problem_h



#define SHORT_BITS 16
#define LONG_LONG_BITS 64
#define PROC_BITS 32

#define X_MIN 0
#define X_MAX 20
#define Y_MIN 0
#define Y_MAX 20


float fitness_func(long long x);
long long code(short x, short y);
void decode(long long code, short * x, short * y);
void init_population(long long population[], int size);

#endif
