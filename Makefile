OBJS = Algorytmy.o Sortowanie.o
SOURCE = Algorytmy.cpp Sortowanie.cpp
HEADER = Algorytmy.h 
OUT = a.out
CC = g++ 
FLAGS = -g -c -Wall
LFLAGS = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) 
	
Algorytmy.o: Algorytmy.cpp 
	$(CC) $(FLAGS) Algorytmy.cpp
	
Sortowanie.o: Sortowanie.cpp
	$(CC) $(FLAGS) Sortowanie.cpp
	
clean: 
	rm -f $(OBJS) $(OUT) 