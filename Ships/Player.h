#pragma once
#include "Board.h"
#include "CruiseMissile.h"
#include "LanguageManager.h"

class Player
{

    std::string name;
    std::vector<std::shared_ptr<Ship>> ships;
    std::shared_ptr<Board> boardPtr;
    std::vector<CruiseMissile> allMissiles;
    std::shared_ptr<LanguageManager> langOptions;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    friend std::istream& operator>>(std::istream& is, Player& player);

public:

	Player() = default;
    Player(const std::string &name, const std::vector<std::shared_ptr<Ship>> &newShips, const std::vector<CruiseMissile> &newAllMissiles,
    const std::shared_ptr<LanguageManager>& langOptions);
    Player(const std::string &name, const std::vector<std::shared_ptr<Ship>> &newShips, const std::shared_ptr<LanguageManager>& langOptions);
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
    
private:

    bool checkRocketPath(const int& altitude, const int& range, const Coords& beginningCoords, const Coords& endingCoords);
    
};
