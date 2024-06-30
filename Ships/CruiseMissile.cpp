#include "CruiseMissile.h"

CruiseMissile::CruiseMissile(const int& newRange, const int& newDamage, const int& newMissileID)
{
	if (isCorrectInt(newRange)) { range = newRange; }
	else { throw std::invalid_argument("Range must be positive integer"); }
	if (isCorrectInt(newDamage)) { damage = newDamage; }
	else { throw std::invalid_argument("Damage must be positive integer"); }
	if (newMissileID>=0) { missileID = newMissileID; }
	else { throw std::invalid_argument("Missile ID must be positive integer"); }
}

CruiseMissile::~CruiseMissile() {}


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


bool CruiseMissile::fire(const Coords& coords, Field& destination) {
	Coords coords1 = destination.getCoords();
	if ((pow(coords.getX() - coords1.getX(), 2) + pow(coords.getY() - coords1.getY(), 2)) <= pow(range, 2)) {
		effect(destination);
		return true;
	} else return false;
}

void CruiseMissile::effect(Field& destination) {
	destination.shipHit(damage);
}

bool CruiseMissile::operator==(const CruiseMissile& other) const {
	// int range;
    // int damage;
    // int missileID;
	return (range == other.range && damage == other.damage && missileID == other.missileID);
}

bool CruiseMissile::operator!=(const CruiseMissile& other) const {
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const CruiseMissile& missle)
{
	os << missle.range << ' ' << missle.damage << ' ' << missle.missileID << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, CruiseMissile& missle)
{
	int range, damage, missleID;

	if (is >> range >> damage >> missleID) {
		missle.range = range;
		missle.damage = damage;
		missle.missileID = missleID;
	}
	else {
		is.setstate(std::ios::failbit);
	}
	return is;
}
