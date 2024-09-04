#include "FunctionsM.h"
#include "Coords.h"
#include <cmath>
#include <algorithm>


bool isCorrectInt(const int& number) 
{
	if (number > 0) { return true; }
	return false;
}


bool isCorrectIntVector(const std::vector<int>& numbers) 
{
	for (int number : numbers)
	{
		if (!isCorrectInt(number)) { return false; }
	}
	return true;
}


bool isCorrectChar(const char& character) 
{
	if (character != ' ') { return true; }
	return false;
}


bool isCorrectCoordsVector(std::vector<Coords> shipCoords, const int& maxBoardSize)
{
	int coordsY = shipCoords[0].getY();
	int coordsX[shipCoords.size()];
	for (Coords coords : shipCoords)
	{
		if (coords.getY() != coordsY) return false;
	}
	std::sort(shipCoords.begin(), shipCoords.end(), [](const Coords& coords1, const Coords& coords2) 
	{
        return coords1.getX() < coords2.getX();
    });
	for (int i = 1; i < shipCoords.size(); i++)
	{
		if ((shipCoords[i].getX() - shipCoords[i - 1].getX() != 1) || shipCoords[i].getX() > maxBoardSize || shipCoords[i].getX() < 2) return false;
	}
	return true;
}


bool areAdjacent(const Coords& coords1, const Coords& coords2) 
{
	return (abs(coords1.getX() - coords2.getX())<=1) && (abs(coords1.getY() - coords2.getY())<=1);
}
