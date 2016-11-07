# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
INC = 

# biblioteki
LIB = -lm

# zaleznosci i komendy
main2: main.o genetic_algorithm.o optim_problem2.o report.o 
	$(LOADER) $(OPT) main.o genetic_algorithm.o optim_problem2.o report.o -o main $(LIB)

main1: main.o genetic_algorithm.o optim_problem.o report.o 
	$(LOADER) $(OPT) main.o genetic_algorithm.o optim_problem.o report.o -o main $(LIB)

main.o: main.c
	$(CCOMP) -c $(OPT) main.c $(INC) 

genetic_algorithm.o: genetic_algorithm.c
	$(CCOMP) -c $(OPT) genetic_algorithm.c $(INC)

optim_problem.o: optim_problem.c
	$(CCOMP) -c $(OPT) optim_problem.c $(INC)

optim_problem2.o: optim_problem2.c
	$(CCOMP) -c $(OPT) optim_problem2.c $(INC)

report.o: report.c
	$(CCOMP) -c $(OPT) report.c $(INC)

simulation.o: simulation.c
	$(CCOMP) -c $(OPT) simulation.c $(INC)

clean:
	rm -f *.o
