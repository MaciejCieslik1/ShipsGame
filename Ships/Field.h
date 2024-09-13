#pragma once
#include <iostream>
#include <memory>
#include "Coords.h"
#include "Ship.h"
#include "Island.h"

class Field
{
protected:
    Coords coords;
	std::vector<std::shared_ptr<Field>> adjacentFields;
	std::shared_ptr<Ship> shipOnField;
	std::shared_ptr<Island> islandOnField;

public:
	Field();
	Field(const Coords& newCoords);

	Coords getCoords() const;
	std::vector<std::shared_ptr<Field>> getAdjacentFields() const;
	std::shared_ptr<Ship> getShipOnField() const;
	std::shared_ptr<Island> getIslandOnField() const;

	void setCoords(const Coords& newCoords);
	void setAdjacentFields(const std::vector<std::shared_ptr<Field>>& newAdjacentFields);
	void setShipOnField(std::shared_ptr<Ship> newShipOnField);
	void setIslandOnField(const std::shared_ptr<Island>& newIsland);
	void addAdjacentField(std::shared_ptr<Field> field);

	std::string displayFieldCrate(void) const;
	void setFieldEmpty(void);
	void shipHit(const int& damage);
};
