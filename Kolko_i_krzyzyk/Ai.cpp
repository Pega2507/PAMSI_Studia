#include "Ai.h"


void Ai::init(int AiPlayer) {
	_AiPlayer = AiPlayer;
	if (_AiPlayer == X_MARK) {
		_otherPlayer = O_MARK;
	} else {
		_otherPlayer = X_MARK;
	}
}

void Ai::makeMove(Board & board, int AiPlayer) {
	Ai::init(AiPlayer);

	AiMove bestMove = _getBest(board, _AiPlayer);
	board.setVal(bestMove.x, bestMove.y, _AiPlayer);
}

Ai::Ai() {}


Ai::~Ai() {}

AiMove Ai::_getBest(Board & board, int player) {
	
	int rv = board.checkVictory();
	if (rv == WON_GAME && player == _AiPlayer) { //This is to see if the previous move was a win. by this time the player has changed.
		return AiMove(-10);
	} else if (rv == WON_GAME && player == _otherPlayer) {
		return AiMove(10);
	} else if (rv == TIE_GAME) {
		return AiMove(0);
	}

	std::vector<AiMove> moves;

	//recursive function to get moves vector
	for (int i = 0; i < SIZE; i++) {

		for (int j = 0; j < SIZE; j++) {

			if (board.getVal(i,j) == EMPTY) {

				AiMove move;
				move.x = i;
				move.y = j;
				board.setVal(i, j, player);
				if (player == _AiPlayer) {
					move.score = _getBest(board, _otherPlayer).score;
				} else {
					move.score = _getBest(board, _AiPlayer).score;
				}
				moves.push_back(move);
				board.setVal(i, j, EMPTY);
			}
		}
	}

	//pick the best move for the current player
	int bestMove = 0;
	if (player == _AiPlayer) {
		int bestScore = -1000000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	} else {
		int bestScore = 1000000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}

	}
	//return the best move
	return moves[bestMove];
	
}
