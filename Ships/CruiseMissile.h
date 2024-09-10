#pragma once
#include <vector>
#include <stdexcept>
#include <istream>
#include <cmath>
#include "Field.h"
#include "Coords.h"
#include "ShipsExceptions.h"

class CruiseMissile {
protected:
    int range;
    int damage;
    int missileID;
    int altitude;

    friend std::ostream& operator<<(std::ostream& os, const CruiseMissile& missle);
    friend std::istream& operator>>(std::istream& is, CruiseMissile& missle);
public:
    CruiseMissile(const int& range, const int& damage, const int& missileID, const int& altitude);

    int getRange() const;
    int getDamage() const;
    int getMissileID() const;
    int getAltitude() const;

    void setRange(const int& newRange);
    void setDamage(const int& newDamage);
    void setAltitude(const int& newAltitude);

    void effect(Field& destination);

    bool operator==(const CruiseMissile& other) const;
    bool operator!=(const CruiseMissile& other) const;
};
