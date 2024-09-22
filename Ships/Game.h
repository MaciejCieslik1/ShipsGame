#pragma once
#include <thread>
#include <chrono>
#include "Player.h"


class Game
{

private:

	std::shared_ptr<Board> board;
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::shared_ptr<Island>> islands;
	int	currentPlayer;
	int numberOfTurns;
	std::shared_ptr<Player> winner;
	int turnStage;
	bool isOn;
	std::shared_ptr<LanguageManager> langOptions;

	int action; 
	std::shared_ptr<Ship> ship; 
	Field destination; 
	int missileID;

public:

	Game(const std::vector<std::shared_ptr<Player>>& players, const std::vector<std::shared_ptr<Island>>& islands, 
	const int& maxBoardSize, std::shared_ptr<LanguageManager> langOptions);

	std::shared_ptr<Board> getBoard() const;
	const std::vector<std::shared_ptr<Player>>& getPlayers() const;
	std::vector<std::shared_ptr<Island>> getIslands() const;
	int	getCurrentPlayerIndex() const;
	int getNumberOfTurns() const;
	std::shared_ptr<Player> getWinner() const;
	int getTurnStage() const;
	bool getIsOn() const;
	int getAction() const;
	std::shared_ptr<Ship> getShip() const;
	Field destinaion() const;
	int getMissileID() const;

	void setBoard(std::shared_ptr<Board> new_board);
	void setPlayers(const std::vector<std::shared_ptr<Player>>& new_players);
	void setIslands(const std::vector<std::shared_ptr<Island>>& newIslands);
	void setCurrentPlayerIndex(const int& new_player);
	void setNumberOfTurns(const int& new_number_of_turns);
	void setWinner(std::shared_ptr<Player> new_winner);
	void setTurnStage(const int& newStage);
	void setIsOn(const bool& state);
	void setAction(const int& newAction);
	void setShip(const std::shared_ptr<Ship>& newShip);
	void setMissileID(const int& newMissileID); 

	void mainGameProcess(const int& input, const int& maxBoardSize, bool& correctMoveFlag);
	void displayInfo();

private:

	void generateBoard(const int& maxBoardSize);
	void checkIfShipSunked();
	void pickAction(const int& input);
	void pickShip(const int& input);
	void pickDestination(const int& input, const int& maxBoardSize);
	void pickMissile(const int& input);
	void confirm(const int& input, bool& correctMoveFlag);
	void newTurn();
};
