#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <cctype>
#include "Coords.h"


bool isCorrectInt(const int& number);
bool isCorrectIntVector(const std::vector<int>& numbers);
bool isLetter(char character);
bool isCorrectCoordsVector(std::vector<Coords> shipCoords, const int& maxBoardSize);
bool isCorrectCoordsVectorLimits(std::vector<Coords> shipCoords, const int& maxBoardSize);
bool areAdjacent(const Coords& coords1, const Coords& coords2);
std::vector<std::string> splitLine(const std::string& line);