#include "Game.h"


Game::Game(const std::vector<std::shared_ptr<Player>>& newPlayers, const std::vector<std::shared_ptr<Island>>& islands, 
    const int& maxBoardSize, std::shared_ptr<LanguageManager> language) 
    : langOptions(language), players(newPlayers), islands(islands)
{
    currentPlayer = 0;
    numberOfTurns = 1;
    winner = nullptr;
    setIsOn(true);
    generateBoard(maxBoardSize);
}


std::shared_ptr<Board> Game::getBoard() const 
{
    return board;
}


const std::vector<std::shared_ptr<Player>>& Game::getPlayers() const 
{
    return players;
}


std::vector<std::shared_ptr<Island>> Game::getIslands() const
{
    return islands;
}


int	Game::getCurrentPlayerIndex() const 
{
    return currentPlayer;
}


int Game::getNumberOfTurns() const 
{
    return numberOfTurns;
}


std::shared_ptr<Player> Game::getWinner() const 
{
    return winner;
}


int Game::getTurnStage() const 
{
    return turnStage;
}


bool Game::getIsOn() const 
{
    return isOn;
}


int Game::getAction() const
{
    return action;
}


std::shared_ptr<Ship> Game::getShip() const
{
    return ship;
}


Field Game::destinaion() const
{
    return destination;
}


int Game::getMissileID() const
{
    return missileID;
}


void Game::setBoard(std::shared_ptr<Board> new_board) 
{
    board = new_board;
}


void Game::setPlayers(const std::vector<std::shared_ptr<Player>>& new_players) 
{
    players = new_players;
}


void Game::setIslands(const std::vector<std::shared_ptr<Island>>& newIslands)
{
    islands = newIslands;
}


void Game::setCurrentPlayerIndex(const int& new_player) 
{
    if (new_player >= players.size() || new_player < 0) throw std::invalid_argument("Player index must be in range [0, <number of players>)");
    else currentPlayer = new_player;
}


void Game::setNumberOfTurns(const int& new_number_of_turns) 
{
    numberOfTurns = new_number_of_turns;
}


void Game::setWinner(std::shared_ptr<Player> new_winner) 
{
    for (std::shared_ptr<Player> player : players) 
    {
        if (player == new_winner) 
        {
            winner = new_winner; 
            return;
        }
    } 
    throw std::invalid_argument("New winner must be one of the active players");
}


void Game::setTurnStage(const int& newStage) 
{
    turnStage = newStage;
}


void Game::setIsOn(const bool& state)
{
    isOn = state;
}


void Game::setAction(const int& newAction)
{
    if (action == 0 || action == 1 || action == 2) action = newAction;
    else throw std::invalid_argument("New action must be equal to 0, 1 or 2");
}


void Game::setShip(const std::shared_ptr<Ship>& newShip)
{
    ship = newShip;
}


void Game::setMissileID(const int& newMissileID)
{
    if (isCorrectInt(newMissileID) || newMissileID == 0) missileID = newMissileID;
    else throw std::invalid_argument("New missileID must be a positive integer");
}


void Game::mainGameProcess(const int& input, const int& maxBoardSize, bool& correctMoveFlag) 
{
    switch (turnStage) 
    {
        case 0: pickAction(input); break;
        case 1: pickShip(input); break;
        case 2: pickDestination(input, maxBoardSize); break;
        case 3: pickMissile(input); break;
        case 4: confirm(input, correctMoveFlag); break;
    }
}


void Game::pickAction(const int& input) 
{
    if (input == 0 || input == 1) 
    {
        action = input;
        turnStage = 1;
    }
}


void Game::pickShip(const int& input) 
{
    if (input >= 0 && input < players[currentPlayer]->getShips().size()) 
    {
        ship = players[currentPlayer]->getShips()[input];
        turnStage = 2;
    }
}


void Game::pickDestination(const int& input, const int& maxBoardSize) 
{
    int x = input/100; int y = input%100;
    if (x >= 1 && x <= maxBoardSize && y >= 1 && y <= maxBoardSize)
    {
        destination = board->findField(Coords(x, y));
        switch (action) 
        {
            case 0: turnStage = 4; break;
            case 1: turnStage = 3; break;
        }
    }
}


void Game::pickMissile(const int& input) 
{
    if (ship->hasMissile(input)) 
    {
        missileID = input;
        turnStage = 4;
    }
}


void Game::confirm(const int& input, bool& correctMoveFlag) 
{
    if (input == 1) 
    {
        switch (action) 
        {
            case 0: correctMoveFlag = players[currentPlayer]->move(ship, destination); break;
            case 1: correctMoveFlag = players[currentPlayer]->fire(ship, destination, missileID); checkIfShipSunked();  break;
        }
        turnStage = 0;
        if (correctMoveFlag) newTurn();
        else std::cout << langOptions->getCommunicate("game_incorrect_action") << std::endl;
    }
    else if (input==0) turnStage = 0;
}


void Game::checkIfShipSunked() 
{
    for (std::shared_ptr<Player> player : players) 
    {   
        std::vector<std::shared_ptr<Ship>> ships = player->getShips();
        for (std::shared_ptr<Ship> ship : ships) 
        {
            if (!ship->isAlive()) 
            {
                player->forgetShip(ship);
                board->removeShip(ship, ship->getCoords());
            }
        }
    }
}

void Game::newTurn() 
{
    for (int i = 0; i < players.size(); i++) 
    {
        if (players[i]->getShips().size() == 0) 
        {
            if (i == players.size()-1) setWinner(players[0]);
            else setWinner(players[i+1]);
            #ifdef _WIN32
            // Windows
                Sleep(milliseconds);
                std::system("cls");
             #else
            // Unix-like system
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::system ("clear");
            #endif
            this->getBoard()->boardDisplay();
            std::cout << langOptions->getCommunicate("game_winner") << getWinner()->getName() << std::endl;
            setIsOn(false);
        }
    }
    if (currentPlayer == players.size()-1) setCurrentPlayerIndex(0);
    else setCurrentPlayerIndex(currentPlayer + 1);
}


void Game::generateBoard(const int& maxBoardSize) 
{
    board = std::make_shared<Board>(maxBoardSize);
    for (std::shared_ptr<Player> player : players) 
    {
        for (std::shared_ptr<Ship> ship : player->getShips()) 
        {
            board->putShip(ship);
        }
    }
    for (std::shared_ptr<Island> islandPtr : islands)
    {
        board->putIsland(islandPtr);
    }   
}


void Game::displayInfo() 
{
    std::vector<CruiseMissile> allMissilies;
    for (std::shared_ptr<Player> player : players) 
    {
        for(CruiseMissile missile : player->getAllMissilies())
        {
            auto it = std::find(allMissilies.begin(), allMissilies.end(), missile);
            if (it == allMissilies.end()) allMissilies.push_back(missile);
        }
    }
    std::cout << langOptions->getCommunicate("game_missiles") << std::endl;
    for (CruiseMissile missile : allMissilies)
    {
        std::cout << langOptions->getCommunicate("game_missile_id") << missile.getMissileID() << langOptions->getCommunicate("game_damage") 
        << missile.getDamage() << langOptions->getCommunicate("game_range") << missile.getRange() << langOptions->getCommunicate("game_altitude") 
        << missile.getAltitude()<< std::endl;
    }
    std::cout << "\n" << langOptions->getCommunicate("game_your_ships") << std::endl;
    getPlayers()[getCurrentPlayerIndex()]->shipsInfo();
    std::cout << "\n" << langOptions->getCommunicate("game_opponent's_ships") << std::endl;
    getPlayers()[(getCurrentPlayerIndex() + 1) % 2]->shipsInfo();
    std::cout << "\n" << langOptions->getCommunicate("game_player's_ships") << getPlayers()[getCurrentPlayerIndex()]->getName() 
    << langOptions->getCommunicate("game_turn") << std::endl;
}
