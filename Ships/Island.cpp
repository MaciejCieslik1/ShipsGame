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


// File handling___________________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const Island& island)
{
	os << island.getHeight() << ';' << island.getCoords().size() << ";";
	for (const Coords& coord : island.getCoords()) 
	{
		os << coord;
	}
	os << '\n';
	return os;
}


std::istream& operator>>(std::istream& is, Island& island)
{
	int height;
    std::vector<Coords> coords;
	Coords coord;
    int coordsNumber;
    char separator = ';';
    if (is >> height >> separator >> coordsNumber >> separator) 
    {
		island.setHeight(height);
	}
    else is.setstate(std::ios::failbit); 
	for (int i=0; i<coordsNumber; i++)
	{
		if (is >> coord) coords.push_back(coord);
		else is.setstate(std::ios::failbit); 
	}
	island.setCoords(coords);
    return is;
}