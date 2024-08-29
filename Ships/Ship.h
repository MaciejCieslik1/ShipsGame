#pragma once
#include <string>
#include <vector>
#include <istream>
#include <algorithm>
#include <stdexcept>
#include "Coords.h"
#include "FunctionsM.h"
#include "ShipsExceptions.h"

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
	~Ship();
	Ship(const int& movement, const int& hitPoints, const char& name, const std::vector<Coords>& coords);

	int getMovement() const;
	int getHitPoints() const;
	char getName() const;
	std::vector<Coords> getCoords() const;
	std::vector<int> getMissileIDs() const;

	void setMovement(const int& newMovement);
	void setHitPoints(const int& newHitPoints);
	void setName(const char& newName);
	void setCoords(const std::vector<Coords>& newCoords);
	virtual void setMissileIDs(const std::vector<int>& newMissileIDs);

	void takeDamage(const int& damage);
	bool isAlive() const;
	bool hasMissile(const int& missileID) const;
	std::vector<Coords> extremeCoords() const;

	char displayOnBoard() const;
	virtual char displayOnBoard(bool isActive) const;
	bool operator==(const Ship& other) const;
	bool operator!=(const Ship& other) const;
};

class Carrier4 : public Ship {
public:
	Carrier4(const std::vector<Coords>& newCoords);
	char displayOnBoard(bool isActive) const override;
};

class Battleship2 : public Ship {
	Battleship2(const std::vector<Coords>& newCoords);
	char displayOnBoard(bool isActive) const override;
};

class Destroyer1 : public Ship {
	Destroyer1(const std::vector<Coords>& newCoords);
	char displayOnBoard(bool isActive) const override;
};
