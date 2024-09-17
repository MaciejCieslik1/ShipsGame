#include "Player.h"

Player::Player(const std::string &name, const std::vector<std::shared_ptr<Ship>> &newShips, const std::vector<CruiseMissile> &newAllMissiles,
	const std::shared_ptr<LanguageManager>& langOptions)
	: name(name), ships(newShips), allMissiles(newAllMissiles), langOptions(langOptions){}

Player::Player(const std::string& name, const std::vector<std::shared_ptr<Ship>>& newShips, const std::shared_ptr<LanguageManager>& langOptions)
	: name(name), ships(newShips), langOptions(langOptions)
{
	allMissiles = std::vector<CruiseMissile>({CruiseMissile(2, 5, 0, 1), CruiseMissile(4, 4, 1, 2), CruiseMissile(6, 3, 2, 3), CruiseMissile(8, 2, 3, 4)}); 
}


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
		CruiseMissile& rocket = allMissiles[missileID];
		for (Coords beginningCoords : shipPtr->getCoords())
		{
			if (checkRocketPath(rocket.getAltitude(), rocket.getRange(), beginningCoords, destination.getCoords()))
			{
				rocket.effect(destination);
				return true;
			}
		}
		return false;
	}
	else return false;
}


bool Player::checkRocketPath(const int& altitude, const int& range, const Coords& beginningCoords, const Coords& endingCoords)
{
	if ((pow(beginningCoords.getX() - endingCoords.getX(), 2) + pow(beginningCoords.getY() - endingCoords.getY(), 2)) <= pow(range, 2)) 
	{
		// count linear function(y = ax + b) parameters, created by beginning an destination coordinates
		int Xbeginning = beginningCoords.getX();
		int Xending = endingCoords.getX();
		int Ybeginning = beginningCoords.getY();
		int Yending = endingCoords.getY();
		if (Xending - Xbeginning != 0)
		{
			float a = float (Yending - Ybeginning) / float(Xending - Xbeginning);
			float b = Ybeginning - a * Xbeginning;
			// calculate the rocket path by dividing each field to 10 parts to find out if the rocket goes through an island
			if (Xbeginning < Xending)
			{
				for (float x = Xbeginning; int(x) < Xending; x = x + 0.1)
				{
					float y = a * x + b;
					Coords currentCoords = Coords(int(x), int(y));
					std::shared_ptr<Island> islandPtr = boardPtr->findField(currentCoords).getIslandOnField();
					if (islandPtr != nullptr && islandPtr->getHeight() >= altitude) return false;
				}
				return true;
			}
			else
			{
				for (float x = Xbeginning; int(x) >= Xending; x = x - 0.1)
				{
					float y = a * x + b;
					Coords currentCoords = Coords(int(x), int(y));
					std::shared_ptr<Island> islandPtr = boardPtr->findField(currentCoords).getIslandOnField();
					if (islandPtr != nullptr && islandPtr->getHeight() >= altitude) return false;
				}
				return true;
			}
		}
		else
		{
			if (Yending > Ybeginning)
			{
				for (int y = Ybeginning; y <= Yending; y++)
				{
					Coords currentCoords = Coords(int(Xbeginning), int(y));
					std::shared_ptr<Island> islandPtr = boardPtr->findField(currentCoords).getIslandOnField();
					if (islandPtr != nullptr && islandPtr->getHeight() >= altitude) return false;
				}
			}
			else
			{
				for (int y = Ybeginning; y >= Yending; y--)
				{
					Coords currentCoords = Coords(int(Xbeginning), int(y));
					std::shared_ptr<Island> islandPtr = boardPtr->findField(currentCoords).getIslandOnField();
					if (islandPtr != nullptr && islandPtr->getHeight() >= altitude) return false;
				}
			}
			return true;
		}
	} 
	else return false;
}


bool Player::move(std::shared_ptr<Ship> shipPtr, Field& destination)
{
	Coords choosenCoords = shipPtr->getCoords()[0];
	Coords destinationCoords = destination.getCoords();
	return boardPtr->moveShipToField(shipPtr, destinationCoords.getX(), destinationCoords.getY());
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
		info += langOptions->getCommunicate("player_ship") + std::to_string(i) + ": ";
		info += std::string (currentShip->getCoords().size(), currentShip->getName());
		info += langOptions->getCommunicate("player_hit_points");
		info += std::to_string(currentShip->getHitPoints());
		info += langOptions->getCommunicate("player_missiles");
		int numberOfMissilies = currentShip->getMissileIDs().size();
		for (int j = 0; j<numberOfMissilies - 1; j++)
		{
			info += std::to_string(j) + ", ";
		}
		info += std::to_string(numberOfMissilies - 1);
		info += langOptions->getCommunicate("player_movement");
		info += std::to_string(currentShip->getMovement()) + "\n";
		i++;
	} 
	std::cout << info;
}


std::ostream& operator<<(std::ostream& os, const Player& player) 
{
	os << player.getName() << ";\n";
	return os;
}


std::istream& operator>>(std::istream& is, Player& player) 
{
	std::string name;
	char separator = ';';
	if (is >> name >> separator) player.setName(name);
	else is.setstate(std::ios::failbit);

    return is;
}
