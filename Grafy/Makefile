OBJS	= bellman_ford.o graf_macierzowy.o lista_graf.o main.o
SOURCE	= bellman_ford.cpp graf_macierzowy.cpp lista_graf.cpp main.cpp
HEADER	= belamn_ford.hpp graf_macierzowy.hpp lista_graf.hpp
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

bellman_ford.o: bellman_ford.cpp
	$(CC) $(FLAGS) bellman_ford.cpp 

graf_macierzowy.o: graf_macierzowy.cpp
	$(CC) $(FLAGS) graf_macierzowy.cpp 

lista_graf.o: lista_graf.cpp
	$(CC) $(FLAGS) lista_graf.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)
