#pragma once
#include "FunctionsM.h"

class Ship
{
protected:
	int movement;
	int hitPoints;
	char name;
    std::vector<Coords> coords;
	std::vector<int> missileIDs;

	friend std::ostream& operator<<(std::ostream& os, const Ship& ship);
	friend std::istream& operator>>(std::istream& is, Ship& ship);
public:
	Ship() = default;
	Ship(const int& movement, const int& hitPoints, const char& name, const std::vector<Coords>& coords, const int& maxBoardSize);
	virtual ~Ship();

	int getMovement() const;
	int getHitPoints() const;
	char getName() const;
	std::vector<Coords> getCoords() const;
	std::vector<int> getMissileIDs() const;

	void setMovement(const int& newMovement);
	void setHitPoints(const int& newHitPoints);
	void setName(const char& newName);
	void setCoords(const std::vector<Coords>& newCoords);
	void setMissileIDs(const std::vector<int>& newMissileIDs);

	void takeDamage(const int& damage);
	bool isAlive() const;
	bool hasMissile(const int& missileID) const;
	std::vector<Coords> extremeCoords() const;

	bool operator==(const Ship& other) const;
	bool operator!=(const Ship& other) const;
};

class Battleship : public Ship 
{
public:
	Battleship(const char& name, const std::vector<Coords>& newCoords, const int& maxBoardSize);
	Battleship(const int& movement, const int& hitPoints, const char& name, const std::vector<Coords>& coords, const int& maxBoardSize);
};

class Cruiser : public Ship 
{
public:
	Cruiser(const char& name, const std::vector<Coords>& newCoords, const int& maxBoardSize);
	Cruiser(const int& movement, const int& hitPoints, const char& name, const std::vector<Coords>& coords, const int& maxBoardSize);
};

class Destroyer : public Ship 
{
public:
	Destroyer(const char& name, const std::vector<Coords>& newCoords, const int& maxBoardSize);
	Destroyer(const int& movement, const int& hitPoints, const char& name, const std::vector<Coords>& coords, const int& maxBoardSize);
};

class Submarine : public Ship 
{
public:
	Submarine(const char& name, const std::vector<Coords>& newCoords, const int& maxBoardSize);
	Submarine(const int& movement, const int& hitPoints, const char& name, const std::vector<Coords>& coords, const int& maxBoardSize);
};