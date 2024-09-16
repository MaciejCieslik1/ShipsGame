#pragma once
#include "Field.h"

class Board
{
protected:
	int	boardSize;
	std::vector<Field> fields;

public:
	Board(const int& boardSize);

	int getBoardSize() const;
	std::vector<Field> getFields(void) const;

	void setBoardSize(const int& newBoardSize);
	void setFields(const std::vector<Field>& new_fields);

	void generateBoard(const int& boardSize);
	void putShip(std::shared_ptr<Ship> newShip);
	void putIsland(const std::shared_ptr<Island>& newShoal);
	void removeShip(std::shared_ptr<Ship> newShip, std::vector<Coords> shipCoords);
	bool moveShipToFieldFirstX(const Coords& closestCoord, const std::vector<Coords>& shipCoords, const int& destinationX, const int& destinationY);
	bool moveShipToFieldFirstY(const Coords& closestCoord, const std::vector<Coords>& shipCoords, const int& destinationX, const int& destinationY);
	bool moveShipToField(const std::shared_ptr<Ship>& shipPtr, const int& destinationX, const int& destinationY);
	Field findField(const Coords& fieldCoords);

	void boardDisplay(void);
};
