#include "FunctionsM.h"
#include "Coords.h"
#include <cmath>

bool isCorrectInt(const int& number) {
	if (number > 0) { return true; }
	return false;
}

bool isCorrectIntVector(const std::vector<int>& numbers) {
	for (int number : numbers)
	{
		if (!isCorrectInt(number)) { return false; }
	}
	return true;
}

bool areAdjacent(const Coords& coords1, const Coords& coords2) {
	return (abs(coords1.getX() - coords2.getX())<=1) && (abs(coords1.getY() - coords2.getY())<=1);
}
