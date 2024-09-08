#pragma once
#include <string>
#include <vector>
#include "Coords.h"
#include "FunctionsM.h"


class Shoal
{
protected:
	char name;
    std::vector<Coords> coords;

	friend std::ostream& operator<<(std::ostream& os, const Shoal& shoal);
	friend std::istream& operator>>(std::istream& is, Shoal& shoal);
public:
	Shoal() = default;
    Shoal(const char& name, const std::vector<Coords>& coords, const int& maxBoardSize);
    Shoal(const std::vector<Coords>& coords, const int& maxBoardSize);

	char getName() const;
	std::vector<Coords> getCoords() const;

	void setName(const char& newName);
	void setCoords(const std::vector<Coords>& newCoords);

	bool operator==(const Shoal& other) const;
	bool operator!=(const Shoal& other) const;
};
