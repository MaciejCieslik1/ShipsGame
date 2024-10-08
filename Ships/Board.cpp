#include "Board.h"


Board::Board(const int& newBoardSize)
{
	if (isCorrectInt(newBoardSize))
	{
		boardSize = newBoardSize;
		generateBoard(newBoardSize);
	}
	else { throw invalid_board_size("Board size must be positive integer"); }
}


int Board::getBoardSize() const
{
	return boardSize;
}


std::vector<Field> Board::getFields() const
{
	return fields;
}


void Board::setBoardSize(const int& newBoardSize)
{
	if (isCorrectInt(boardSize)) {boardSize = newBoardSize;}
	else { throw invalid_board_size("Board size must be positive integer"); }
}


void Board::setFields(const std::vector<Field>& newFields)
{
	if (newFields.size() == boardSize * boardSize) { fields = newFields; }
	else { throw invalid_field_size("Fields must be equal to board size in power 2"); }

}


void Board::generateBoard(const int& boardSize)
{
	std::vector<Field> allFields;
	for (int y = 1; y < boardSize + 1; y++)
	{
		for (int x = 1; x < boardSize + 1; x++)
		{
			Coords currentCoords = Coords(x, y);
			Field currentField = Field(currentCoords);
			allFields.push_back(currentField);
		}
	}
	fields = allFields;
}


void Board::putShip(std::shared_ptr<Ship> newShip)
{
	std::vector<Coords> shipCoords = newShip->getCoords();
	std::vector<Field>& currentFields = fields;
	for (Coords shipSectorCoords : shipCoords)
	{
		int correctIndex = (shipSectorCoords.getY() - 1) * boardSize + shipSectorCoords.getX() - 1;
		if (correctIndex > boardSize * boardSize - 1) throw field_out_of_range("Field is out of range");
		if (currentFields[correctIndex].getShipOnField() == nullptr && currentFields[correctIndex].getIslandOnField() == nullptr)
		{
			Field newField{shipSectorCoords};
			newField.setShipOnField(newShip);
			currentFields[correctIndex] = newField;
		}
		else 
		{
			std::string info = "Field (" + std::to_string(shipSectorCoords.getX()) + ", " +  std::to_string(shipSectorCoords.getY()) + ") is already occupied";
			throw field_occupied(info);
		}
	}
}


void Board::putIsland(const std::shared_ptr<Island>& newIsland)
{
	std::vector<Coords> IslandCoords = newIsland->getCoords();
	std::vector<Field>& currentFields = fields;
	for (Coords islandSectorCoords : IslandCoords)
	{
		int correctIndex = (islandSectorCoords.getY() - 1) * boardSize + islandSectorCoords.getX() - 1;
		if (correctIndex > boardSize * boardSize - 1) { throw field_out_of_range("Field is out of range"); }
		if (currentFields[correctIndex].getShipOnField() == nullptr && currentFields[correctIndex].getIslandOnField() == nullptr)
		{
			Field newField{islandSectorCoords};
			newField.setIslandOnField(newIsland);
			currentFields[correctIndex] = newField;
		}
		else 
		{
			std::string info = "Field (" + std::to_string(islandSectorCoords.getX()) + ", " +  std::to_string(islandSectorCoords.getY()) + ") is already occupied";
			throw field_occupied(info);
		}
	}
}


void Board::removeShip(std::shared_ptr<Ship> newShip, std::vector<Coords> shipCoords)
{
	std::vector<Field>& currentFields = fields;
	for (Coords shipSectorCoords : shipCoords)
	{
		int correctIndex = (shipSectorCoords.getY() - 1) * boardSize + shipSectorCoords.getX() - 1;
		if (correctIndex > boardSize * boardSize - 1) { throw field_out_of_range("Field is out of range"); }
		Field newField{shipSectorCoords};
		newField.setShipOnField(nullptr);
		currentFields[correctIndex] = newField;
	}
}


Field Board::findField(const Coords& fieldCoords)
{
	for (Field field : fields)
	{
		if (field.getCoords().getX() == fieldCoords.getX() && field.getCoords().getY() == fieldCoords.getY()) { return field; }
	}
	throw field_not_found("Field was not found");
	return Field();
}


void Board::boardDisplay(void)
{
	std::string firstLine = "   ";
	for (int i = 1; i <= this->boardSize; ++i)
	{
		if (i < 10) firstLine += " " + std::to_string(i) + " ";
		else firstLine += " " + std::to_string(i);
	}
	std::cout << firstLine << std::endl;
	for (int i = 0; i < this->boardSize; ++i) {
		if (i < 9) std::cout << std::to_string(i + 1) << "  ";
		else std::cout << std::to_string(i + 1) + " ";
		for (int j = 0; j < this->boardSize; ++j) {
			const Field& field = this->getFields()[i * boardSize + j];
			std::cout << field.displayFieldCrate();
		}
		std::cout << '\n';
	}
}


bool Board::moveShipToFieldFirstX(const Coords& closestCoord, const std::vector<Coords>& shipCoords, const int& destinationX, const int& destinationY)
{
	if (destinationX > boardSize || destinationX < 1 || destinationY > boardSize || destinationY < 1) { return false; }
	int y = closestCoord.getY();

	if (closestCoord.getX() < destinationX)
	{
		for (int x = closestCoord.getX() + 1; x <= destinationX; x++)
		{
			Coords currentFieldCoords = Coords(x, y);
			Field currentField = findField(currentFieldCoords);
			if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
		}
		if (closestCoord.getY() < destinationY)
		{
			for (int y = closestCoord.getY() + 1; y <= destinationY; y++)
			{
				for (int x = destinationX - shipCoords.size() + 1; x <= destinationX; x++)
				{
					Coords currentFieldCoords = Coords(x, y);
					Field currentField = findField(currentFieldCoords);
					if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
				}
			}
		}
		else if (closestCoord.getY() > destinationY)
		{
			for (int y = closestCoord.getY() - 1; y >= destinationY; y--)
			{
				for (int x = destinationX - shipCoords.size() + 1; x <= destinationX; x++)
				{
					Coords currentFieldCoords = Coords(x, y);
					Field currentField = findField(currentFieldCoords);
					if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
				}

			}
		}
	}

	else if (closestCoord.getX() > destinationX)
	{
		for (int x = closestCoord.getX() - 1; x >= destinationX; x--)
		{
			Coords currentFieldCoords = Coords(x, y);
			Field currentField = findField(currentFieldCoords);
			if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
		}
		if (closestCoord.getY() < destinationY)
		{
			for (int y = closestCoord.getY() + 1; y <= destinationY; y++)
			{
				for (int x = destinationX; x <= destinationX + shipCoords.size() - 1; x++)
				{
					Coords currentFieldCoords = Coords(x, y);
					Field currentField = findField(currentFieldCoords);
					if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
				}

			}
		}
		else if (closestCoord.getY() > destinationY)
		{
			for (int y = closestCoord.getY() - 1; y >= destinationY; y--)
			{
				for (int x = destinationX; x <= destinationX + shipCoords.size() - 1; x++)
				{
					Coords currentFieldCoords = Coords(x, y);
					Field currentField = findField(currentFieldCoords);
					if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
				}

			}
		}
	}
	else return false;
	return true;
}


bool Board::moveShipToFieldFirstY(const Coords& closestCoord, const std::vector<Coords>& shipCoords, const int& destinationX, const int& destinationY)
{
	if (destinationX > boardSize || destinationX < 1 || destinationY > boardSize || destinationY < 1) { return false; }
	if (closestCoord.getY() < destinationY)
	{
		for (int y = closestCoord.getY() + 1; y <= destinationY; y++)
		{
			for (Coords currentShipCoord : shipCoords)
			{
				Coords currentFieldCoords = Coords(currentShipCoord.getX(), y);
				Field currentField = findField(currentFieldCoords);
				if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
			}

		}
		int y = destinationY;
		if (closestCoord.getX() < destinationX)
		{
			for (int x = closestCoord.getX(); x <= destinationX; x++)
			{
				Coords currentFieldCoords = Coords(x, y);
				Field currentField = findField(currentFieldCoords);
				if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
			}
		}
		else if (closestCoord.getX() > destinationX)
		{
			for (int x = closestCoord.getX(); x >= destinationX; x--)
			{
				Coords currentFieldCoords = Coords(x, y);
				Field currentField = findField(currentFieldCoords);
				if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
			}
		}
	}
	else if (closestCoord.getY() > destinationY)
	{
		for (int y = closestCoord.getY() - 1; y >= destinationY; y--)
		{
			for (Coords currentShipCoord : shipCoords)
			{
				Coords currentFieldCoords = Coords(currentShipCoord.getX(), y);
				Field currentField = findField(currentFieldCoords);
				if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
			}

		}
		int y = destinationY;
		if (closestCoord.getX() < destinationX)
		{
			for (int x = closestCoord.getX(); x <= destinationX; x++)
			{
				Coords currentFieldCoords = Coords(x, y);
				Field currentField = findField(currentFieldCoords);
				if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
			}
		}
		else if (closestCoord.getX() > destinationX)
		{
			for (int x = closestCoord.getX(); x >= destinationX; x--)
			{
				Coords currentFieldCoords = Coords(x, y);
				Field currentField = findField(currentFieldCoords);
				if (currentField.getShipOnField() != nullptr || currentField.getIslandOnField() != nullptr) { return false; }
			}
		}
	}
	else return false;
	return true;
}


bool Board::moveShipToField(const std::shared_ptr<Ship>& ship, const int& destinationX, const int& destinationY)
{
	std::vector<Coords> shipCoords = ship->getCoords();
	std::vector<Coords> extremeCoords = ship->extremeCoords();
	Coords extremeBig = extremeCoords[0];
	Coords extremeSmall = extremeCoords[1];
	int distanceBig = abs(destinationX - extremeBig.getX()) + abs(destinationY - extremeBig.getY());
	int distanceSmall = abs(destinationX - extremeSmall.getX()) + abs(destinationY - extremeSmall.getY());
	Coords closestCoord;
	if (distanceBig < distanceSmall) { closestCoord = extremeBig; }
	else { closestCoord = extremeSmall; }

	// calculate difference in between final and beginnning cooridnates
	int deltaX = destinationX - closestCoord.getX();
	int deltaY = destinationY - closestCoord.getY();

	// check if ship has enough movement to be moved
	if (ship->getMovement() < deltaX + deltaY) { return false; }

	std::vector<Coords> CoordsOfShip = ship->getCoords();

	if (moveShipToFieldFirstX(closestCoord, CoordsOfShip, destinationX, destinationY) ||
		moveShipToFieldFirstY(closestCoord, CoordsOfShip, destinationX, destinationY))
	{
		std::vector<Coords> finalShipCoords;
		for (Coords currentShipCoord : CoordsOfShip)
		{
			Coords newCoords;
			newCoords.setX(currentShipCoord.getX() + deltaX);
			newCoords.setY(currentShipCoord.getY() + deltaY);
			finalShipCoords.push_back(newCoords);
		}
		ship->setCoords(finalShipCoords);
		removeShip(ship, shipCoords);
		putShip(ship);
		return true;
	}
	else { return false; }
}
