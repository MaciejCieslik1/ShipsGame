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

	bool loadGameState(int& maxBoardSize);
	bool saveGameState(const int& maxBoardSize);
	bool throwExceptionAndReturn();
	void loadShip(const std::vector<std::string>& words, std::vector<std::shared_ptr<Ship>>& ships, const int& maxBoardSize);
	void checkLineCorrectness(std::ifstream& file, std::string& line, std::vector<std::string>& words);
	void checkShipTitleLine(std::ifstream& file, std::string& line, std::vector<std::string>& words, int& shipsNumber, const std::string& shipTitle);
	void checkPlayerTitleLine(std::ifstream& file, std::string& line, std::vector<std::string>& words, std::vector<std::string>& playerNames, 
		const std::string& playerTitle);
	void loadShipsLoop(std::ifstream& file, std::string& line,const int& shipsNumber, std::vector<std::string>& words, std::vector<std::shared_ptr<Ship>>& ships,
		const int& maxBoardSize);
	void loadAllPlayerInfo(std::ifstream& file, std::string& line, int& shipsNumber, std::vector<std::string>& words, std::vector<std::shared_ptr<Ship>>& ships,
		const std::string& shipTitle, const std::string& playerTitle, std::vector<std::string>& playerNames, const int& maxBoardSize);
	void savePlayerInfo(std::ofstream& file, const int& playerIndex);
	void finishGamePreparation(void);
	void initializeNewGame(std::vector<std::string>& playerNames, const int& maxBoardSize);
	void startGame(const int& maxBoardSize);
};
