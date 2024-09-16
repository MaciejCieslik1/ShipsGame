#include "Ship.h"


Ship::Ship(const int& newMovement, const int& newHitPoints, const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardsize)
{
	if (isCorrectInt(newMovement)) movement = newMovement;
	else throw invalid_movement_value("Movement must be positive integer");
	if (isCorrectInt(newHitPoints)) hitPoints = newHitPoints;
	else throw invalid_hit_point_value("Hit points must be positive integer");
	if (isLetter(newName)) name = newName;
	else throw invalid_name("Invalid character for name"); 
	if (isCorrectCoordsVector(newCoords, maxBoardsize)) 
	{
		coords = newCoords; 
	}
	else throw invalid_coordinate("Invalid ship's coordinates");
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
	if (isLetter(newName)) { name = newName; }
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


// Battleship________________________________________________________________________________________
Battleship::Battleship(const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardSize)
    : Ship(4, 10, newName, newCoords, maxBoardSize)
	{
		if (coords.size() != 4) throw invalid_coordinate("Battleship must take exactly 4 fields"); 
		missileIDs = { 0, 1, 2, 3 };
	}


Battleship::Battleship(const int& movement, const int& hitPoints, const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardSize)
    : Ship(movement, hitPoints, newName, newCoords, maxBoardSize)
	{
		if (coords.size() != 4) throw invalid_coordinate("Battleship must take exactly 4 fields"); 
		missileIDs = { 0, 1, 2, 3 };
	}


std::ostream& operator<<(std::ostream& os, const Battleship& battleship)
{
	os << "Battleship;" << battleship.getName() << ';' << battleship.getCoords().size() << ';';
	for (const Coords& coord : battleship.getCoords()) 
	{
		os << coord;
	}
	os << '\n';
	return os;
}


std::istream& operator>>(std::istream& is, Battleship& battleship)
{
	char name;
    std::vector<Coords> coords;
	Coords coord;
    int coordsNumber;
    char separator = ';';
	std::string shipType = "Battleship;";
    if (is >> shipType >> name >> separator >> coordsNumber >> separator) 
    {
		battleship.setName(name);
	}
    else is.setstate(std::ios::failbit); 
	for (int i=0; i<coordsNumber; i++)
	{
		if (is >> coord) coords.push_back(coord);
		else is.setstate(std::ios::failbit); 
	}
	battleship.setCoords(coords);
    return is;
}


// Cruiser____________________________________________________________________________________
Cruiser::Cruiser(const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardSize)
    : Ship(6, 8, newName, newCoords, maxBoardSize)
	{
		if (coords.size() != 3) throw invalid_coordinate("Cruiser must take exactly 3 fields"); 
		missileIDs = { 0, 1, 2 };
	}


Cruiser::Cruiser(const int& movement, const int& hitPoints, const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardSize)
    : Ship(movement, hitPoints, newName, newCoords, maxBoardSize)
	{
		if (coords.size() != 3) throw invalid_coordinate("Cruiser must take exactly 3 fields"); 
		missileIDs = { 0, 1, 2 };
	}


std::ostream& operator<<(std::ostream& os, const Cruiser& cruiser)
{
	os << "Cruiser;" << cruiser.getName() << ';' << cruiser.getCoords().size() << ';';
	for (const Coords& coord : cruiser.getCoords()) 
	{
		os << coord;
	}
	return os;
}


std::istream& operator>>(std::istream& is, Cruiser& cruiser)
{
	char name;
    std::vector<Coords> coords;
	Coords coord;
    int coordsNumber;
    char separator = ';';
	std::string shipType = "Cruiser;";
    if (is >> shipType >> name >> separator >> coordsNumber >> separator) 
    {
		cruiser.setName(name);
	}
    else is.setstate(std::ios::failbit); 
	for (int i=0; i<coordsNumber; i++)
	{
		if (is >> coord) coords.push_back(coord);
		else is.setstate(std::ios::failbit); 
	}
	cruiser.setCoords(coords);
    return is;
}


// Destroyer______________________________________________________________________________________
Destroyer::Destroyer(const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardSize)
    : Ship(8, 6, newName, newCoords, maxBoardSize)
	{
		if (coords.size() != 2) throw invalid_coordinate("Destroyer must take exactly 2 fields"); 
		missileIDs = { 0, 1 };
	}


Destroyer::Destroyer(const int& movement, const int& hitPoints, const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardSize)
    : Ship(movement, hitPoints, newName, newCoords, maxBoardSize)
	{
		if (coords.size() != 2) throw invalid_coordinate("Destroyer must take exactly 2 fields"); 
		missileIDs = { 0, 1 };
	}


std::ostream& operator<<(std::ostream& os, const Destroyer& destroyer)
{
	os << "Destroyer;" << destroyer.getName() << ';' << destroyer.getCoords().size() << ';';
	for (const Coords& coord : destroyer.getCoords()) 
	{
		os << coord;
	}
	return os;
}


std::istream& operator>>(std::istream& is, Destroyer& destroyer)
{
	char name;
    std::vector<Coords> coords;
	Coords coord;
    int coordsNumber;
    char separator = ';';
	std::string shipType = "Destroyer;";
    if (is >> shipType >> name >> separator >> coordsNumber >> separator) 
    {
		destroyer.setName(name);
	}
    else is.setstate(std::ios::failbit); 
	for (int i=0; i<coordsNumber; i++)
	{
		if (is >> coord) coords.push_back(coord);
		else is.setstate(std::ios::failbit); 
	}
	destroyer.setCoords(coords);
    return is;
}


// Submarine______________________________________________________________________________________
Submarine::Submarine(const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardSize)
    : Ship(10, 4, newName, newCoords, maxBoardSize)
	{
		if (coords.size() != 2) throw invalid_coordinate("Submarine must take exactly 1 field"); 
		missileIDs = { 0 };
	}


Submarine::Submarine(const int& movement, const int& hitPoints, const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardSize)
    : Ship(movement, hitPoints, newName, newCoords, maxBoardSize)
	{
		if (coords.size() != 2) throw invalid_coordinate("Submarine must take exactly 1 field"); 
		missileIDs = { 0 };
	}


std::ostream& operator<<(std::ostream& os, const Submarine& submarine)
{
	os << "Submarine;" << submarine.getName() << ';' << submarine.getCoords().size() << ';';
	for (const Coords& coord : submarine.getCoords()) 
	{
		os << coord;
	}
	return os;
}


std::istream& operator>>(std::istream& is, Submarine& submarine)
{
	char name;
    std::vector<Coords> coords;
	Coords coord;
    int coordsNumber;
    char separator = ';';
	std::string shipType = "Submarine;";
    if (is >> shipType >> name >> separator >> coordsNumber >> separator) 
    {
		submarine.setName(name);
	}
    else is.setstate(std::ios::failbit); 
	for (int i=0; i<coordsNumber; i++)
	{
		if (is >> coord) coords.push_back(coord);
		else is.setstate(std::ios::failbit); 
	}
	submarine.setCoords(coords);
    return is;
}