#pragma once
#include <vector>
#include <stdexcept>
#include <istream>
#include <algorithm>
#include "ShipsExceptions.h"
#include "Field.h"
#include "Board.h"
#include "Player.h"

class Game
{
protected:
	Board* board;
	std::vector<Player*> players;
	int	currentPlayer;
	int numberOfTurns;
	Player* winner;
	int turnStage;
	bool isOn;

	int action; Ship* ship; Field destination; int missile;

	friend std::ostream& operator<<(std::ostream& os, const Game& game);
	friend std::istream& operator>>(std::istream& is, Game& game);

public:
	Game();
	Game(const std::vector<Player*>& players, const int& maxBoardSize);
	~Game();

	Board* getBoard() const;
	const std::vector<Player*>& getPlayers() const;
	int	getCurrentPlayerIndex() const;
	int getNumberOfTurns() const;
	Player* getWinner() const;
	int getTurnStage() const;
	bool getIsOn() const;

	void setBoard(Board* new_board);
	void setPlayers(const std::vector<Player*>& new_players);
	void setCurrentPlayerIndex(const int& new_player);
	void setNumberOfTurns(const int& new_number_of_turns);
	void setWinner(Player* new_winner);
	void setTurnStage(const int& newStage);
	void turnGameOn();
	void turnGameOff();
	void generateBoard(const int& maxBoardSize);
	void checkIfShipSunked();
	void mainGameProcess(const int& input, const int& maxBoardSize);
	void displayInfo();

private:
	void pickAction(const int& input);
	void pickShip(const int& input);
	void pickDestination(const int& input, const int& maxBoardSize);
	void pickMissile(const int& input);
	void confirm(const int& input);

	void newTurn();
};
