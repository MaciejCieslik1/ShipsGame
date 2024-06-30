#pragma once
#include <memory>
#include <iostream>
#include <cstdlib>
#include <thread>
#include "CruiseMissile.h"
#include "Ship.h"
#include "LanguageManager.h"
#include "FileHandler.h"
#include "Player.h"
#include "Game.h"
#include "Field.h"
#include "Coords.h"
#include "Board.h"

class Process
{
	std::unique_ptr<Game> game;
	std::unique_ptr<Player> player_1;
	std::unique_ptr<Player> player_2;
	std::shared_ptr<LanguageManager> langOptions;

public:
	Process() = default;
	Process(std::shared_ptr<LanguageManager> language);
	~Process() = default;

	static void sleep(unsigned int milliseconds);
	static void clearScreen(void);

	void loadGameState(void);
	void initializeNewGame(std::vector<std::string>& playerNames);
	void saveGameState(void);
	void startGame(void);
};
