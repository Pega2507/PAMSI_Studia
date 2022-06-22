#pragma once

#include"Board.h"

struct AiMove {
	AiMove() {};
	AiMove(int Score) : score(Score) {};
	int x;
	int y;
	int score;
};

class Ai {
public:
	//Initialize Ai player
	void init(int AiPlayer);
	void makeMove(Board& board, int AiPlayer);
	Ai();
	~Ai();

private:
	AiMove _getBest(Board& board, int player);
	int _AiPlayer;
	int _otherPlayer;
};



