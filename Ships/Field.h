#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Coords.h"
#include "Ship.h"

class Field
{
protected:
    Coords coords;
	std::vector<Field*> adjacentFields;
	Ship* shipOnField;

	friend std::ostream& operator<<(std::ostream& os, const Field& field);
	friend std::istream& operator>>(std::istream& is, Field& field);

public:
	Field();
	Field(const Coords& newCoords);
	~Field();

	Coords getCoords() const;
	std::vector<Field*> getAdjacentFields() const;
	Ship* getShipOnField() const;

	void setCoords(const Coords& newCoords);
	void setAdjacentFields(const std::vector<Field*>& newAdjacentFields);
	void setShipOnField(Ship* newShipOnField);
	void addAdjacentField(Field* field);

	std::string displayFieldCrate(void) const;
	void setFieldEmpty(void);
	void shipHit(const int& damage);
};
