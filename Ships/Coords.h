#pragma once
#include <stdexcept>
#include <istream>
#include "ShipsExceptions.h"

class Coords {
    int x;
    int y;

    friend std::ostream& operator<<(std::ostream& os, const Coords& coords);
	friend std::istream& operator>>(std::istream& is, Coords& coords);
public:
    Coords();
    Coords(const int& newX, const int& newY);
    int getX() const;
    int getY() const;
    void setX(const int& newX);
    void setY(const int& newY);
};
