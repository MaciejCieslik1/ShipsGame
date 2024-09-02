#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "Coords.h"
#include "Ship.h"

class Field
{
protected:
    Coords coords;
	std::vector<std::shared_ptr<Field>> adjacentFields;
	std::shared_ptr<Ship> shipOnField;

	friend std::ostream& operator<<(std::ostream& os, const Field& field);
	friend std::istream& operator>>(std::istream& is, Field& field);

public:
	Field();
	Field(const Coords& newCoords);
	~Field();

	Coords getCoords() const;
	std::vector<std::shared_ptr<Field>> getAdjacentFields() const;
	std::shared_ptr<Ship> getShipOnField() const;

	void setCoords(const Coords& newCoords);
	void setAdjacentFields(const std::vector<std::shared_ptr<Field>>& newAdjacentFields);
	void setShipOnField(std::shared_ptr<Ship> newShipOnField);
	void addAdjacentField(std::shared_ptr<Field> field);

	std::string displayFieldCrate(void) const;
	void setFieldEmpty(void);
	void shipHit(const int& damage);
};
