#pragma once
#include <cstdlib>
#include <fstream>
#include "Game.h"

class Process
{
	std::unique_ptr<Game> game;
	std::unique_ptr<Player> player_1;
	std::unique_ptr<Player> player_2;
	std::shared_ptr<LanguageManager> langOptions;

public:
	Process() = default;
	Process(std::shared_ptr<LanguageManager> language);

	static void sleep(unsigned int milliseconds);
	static void clearScreen(void);

	bool loadGameState(void);
	void initializeNewGame(std::vector<std::string>& playerNames, const int& maxBoardSize);
	void saveGameState(void);
	void startGame(const int& maxBoardSize);
};
