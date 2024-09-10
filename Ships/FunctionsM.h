#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include "Coords.h"


bool isCorrectInt(const int& number);
bool isCorrectIntVector(const std::vector<int>& numbers);
bool isCorrectChar(const char& character);
bool isCorrectCoordsVector(std::vector<Coords> shipCoords, const int& maxBoardSize);
bool isCorrectCoordsVectorLimits(std::vector<Coords> shipCoords, const int& maxBoardSize);
bool areAdjacent(const Coords& coords1, const Coords& coords2);