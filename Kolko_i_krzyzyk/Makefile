OBJS = Test.o Board.o MainGame.o Ai.o main.o
SOURCE = Test.cpp Board.cpp MainGame.cpp Ai.cpp main.cpp
HEADER = Test.h Board.h MainGame.h Ai.h
OUT	= a.out
CC = g++
FLAGS = -g -c -Wall
LFLAGS = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
Test.o: Test.cpp
	$(CC) $(FLAGS) Test.cpp 
Board.o: Board.cpp
	$(CC) $(FLAGS) Board.cpp 
MainGame.o: MainGame.cpp
	$(CC) $(FLAGS) MainGame.cpp 
Ai.o: Ai.cpp
	$(CC) $(FLAGS) Ai.cpp 
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

clean:
	rm -f $(OBJS) $(OUT)
