#include "FunctionsM.h"
#include "Field.h"


Field::Field()
{
    Coords newCoords;
    std::vector<std::shared_ptr<Field>> newAdjacent;
    coords = newCoords;
    adjacentFields = newAdjacent;
    shipOnField = nullptr;
    shoalOnField = nullptr;

}


Field::Field(const Coords& newCoords) : coords(newCoords)
{
    std::vector<std::shared_ptr<Field>> newAdjacent;
    adjacentFields = newAdjacent;
    shipOnField = nullptr;
    shoalOnField = nullptr;
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


std::shared_ptr<Shoal> Field::getShoalOnField() const 
{
    return shoalOnField;
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


void Field::setShoalOnField(const std::shared_ptr<Shoal>& newShoalOnField) 
{
    shoalOnField = newShoalOnField;
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
    else if (this->getShoalOnField() != nullptr)
    {
        std::string shoalDisplay {this->getShoalOnField()->getName()};
        return "[" + shoalDisplay + "]";
    }
    else return "[ ]";
}


void Field::setFieldEmpty(void)
{
    shipOnField = nullptr;
    shoalOnField = nullptr;
}


void Field::shipHit(const int& damage) 
{
    if (damage > 0 && shipOnField) shipOnField->takeDamage(damage);
}


std::ostream& operator<<(std::ostream& os, const Field& field) {
    os << field.coords << " ";
    if (field.shipOnField) os << *field.shipOnField; 
    else os << "empty";
    return os;
}

std::istream& operator>>(std::istream& is, Field& field) {
    is >> field.coords;
    std::string shipStatus;
    is >> shipStatus;
    if (shipStatus == "empty") field.shipOnField = nullptr;
    else 
    {
        // Wczytaj dane statku, jeśli nie jest puste
        std::shared_ptr<Ship> ship = std::make_shared<Ship>();
        is >> *ship;
        field.shipOnField = ship;
    }
    return is;
}