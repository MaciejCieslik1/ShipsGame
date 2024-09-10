#pragma once
#include "FunctionsM.h"


class Island
{
protected:
    std::vector<Coords> coords;
	int height;

	friend std::ostream& operator<<(std::ostream& os, const Island& island);
	friend std::istream& operator>>(std::istream& is, Island& island);
public:
	Island() = default;
    Island(const std::vector<Coords>& coords, const int& height, const int& maxBoardSize);

	std::vector<Coords> getCoords() const;
	int getHeight() const;

	void setCoords(const std::vector<Coords>& newCoords);
	void setHeight(const int& newHeight);

	bool operator==(const Island& other) const;
	bool operator!=(const Island& other) const;
};
