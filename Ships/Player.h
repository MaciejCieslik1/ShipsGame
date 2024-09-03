#pragma once
#include <vector>
#include <stdexcept>
#include "Ship.h"
#include "Field.h"
#include "Board.h"
#include "CruiseMissile.h"
#include "FunctionsM.h"

class Player
{
protected:
    std::string name;
    std::vector<std::shared_ptr<Ship>> ships;
    std::shared_ptr<Board> boardPtr;
    std::vector<CruiseMissile> allMissiles;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    friend std::istream& operator>>(std::istream& is, Player& player);
public:
	Player() = default;
    ~Player();
    Player(const std::string &name, const std::vector<std::shared_ptr<Ship>> &newShips, const std::vector<CruiseMissile> &newAllMissiles);
    Player(const std::string &name, const std::vector<std::shared_ptr<Ship>> &newShips);
    std::vector<std::shared_ptr<Ship>> getShips() const;
    std::shared_ptr<Board> getBoardPtr() const;
    std::vector<CruiseMissile> getAllMissilies() const;
    std::string getName() const;

    void setName(const std::string newName);
    void setShips(const std::vector<std::shared_ptr<Ship>>& newShips);
    void setBoard(std::shared_ptr<Board> newBoard);
    void setAllMissiles(const std::vector<CruiseMissile>& newAllMissiles);

    bool fire(std::shared_ptr<Ship> ship, Field& destination, const int& missileID);
    bool move(std::shared_ptr<Ship> ship, Field& destination);
    void forgetShip(std::shared_ptr<Ship> ship);
    void shipsInfo() const;

    bool operator==(const Player& other) const;
    bool operator!=(const Player& other) const;
};
