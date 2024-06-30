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
    std::vector<Ship*> ships;
    Board* boardPtr;
    std::vector<CruiseMissile> allMissiles;
    int maxMoves;
    int moveCounter;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    friend std::istream& operator>>(std::istream& is, Player& player);
public:
	Player() = default;
    ~Player();
    Player(const std::string& name, const int& maxMoves, const int& moveCounter);
    Player(const std::string &name, const std::vector<Ship *> &newShips, const int &newMaxMoves, const std::vector<CruiseMissile> &newAllMissiles);
    Player(const std::vector<Ship*>& newShips, Board*& newBoard, const int& newMaxMoves, const std::vector<CruiseMissile>& newAllMissiles);
    std::vector<Ship*> getShips() const;
    Board* getBoardPtr() const;
    std::vector<CruiseMissile> getAllMissilies() const;
    int getMaxMoves() const;
    int getMoveCounter() const;
    std::string getName() const;

    void setName(const std::string newName);
    void setShips(const std::vector<Ship*>& newShips);
    void setBoard(Board* newBoard);
    void setAllMissiles(const std::vector<CruiseMissile>& newAllMissiles);
    void setMaxMoves(const int& newMaxMoves);
    void setMoveCounter(const int& newMoveCounter);

    bool decrementMoves(const int& n);
    bool fire(Ship* ship, Field& destination, const int& missileID);
    bool move(Ship* ship, Field& destination);
    void forgetShip(Ship* ship);

    bool operator==(const Player& other) const;
    bool operator!=(const Player& other) const;
};
