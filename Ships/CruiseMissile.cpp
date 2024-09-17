#include "CruiseMissile.h"


CruiseMissile::CruiseMissile(const int& newRange, const int& newDamage, const int& newMissileID, const int& newAltitude)
{
	if (isCorrectInt(newRange)) range = newRange;
	else throw std::invalid_argument("Range must be positive integer");
	if (isCorrectInt(newDamage)) damage = newDamage;
	else throw std::invalid_argument("Damage must be positive integer");
	if (newMissileID >= 0) missileID = newMissileID;
	else throw std::invalid_argument("Missile ID must be positive integer");
	if (newAltitude >= 0) altitude = newAltitude;
	else throw std::invalid_argument("Altitude must be positive integer");
}


int CruiseMissile::getRange() const
{
	return range;
}


int CruiseMissile::getDamage() const
{
	return damage;
}


int CruiseMissile::getMissileID() const
{
	return missileID;
}


int CruiseMissile::getAltitude() const
{
	return altitude;
}


void CruiseMissile::setRange(const int& newRange)
{
	if (isCorrectInt(newRange)) { range = newRange; }
	else { throw std::invalid_argument("Range must be positive integer"); }
}


void CruiseMissile::setDamage(const int& newDamage)
{
	if (isCorrectInt(newDamage)) { damage = newDamage; }
	else { throw std::invalid_argument("Damage must be positive integer"); }
}


void CruiseMissile::setAltitude(const int& newAltitude)
{
	if (newAltitude >= 0) altitude = newAltitude;
	else throw std::invalid_argument("Altitude must be positive integer");
}


void CruiseMissile::effect(Field& destination) {
	destination.shipHit(damage);
}


bool CruiseMissile::operator==(const CruiseMissile& other) const {
	return (range == other.range && damage == other.damage && missileID == other.missileID && altitude == other.altitude);
}


bool CruiseMissile::operator!=(const CruiseMissile& other) const {
	return !(*this == other);
}
