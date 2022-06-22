#include "MainGame.h"


void MainGame::_handleMenu() {

	printf(" WELCOME TO TIC TACT TOE\n");
	printf("Enter '1' to play\n '2' for tests \n '3' to quit\n");

	std::string userInput;
	std::cin >> userInput;

	if (userInput == "3") {
		_gameState = GameState::EXIT;
	}

	if (userInput == "2") {
		_gameState = GameState::Test;
	}
	
	if (userInput == "1") {
		_gameState = GameState::Ai;
	}

	bool isValid;
	char input = ' ';

	if (userInput != "Exit" && userInput != "TrainNN" && userInput != "TrainGA") {
		printf("\nWould you like to be X or O: (O goes first!!)");
		do {
			isValid = true;
			if (!(std::cin >> input)) {
				std::cout << "Invalid input!";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				isValid = false;
			} else if (input == 'x' || input == 'X') {
				_humanPlayer = X_MARK;
				_pcPlayer = O_MARK;
				_currentPlayer = _pcPlayer;
			} else if (input == 'o' || input == 'O') {
				_humanPlayer = O_MARK;
				_pcPlayer = X_MARK;
				_currentPlayer = _humanPlayer;
			} else {
				std::cout << "Must enter X or O!";
				isValid = false;
			}
		} while (isValid == false);
	}
	
}

void MainGame::_changePlayer() {
	if (_currentPlayer == _humanPlayer) {
		_currentPlayer = _pcPlayer;
	} else {
		_currentPlayer = _humanPlayer;
	}
}

void MainGame::_displayresult(int gameEnd) {
	if (gameEnd == WON_GAME) {
		if (_currentPlayer == _humanPlayer) {
			printf("YOU WON!!");
		} else {
			printf("LOOOOOSER!!");
		}
	} else {
		printf("Game Drawn");
	}
}

void MainGame::_TestMove() {
	_Test.move(_board,_pcPlayer);
}

void MainGame::_humanMove() {
	bool moveMade = false;
	while (moveMade == false) {
		
		int x, y;
		
		printf("Enter X: ");
		std::cin >> x;
		printf("Enter Y: ");
		std::cin >> y;
		x--;
		y--;
		
		if (_board.getVal(x, y) == EMPTY) {
			_board.setVal(x, y, _humanPlayer);
			moveMade = true;
		} else {
			printf("place taken!! try another spot");
		}
	} 
	
}

void MainGame::_AiMove() {
	_Ai.makeMove(_board, _pcPlayer);
}

/*problem is: game doesnt end before board is full, then it prints the same board with values
	and you cant do anything cause eveything is freakin full*/

void MainGame::run() {
	_handleMenu();
	_board.init();
	while (_gameState != GameState::EXIT) {
	
		//print the board
		//std::cout<<"\n\n Board printing \n\n ";
		_board.print(); //sth wrong here?
		
		//players move
		if (_gameState == GameState::Test) {
			if (_currentPlayer == _humanPlayer) {
				_humanMove();
			} else {
				_TestMove();
			}
		} else if (_gameState== GameState::Ai) {
			if (_currentPlayer == _humanPlayer) {
				_humanMove();
			} else {
				_AiMove();
			}
		}

		//Check for a win situation
		int gameEnd = _board.checkVictory();

		if (gameEnd == WON_GAME || gameEnd == TIE_GAME) {
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			_board.print();
			_displayresult(gameEnd); 
			do {
     			std::cout << '\n' << "Press the Enter key to continue.";
   			} while (std::cin.get() != '\n');
		} else {
		    _changePlayer();

			//cheap way to clear the command prompt
			for (int i = 0; i < 3; i++) {
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			}
		}

	}

}

MainGame::MainGame() {}


MainGame::~MainGame() {}
