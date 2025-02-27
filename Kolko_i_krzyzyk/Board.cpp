#include "Board.h"
#include<string>

// Arrays of chars for printing out the board all fancy-like
const char GLYPHS[3][3][3] = {
	{
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' }
	},
	{
		{ '#', ' ', '#' },
		{ ' ', '#', ' ' },
		{ '#', ' ', '#' }
	},
	{
		{ '#', '#', '#' },
		{ '#', ' ', '#' },
		{ '#', '#', '#' }
	}
};


Board::Board() {}


Board::~Board() {}

void Board::init() {		//initializing board
	_board.resize(SIZE, std::vector<int>(SIZE, EMPTY));
	clear();
}

void Board::clear() {		//filling board with empty values
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			_board[i][j] = EMPTY;
		}
	}
}



void Board::print() const {
	// Instead of calling printf multiple times, we build a single
	// string and call printf once, since its faster.

	std::string text = "";
	// Just reserve a bunch of memory, this should be enough
	text.reserve(SIZE * SIZE * 4);

	// Make top number rows (guide)
	addGuide(text);

	// Loop through columns
	for (int y = SIZE-1; y >=0; y--) {
		// Add line
		addHorizontalLine(text);
		// Loop through y
		for (int ny = 0; ny < 3; ny++) {
			// Add number or space
			if (ny == 1) {
				text += std::to_string(1+y);
			} else {
				text += " ";
			}
			// Loop through row cells
			for (int x = 0; x <SIZE; x++) {
				// Loop through x
				text += "|";
				for (int nx = 0; nx < 3; nx++) {
					text += GLYPHS[getVal(x, y)][ny][nx];
				}
			}
			text += "|";
			// Add number or newline
			if (ny == 1) {
				text += std::to_string(y+1) + "\n";
			} else {
				text += "\n";
			}
		}
	}
	// Add bottom line
	addHorizontalLine(text); \
		// Make bottom guide
		addGuide(text);

	// printf is faster than cout

	// Print the string
	printf("%s\n", text.c_str());
}


int Board::checkVictory() const {
	int counter = 1;

	//ALL BELOW DONE WITH VECTOR INDEXING OF THE ARRAY
	//COLUMNS
	for (int i = 0; i < SIZE; i++) {
		counter = 1;
		for (int j = 0; j < SIZE-1; j++) {
			if ((getVal(i,j) == getVal(i,j+1)) && (getVal(i,j) != EMPTY)){
				counter++;
				if (counter == IN_A_ROW) {
					return WON_GAME;
				}
			} else {
				counter = 1;
			}
		}
	}
	//ROWS
	for (int i = 0; i < SIZE; i++) {
		counter = 1;
		for (int j = 0; j < SIZE-1; j++) {
			if ((getVal(j, i) == getVal(j+1, i)) && (getVal(j, i) != EMPTY)) {
				counter++;
				if (counter == IN_A_ROW) {
					return WON_GAME;
				}
			} else {
				counter = 1;
			}
		}
	}

	//DIAGONALS LEFT TO RIGHT
	for (int i = 1; i < SIZE - IN_A_ROW + 1; i++) {//no need to check big diagonal again
		counter = 1;
		for (int k = 0; k < (SIZE-i-1); k++) {
			if ((getVal(k, i+k) == getVal(k+1, i + k+1)) && (getVal(k, i+k) != EMPTY)) {
				counter++;
				if (counter == IN_A_ROW) {
					return WON_GAME;
				} 
				} else {
				counter = 1;
			}
		}
	}
	for (int i = 0; i < SIZE - IN_A_ROW + 1; i++) {
		counter = 1;
		for (int k = 0; k < (SIZE - i-1); k++) {
			if ((getVal(i+k, k) == getVal(i+k + 1, k + 1)) && (getVal(i+k, k) != EMPTY)) {
				counter++;
				if (counter == IN_A_ROW) {
					return WON_GAME;
				} 
				} else {
				counter = 1;
			}
		}
	}

	//DIAGONALS RIGHT TO LEFT 
	for (int i = 0; i < SIZE - IN_A_ROW + 1; i++) {
		counter = 1;
		for (int k = 0; k < (SIZE - i-1); k++) {
			if ((getVal(SIZE-1-k,i + k) == getVal(SIZE-1-(k + 1), i + k + 1)) && (getVal(SIZE-1-k, i + k) != EMPTY)) {
				counter++;
				if (counter == IN_A_ROW) {
					return WON_GAME;
				} 
				} else {
				counter = 1;
			}
		}
	}

	for (int i = 1; i < SIZE - IN_A_ROW + 1; i++) {
		counter = 1;
		for (int k = 0; k < (SIZE - i-1); k++) {
			if ((getVal(SIZE-1-i - k, k) == getVal(SIZE-i - k- 2, k + 1)) && (getVal(SIZE -1 - i - k, k) != EMPTY)) {
				counter++;
				if (counter == IN_A_ROW) {
					return WON_GAME;
				}
				} else {
				counter = 1;
			}
		}
	}

	// Check for tie game ???
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (_board[i][j] == EMPTY) {
				return EMPTY;
			}
		}
	}
	return TIE_GAME;


}

void Board::addHorizontalLine(std::string& s) const {
	s += "-";
	for (int x = 0; x < SIZE; x++) {
		s += "----";
	}
	s += "--\n";
}

void Board::addGuide(std::string& s) const {
	s += " ";
	for (int i = 1; i <= SIZE; i++) {
		s += "| " + std::to_string(i) + " ";
	}
	s += "|\n";
}

//END OF COPY
