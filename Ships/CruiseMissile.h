#pragma once
#include "Field.h"

class CruiseMissile {
    int range;
    int damage;
    int missileID;
    int altitude;
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
