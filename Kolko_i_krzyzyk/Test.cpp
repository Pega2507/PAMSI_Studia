#include "Test.h"

void Test::move(Board& board,int TestPlayer) {
	int x, y;
	bool isDone = false;
	while (isDone == false) {
		x = rand() % SIZE;
		y = rand() % SIZE;
		if (board.getVal(x,y) == EMPTY) {
			board.setVal(x, y, TestPlayer);
			isDone = true;
		}
	}
}
//completely random choice, use for tests
Test::Test() {}


Test::~Test() {}
