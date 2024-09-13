#include "Field.h"


Field::Field()
{
    Coords newCoords;
    std::vector<std::shared_ptr<Field>> newAdjacent;
    coords = newCoords;
    adjacentFields = newAdjacent;
    shipOnField = nullptr;
    islandOnField = nullptr;

}


Field::Field(const Coords& newCoords) : coords(newCoords)
{
    std::vector<std::shared_ptr<Field>> newAdjacent;
    adjacentFields = newAdjacent;
    shipOnField = nullptr;
    islandOnField = nullptr;
}


Coords Field::getCoords() const 
{
    return coords;
}


std::vector<std::shared_ptr<Field>> Field::getAdjacentFields() const 
{
    return adjacentFields;
}


std::shared_ptr<Ship> Field::getShipOnField() const 
{
    return shipOnField;
}


std::shared_ptr<Island> Field::getIslandOnField() const 
{
    return islandOnField;
}


void Field::setCoords(const Coords& newCoords) 
{
    coords = newCoords;
}


void Field::setAdjacentFields(const std::vector<std::shared_ptr<Field>>& newAdjacentFields) 
{
    adjacentFields = newAdjacentFields;
}


void Field::setShipOnField(std::shared_ptr<Ship> newShipOnField) 
{
    shipOnField = newShipOnField;
}


void Field::setIslandOnField(const std::shared_ptr<Island>& newShoalOnField) 
{
    islandOnField = newShoalOnField;
}


void Field::addAdjacentField(std::shared_ptr<Field> field) 
{
    if (field && areAdjacent(coords, field->getCoords())) adjacentFields.push_back(field);
}


std::string Field::displayFieldCrate(void) const
{
    if (this->getShipOnField() != nullptr)
    {
        std::string shipDisplay {this->getShipOnField()->getName()};
        return "[" + shipDisplay + "]";
    }
    else if (this->getIslandOnField() != nullptr)
    {
        int IslandDisplay {this->getIslandOnField()->getHeight()};
        return "[" + std::to_string(IslandDisplay) + "]";
    }
    else return "[ ]";
}


void Field::setFieldEmpty(void)
{
    shipOnField = nullptr;
    islandOnField = nullptr;
}


void Field::shipHit(const int& damage) 
{
    if (damage > 0 && shipOnField) shipOnField->takeDamage(damage);
}
