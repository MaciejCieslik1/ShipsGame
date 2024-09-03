#include "Player.h"

Player::Player(const std::string &name, const std::vector<std::shared_ptr<Ship>> &newShips, const std::vector<CruiseMissile> &newAllMissiles)
	: name(name), ships(newShips), allMissiles(newAllMissiles) {}

Player::Player(const std::string& name, const std::vector<std::shared_ptr<Ship>>& newShips)
	: name(name), ships(newShips)
{
	allMissiles = std::vector<CruiseMissile>({CruiseMissile(2, 5, 0), CruiseMissile(4, 4, 1), CruiseMissile(6, 3, 2), CruiseMissile(8, 2, 3)}); 
}


Player::~Player() {}


std::vector<std::shared_ptr<Ship>> Player::getShips() const
{
	return ships;
}


std::shared_ptr<Board> Player::getBoardPtr() const
{
	return boardPtr;
}


std::vector <CruiseMissile> Player::getAllMissilies() const
{
	return allMissiles;
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


void Player::setShips(const std::vector<std::shared_ptr<Ship>> &newShips)
{
	ships = newShips;
}


void Player::setBoard(std::shared_ptr<Board> newBoard)
{
	boardPtr = newBoard;
}


void Player::setAllMissiles(const std::vector<CruiseMissile>& newAllMissiles)
{
	allMissiles = newAllMissiles;
}


bool Player::fire(std::shared_ptr<Ship> shipPtr, Field& destination, const int& missileID)
{
	std::vector<Coords> shipCoords = shipPtr->getCoords();
	Coords destinationCoords = destination.getCoords();
	Coords closestCoords = shipCoords[0];
	int distance = abs(destinationCoords.getX() - closestCoords.getX()) + abs(destinationCoords.getY() - closestCoords.getY());
	for (Coords currentCords : shipCoords)
	{
		int newDistance = abs(destinationCoords.getX() - currentCords.getX()) + abs(destinationCoords.getY() - currentCords.getY());
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


bool Player::move(std::shared_ptr<Ship> shipPtr, Field& destination)
{
	Coords choosenCoords = shipPtr->getCoords()[0];
	Coords destinationCoords = destination.getCoords();
	Field shipField = boardPtr->findField(choosenCoords);
	return boardPtr->moveShipToField(shipField, destinationCoords.getX(), destinationCoords.getY());
}


void Player::forgetShip(std::shared_ptr<Ship> ship)
{
	std::vector<std::shared_ptr<Ship>> newShipsVector;
	for (std::shared_ptr<Ship> currentPtr : ships)
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
	for (std::shared_ptr<Ship> currentShip : ships)
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


std::ostream& operator<<(std::ostream& os, const Player& player) 
{
	os << player.name << '\n';
	return os;
}


std::istream& operator>>(std::istream& is, Player& player) 
{
	std::string name;
    int maxMoves;
    int moveCounter;

	if (is >> name >> maxMoves >> moveCounter) player.name = name;
	else is.setstate(std::ios::failbit);

    return is;
}


bool Player::operator==(const Player& other) const 
{
	if (name != other.name) return false;
    if (ships.size() != other.ships.size()) return false;
    for (size_t i = 0; i < ships.size(); ++i) {
        if (*ships[i] != *other.ships[i]) return false;
    }

    if (boardPtr != other.boardPtr) return false;
    if (allMissiles != other.allMissiles) return false;

    return true;
}


bool Player::operator!=(const Player& other) const 
{
	return !(*this == other);
}
