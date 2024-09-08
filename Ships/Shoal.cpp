#include "Shoal.h"


Shoal::Shoal(const char& newName, const std::vector<Coords>& newCoords, const int& maxBoardsize)
{
	if (isCorrectChar(newName)) name = newName;
	else throw invalid_name("Invalid character for name"); 
	if (isCorrectCoordsVector(newCoords, maxBoardsize)) 
	{
		coords = newCoords; 
	}
	else throw invalid_coordinate("Invalid shoal's coordinates");
}


Shoal::Shoal(const std::vector<Coords>& newCoords, const int& maxBoardsize)
{
	name = '0';
	if (isCorrectCoordsVectorLimits(newCoords, maxBoardsize)) 
	{
		coords = newCoords; 
	}
	else throw invalid_coordinate("Invalid shoal's coordinates");
}


char Shoal::getName() const
{
	return name;
}


std::vector<Coords> Shoal::getCoords() const
{
	return coords;
}


void Shoal::setName(const char& newName)
{
	if (isCorrectChar(newName)) { name = newName; }
	else { throw invalid_name("Invalid character for name"); }
}


void Shoal::setCoords(const std::vector<Coords>& newCoords)
{
	coords = newCoords;
}


bool Shoal::operator==(const Shoal &other) const
{
	if (this->getCoords().size() != other.getCoords().size()) { return false; }
	for (int i = 0; i < this->getCoords().size(); i++)
	{
		if (this->getCoords()[i].getX() != other.getCoords()[i].getX() || this->getCoords()[i].getY() != other.getCoords()[i].getY()) { return false; }
	}
	return true;
}


bool Shoal::operator!=(const Shoal& other) const
{
	return !(*this == other);
}


// File handling___________________________________________________________________________________


std::ostream& operator<<(std::ostream& os, const Shoal& shoal)
{
	os << shoal.name << ' ' <<  shoal.coords.size() << ' ';
	for (const auto& v : shoal.coords) 
	{
		os << v << ' ';
	}
	return os << '\n';
}

std::istream& operator>>(std::istream& is, Shoal& ship)
{
    char name;
    std::vector<Coords> coords;
    int numCoords;

    if (!(is >> name >> numCoords)) throw std::runtime_error("Error while loading ship data");

    coords.reserve(numCoords);
    for (int i = 0; i < numCoords; ++i) 
	{
        Coords coord;
        if (!(is >> coord)) {
            throw std::runtime_error("Error while loading ship coordinates");
        }
        coords.push_back(coord);
    }

    char separator;
    if (!(is >> separator) || separator != ';') throw std::runtime_error("Error while loading delimiter");
    ship.setName(name);
    ship.setCoords(coords);

    return is;
}