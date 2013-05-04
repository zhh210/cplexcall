CC = g++
CFLAGS1 = -I /usr/local/CPLEX_Studio_124/cplex/include/ -I /usr/local/CPLEX_Studio_124/concert/include/ -DIL_STD
CPLAGS2 = -L /usr/local/CPLEX_Studio_124/cplex/lib/x86-64_sles10_4.1/static_pic/ -L /usr/local/CPLEX_Studio_124/concert/lib/x86-64_sles10_4.1/static_pic/ -lilocplex -lconcert -lcplex -lm -lpthread
OBJECTS1 = BqpCplex.o
OBJECTS2 = BqpCplex

$OBJECTS2$ : $OBJECTS1$
	$(CC)$  -o  $(OBJECTS2)$  $(OBJECTS1)$  $(CPLAGS2)$

$OBJECTS1$ : BqpCplex.cpp
	$(CC)$  $(CFLAGS1) -c -o $(OBJECTS1)$  BqpCplex.cpp


