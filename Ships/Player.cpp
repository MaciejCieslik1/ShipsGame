#include "Player.h"

Player::Player(const std::string& name, const int& maxMoves, const int& moveCounter)
	: name(name), maxMoves(maxMoves), moveCounter(moveCounter), boardPtr(nullptr)
	{ }

Player::Player(const std::string &name, const std::vector<Ship *> &newShips, const int &newMaxMoves, const std::vector<CruiseMissile> &newAllMissiles)
	: name(name), ships(newShips), maxMoves(newMaxMoves), allMissiles(newAllMissiles)
{
	this->boardPtr = nullptr;
	if (!isCorrectInt) throw invalid_max_moves_value("Max moves number must be a positive integer");
}

Player::Player(const std::vector<Ship*>& newShips, Board*& newBoardPtr, const int& newMaxMoves, const std::vector<CruiseMissile>& newAllMissiles)
{
	ships = newShips;
	boardPtr = newBoardPtr;
	allMissiles = newAllMissiles;
	if (isCorrectInt(newMaxMoves)) { maxMoves = newMaxMoves; }
	else { throw invalid_max_moves_value("Max moves number must be a positive integer"); }
	moveCounter = maxMoves;

}


Player::~Player() {
	for (Ship* ship : ships) {
		delete ship;
	}
}


std::vector<Ship*> Player::getShips() const
{
	return ships;
}


Board* Player::getBoardPtr() const
{
	return boardPtr;
}


std::vector <CruiseMissile> Player::getAllMissilies() const
{
	return allMissiles;
}


int Player::getMaxMoves() const
{
	return maxMoves;
}


int Player::getMoveCounter() const
{
	return moveCounter;
}

std::string Player::getName() const
{
    return name;
}

void Player::setName(const std::string newName)
{
	for (const char& v : newName) if(v == ' ') {
		throw space_in_name_error("Name cannot be spaced");
	}
	name = newName;
}

void Player::setShips(const std::vector<Ship *> &newShips)
{
	ships = newShips;
}


void Player::setBoard(Board* newBoard)
{
	boardPtr = newBoard;
}


void Player::setAllMissiles(const std::vector<CruiseMissile>& newAllMissiles)
{
	allMissiles = newAllMissiles;
}


void Player::setMaxMoves(const int& newMaxMoves)
{
	maxMoves = newMaxMoves;
}


void Player::setMoveCounter(const int& newMoveCunter)
{
	moveCounter = newMoveCunter;
}


bool Player::decrementMoves(const int& n)
{
	if (isCorrectInt(n) && n <= moveCounter && n <= maxMoves)
	{
		moveCounter -= n;
		return true;
	}
	else { return false; }
}


bool Player::fire(Ship* shipPtr, Field& destination, const int& missileID)
{
	std::vector<Coords> shipCoords = shipPtr->getCoords();
	Coords destinationCoords = destination.getCoords();
	Coords closestCoords = shipCoords[0];
	int distance = abs(destinationCoords.getX() - closestCoords.getX()) + abs(destinationCoords.getY() - closestCoords.getY());
	for (Coords currentCords : shipCoords)
	{
		int newDistance = abs(destinationCoords.getX() - currentCords.getX()) + abs(destinationCoords.getY() - currentCords.getY()) < distance;
		if (newDistance < distance)
		{
			distance = newDistance;
			closestCoords = currentCords;
		}
	}
	if (shipPtr->hasMissile(missileID))
	{
		return allMissiles[missileID].fire(closestCoords, destination);
	}
	else { return false; }
}


bool Player::move(Ship* shipPtr, Field& destination)
{
	Coords choosenCoords = shipPtr->getCoords()[0];
	Coords destinationCoords = destination.getCoords();
	Field shipField = boardPtr->findField(choosenCoords);
	return boardPtr->moveShipToField(shipField, destinationCoords.getX(), destinationCoords.getY());
}


void Player::forgetShip(Ship* ship)
{
	std::vector<Ship*> newShipsVector;
	for (Ship* currentPtr : ships)
	{
		if (currentPtr != ship)
		{
			newShipsVector.push_back(currentPtr);
		}
	}
	ships = newShipsVector;
}


void Player::shipsInfo() const
{
	std::string info;
	int i = 0;
	for (Ship* currentShip : ships)
	{
		info += "Ship " + std::to_string(i) + ": ";
		info += std::string (currentShip->getCoords().size(), currentShip->getName());
		info += ", hit points: ";
		info += std::to_string(currentShip->getHitPoints());
		info += " , missilies: ";
		int numberOfMissilies = currentShip->getMissileIDs().size();
		for (int j = 0; j<numberOfMissilies - 1; j++)
		{
			info += std::to_string(j) + ", ";
		}
		info += std::to_string(numberOfMissilies - 1);
		info += " , movement: ";
		info += std::to_string(currentShip->getMovement()) + "\n";
		i++;
	} 
	std::cout << info;
}


std::ostream& operator<<(std::ostream& os, const Player& player) {
	os << player.name << ' ' << player.maxMoves << ' ' << player.moveCounter << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Player& player) {
	std::string name;
    int maxMoves;
    int moveCounter;

	if (is >> name >> maxMoves >> moveCounter) {
        player.name = name;
        player.maxMoves = maxMoves;
        player.moveCounter = moveCounter;
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
}

bool Player::operator==(const Player& other) const {
	// std::string name;
    // std::vector<Ship*> ships;
    // Board* boardPtr;
    // std::vector<CruiseMissile> allMissiles;
    // int maxMoves;
    // int moveCounter;
	if (name != other.name) return false;
    if (ships.size() != other.ships.size()) return false;
    for (size_t i = 0; i < ships.size(); ++i) {
        if (*ships[i] != *other.ships[i]) return false;
    }

    if (boardPtr != other.boardPtr) return false;
    if (allMissiles != other.allMissiles) return false;
    if (maxMoves != other.maxMoves) return false;
    if (moveCounter != other.moveCounter) return false;

    return true;
}

bool Player::operator!=(const Player& other) const {
	return !(*this == other);
}
