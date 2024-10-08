#include "Coords.h"


Coords::Coords() 
{
	x = 0; y = 0;
}


Coords::Coords(const int& newX, const int& newY) 
{
	if (newX > 0 && newY > 0) 
	{
		x = newX;
		y = newY;
	}
	else 
	{
		x = 0;
		y = 0;
	}
}


int Coords::getX() const 
{
	return x;
}


int Coords::getY() const 
{
	return y;
}


void Coords::setX(const int& newX) 
{
	if (newX > 0) x = newX; 
	else throw invalid_coordinate("X coordinate must be positive integer");
}


void Coords::setY(const int& newY) 
{
	if (newY > 0) y = newY;
	else throw invalid_coordinate("Y coordinate must be positive integer");
}


std::ostream& operator<<(std::ostream& os, const Coords& coords)
{
	os << coords.getX() << ';' << coords.getY() << ';';
	return os;
}


std::istream& operator>>(std::istream& is, Coords& coords)
{
	char separator = ';';
	int x, y;
    if (is >> x >> separator >> y >> separator) 
    {
        coords.setX(x);
		coords.setY(y);
    }
    else is.setstate(std::ios::failbit); 
    return is;
}