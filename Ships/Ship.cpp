#include "Ship.h"
#include "FunctionsM.h"

Ship::Ship(const int& newMovement, const int& newHitPoints, const char& newName, const std::vector<Coords>& newCoords)
{
	if (isCorrectInt(newMovement)) { movement = newMovement; }
	else { throw invalid_movement_value("Movement must be positive integer"); }
	if (isCorrectInt(newHitPoints)) { hitPoints = newHitPoints; }
	else { throw invalid_hit_point_value("Hit points must be positive integer"); }
	if (isCorrectChar(newName)) { name = newName; }
	else { throw invalid_name("Invalid character for name"); }
	coords = newCoords;
	std::vector<int> missilies = { 0, 1, 2 };
	missileIDs = missilies;
}


Ship::~Ship() {}


int Ship::getMovement() const
{
	return movement;
}


int Ship::getHitPoints() const
{
	return hitPoints;
}

char Ship::getName() const
{
	return name;
}

std::vector<Coords> Ship::getCoords() const
{
	return coords;
}


std::vector<int> Ship::getMissileIDs() const
{
	return missileIDs;
}


void Ship::setMovement(const int& newMovement)
{
	if (isCorrectInt(newMovement)) { movement = newMovement; }
	else { throw invalid_movement_value("Movement must be positive integer"); }
}


void Ship::setHitPoints(const int& newHitPoints)
{
	if (isCorrectInt(newHitPoints)) { hitPoints = newHitPoints; }
	else { throw invalid_hit_point_value("Hit points must be positive integer"); }
}


void Ship::setName(const char& newName)
{
	if (isCorrectChar(newName)) { name = newName; }
	else { throw invalid_name("Invalid character for name"); }
}


void Ship::setCoords(const std::vector<Coords>& newCoords)
{
	coords = newCoords;
}


void Ship::setMissileIDs(const std::vector<int>& newMissileIDs)
{
	if (isCorrectIntVector(newMissileIDs)) { missileIDs = newMissileIDs; }
	else { throw invalid_missle_id("Missilies IDs must be vector of positive integers"); }
}


void Ship::takeDamage(const int& damage)
{
	if (isCorrectInt(damage)) { hitPoints -= damage; }
	else { throw invalid_damage_value("Damage must be positive integer"); }
}


bool Ship::isAlive() const
{
	if (hitPoints > 0) { return true; }
	return false;
}


bool Ship::hasMissile(const int& missileID) const
{
	if (missileID >=0)
	{
		if (std::find(missileIDs.begin(), missileIDs.end(), missileID) != missileIDs.end()) { return true; }
		return false;
	}
	return false;
}


std::vector<Coords> Ship::extremeCoords() const
{
	std::vector<Coords> allShipCoords = getCoords();
	std::vector<Coords> extreme;
	if (allShipCoords.size() > 1)
	{
		Coords biggestCoord = allShipCoords[0];
		Coords smallestCoord = allShipCoords[0];
		if (allShipCoords[0].getX() == allShipCoords[1].getX())
		{
			for (Coords currentCoord : allShipCoords)
			{
				if (currentCoord.getY() > biggestCoord.getY())
				{
					biggestCoord = currentCoord;
				}
				if (currentCoord.getY() < smallestCoord.getY())
				{
					smallestCoord = currentCoord;
				}
			}
		}
		else
		{
			for (Coords currentCoord : allShipCoords)
			{
				if (currentCoord.getX() > biggestCoord.getX())
				{
					biggestCoord = currentCoord;
				}
				if (currentCoord.getX() < smallestCoord.getX())
				{
					smallestCoord = currentCoord;
				}
			}
		}
		extreme.push_back(biggestCoord);
		extreme.push_back(smallestCoord);
		return extreme;
	}
	else
	{
		extreme.push_back(allShipCoords[0]);
		extreme.push_back(allShipCoords[0]);
		return extreme;
	}
}

char Ship::displayOnBoard() const
{
	return 'S';
}

char Ship::displayOnBoard(bool isActive) const
{
	return isActive ? 'S' : 's';
}

bool Ship::operator==(const Ship &other) const
{
	if (this->getHitPoints() != other.getHitPoints() || this->getMovement() != other.getMovement()) { return false; }
	if (this->getCoords().size() != other.getCoords().size() || this->getMissileIDs().size() != other.getMissileIDs().size()) { return false; }
	for (int i = 0; i < this->getCoords().size(); i++)
	{
		if (this->getCoords()[i].getX() != other.getCoords()[i].getX() || this->getCoords()[i].getY() != other.getCoords()[i].getY()) { return false; }
	}
	for (int i = 0; i < this->getMissileIDs().size(); i++)
	{
		if (this->getMissileIDs()[i] != other.getMissileIDs()[i]) { return false; }
	}
	return true;
}


bool Ship::operator!=(const Ship& other) const
{
	return !(*this == other);
}

// Carrier4________________________________________________________________________________________
Carrier4::Carrier4(const std::vector<Coords>& newCoords) {
	if (coords.size()!=4) { throw invalid_movement_value("Carrier must take exactly 4 fields"); }
	coords = newCoords; movement = 5; hitPoints = 20;
	std::vector<int> missilies = { 0, 1, 2 };
	missileIDs = missilies;
}
char Carrier4::displayOnBoard(bool isActive) const {
	return isActive ? 'C' : 'c';
}

// Battleship2_____________________________________________________________________________________
Battleship2::Battleship2(const std::vector<Coords>& newCoords) {
	if (coords.size()!=2) { throw invalid_movement_value("Battleship must take exactly 2 fields"); }
	coords = newCoords; movement = 10; hitPoints = 10;
	std::vector<int> missilies = { 0, 1 };
	missileIDs = missilies;
}
char Battleship2::displayOnBoard(bool isActive) const {
	return isActive ? 'B' : 'b';
}

// Destroyer1______________________________________________________________________________________
Destroyer1::Destroyer1(const std::vector<Coords>& newCoords) {
	if (coords.size()!=1) { throw invalid_movement_value("Destroyer must take exactly 1 fields"); }
	coords = newCoords; movement = 20; hitPoints = 5;
	std::vector<int> missilies = { 0 };
	missileIDs = missilies;
}
char Destroyer1::displayOnBoard(bool isActive) const {
	return isActive ? 'D' : 'd';
}

// File handling___________________________________________________________________________________

std::ostream& operator<<(std::ostream& os, const Ship& ship)
{
	os << ship.movement << ' ' << ship.hitPoints << ' ' <<  ship.coords.size() << ' ' << ship.missileIDs.size() << ' ';
	for (const auto& v : ship.coords) {
		os << v << ' ';
	}
	for (const auto& v : ship.missileIDs) {
		os << v << ' ';
	}
	return os << '\n';
}

std::istream& operator>>(std::istream& is, Ship& ship)
{
    int movement, hitPoints;
    std::vector<Coords> coords;
    std::vector<int> missileIDs;
    int numCoords, numMissiles;

    if (!(is >> movement >> hitPoints >> numCoords)) {
        throw std::runtime_error("Error while loading ship data");
    }

    coords.reserve(numCoords);
    for (int i = 0; i < numCoords; ++i) {
        Coords coord;
        if (!(is >> coord)) {
            throw std::runtime_error("Error while loading ship coordinates");
        }
        coords.push_back(coord);
    }

    char separator;
    if (!(is >> separator) || separator != ';') {
        throw std::runtime_error("Error while loading delimiter");
    }

    if (!(is >> numMissiles)) {
        throw std::runtime_error("Error while loading missile Id's");
    }
    missileIDs.reserve(numMissiles);
    for (int i = 0; i < numMissiles; ++i) {
        int missileID;
        if (!(is >> missileID)) {
            throw std::runtime_error("Error while loading missile Id's");
        }
        missileIDs.push_back(missileID);
    }

    ship.setMovement(movement);
    ship.setHitPoints(hitPoints);
    ship.setCoords(coords);
    ship.setMissileIDs(missileIDs);

    return is;
}