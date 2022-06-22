#pragma once
#include<string>
#include<iostream>
#include"Board.h"
#include"Test.h"
#include"Ai.h"

enum class GameState{MENU, Test, Ai, TRAIN_NN,TRAIN_GA, EXIT};

class MainGame {
public:

	
	void run();
	MainGame();
	~MainGame();

private:

	void _handleMenu();
	//void _gameLoop();
	void _changePlayer();
	void _displayresult(int gameEnd);
	void _TestMove();
	void _humanMove();
	void _AiMove();


	Board _board;
	GameState _gameState;
	int _currentPlayer;
	int _pcPlayer;
	int _humanPlayer;
	Test _Test;
	Ai _Ai;

};

