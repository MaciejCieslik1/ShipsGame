#include "Island.h"

Island::Island(const std::vector<Coords>& newCoords, const int& newHeight, const int& newMaxBoardSize)
{
	if(isCorrectInt(newHeight) || newHeight == 0) height = newHeight;
	else throw invalid_height("Invalid island's height");
	if (isCorrectCoordsVectorLimits(newCoords, newMaxBoardSize)) 
	{
		coords = newCoords; 
	}
	else throw invalid_coordinate("Invalid island's coordinates");
}


std::vector<Coords> Island::getCoords() const
{
	return coords;
}


int Island::getHeight() const
{
	return height;
}


void Island::setCoords(const std::vector<Coords>& newCoords)
{
	coords = newCoords;
}


void Island::setHeight(const int& newHeight)
{
	if (isCorrectInt(newHeight)) height = newHeight;
	else throw invalid_height("Invalid island height");
}


bool Island::operator==(const Island &other) const
{
	if (this->getCoords().size() != other.getCoords().size()) { return false; }
	for (int i = 0; i < this->getCoords().size(); i++)
	{
		if (this->getCoords()[i].getX() != other.getCoords()[i].getX() || this->getCoords()[i].getY() != other.getCoords()[i].getY()) { return false; }
	}
	return true;
}


bool Island::operator!=(const Island& other) const
{
	return !(*this == other);
}


// File handling___________________________________________________________________________________


std::ostream& operator<<(std::ostream& os, const Island& shoal)
{
	os << shoal.height << ' ' <<  shoal.coords.size() << ' ';
	for (const auto& v : shoal.coords) 
	{
		os << v << ' ';
	}
	return os << '\n';
}

std::istream& operator>>(std::istream& is, Island& ship)
{
    int height;
    std::vector<Coords> coords;
    int numCoords;

    if (!(is >> height >> numCoords)) throw std::runtime_error("Error while loading ship data");

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
    ship.setHeight(height);
    ship.setCoords(coords);

    return is;
}
