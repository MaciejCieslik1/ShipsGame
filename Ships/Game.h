#pragma once
#include <vector>
#include <stdexcept>
#include <istream>
#include <algorithm>
#include <thread>
#include <chrono>
#include "ShipsExceptions.h"
#include "Field.h"
#include "Board.h"
#include "Player.h"

class Game
{
protected:
	std::shared_ptr<Board> board;
	std::vector<std::shared_ptr<Player>> players;
	int	currentPlayer;
	int numberOfTurns;
	std::shared_ptr<Player> winner;
	int turnStage;
	bool isOn;

	int action; std::shared_ptr<Ship> ship; Field destination; int missile;

	friend std::ostream& operator<<(std::ostream& os, const Game& game);
	friend std::istream& operator>>(std::istream& is, Game& game);

public:
	Game();
	Game(const std::vector<std::shared_ptr<Player>>& players, const int& maxBoardSize);
	~Game();

	std::shared_ptr<Board> getBoard() const;
	const std::vector<std::shared_ptr<Player>>& getPlayers() const;
	int	getCurrentPlayerIndex() const;
	int getNumberOfTurns() const;
	std::shared_ptr<Player> getWinner() const;
	int getTurnStage() const;
	bool getIsOn() const;

	void setBoard(std::shared_ptr<Board> new_board);
	void setPlayers(const std::vector<std::shared_ptr<Player>>& new_players);
	void setCurrentPlayerIndex(const int& new_player);
	void setNumberOfTurns(const int& new_number_of_turns);
	void setWinner(std::shared_ptr<Player> new_winner);
	void setTurnStage(const int& newStage);
	void turnGameOn();
	void turnGameOff();
	void generateBoard(const int& maxBoardSize);
	void checkIfShipSunked();
	void mainGameProcess(const int& input, const int& maxBoardSize, bool& correctMoveFlag);
	void displayInfo();

private:
	void pickAction(const int& input);
	void pickShip(const int& input);
	void pickDestination(const int& input, const int& maxBoardSize);
	void pickMissile(const int& input);
	void confirm(const int& input, bool& correctMoveFlag);

	void newTurn();
};
