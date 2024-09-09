#include "Game.h"


Game::Game(std::shared_ptr<LanguageManager> language) : langOptions(language)
{
    std::vector<std::shared_ptr<Player>> newPlayers;
    players = newPlayers;
    currentPlayer = 0;
    numberOfTurns = 1;
    winner = nullptr;
    int maxBoardSize = 10;
    turnGameOn();
    generateBoard(maxBoardSize);
}


Game::Game(const std::vector<std::shared_ptr<Player>>& newPlayers, const std::shared_ptr<Island>& island, const int& maxBoardSize, std::shared_ptr<LanguageManager> language) 
    : langOptions(language), players(newPlayers), island(island)
{
    currentPlayer = 0;
    numberOfTurns = 1;
    winner = nullptr;
    turnGameOn();
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


std::shared_ptr<Island> Game::getIsland() const
{
    return island;
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


void Game::setBoard(std::shared_ptr<Board> new_board) 
{
    board = new_board;
}


void Game::setPlayers(const std::vector<std::shared_ptr<Player>>& new_players) 
{
    players = new_players;
}


void Game::setIsland(const std::shared_ptr<Island>& newIsland)
{
    island = newIsland;
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


void Game::turnGameOn() 
{
    isOn = true;
}


void Game::turnGameOff() 
{
    isOn = false;
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
        missile = input;
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
            case 1: correctMoveFlag = players[currentPlayer]->fire(ship, destination, missile); checkIfShipSunked();  break;
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
            turnGameOff();
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
            board->putShip(ship, ship->getCoords());
        }
    }
    board->putIsland(island);
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
        << missile.getDamage() << langOptions->getCommunicate("game_range") << missile.getRange() << std::endl;
    }
    std::cout << "\n" << langOptions->getCommunicate("game_your_ships") << std::endl;
    getPlayers()[getCurrentPlayerIndex()]->shipsInfo();
    std::cout << "\n" << langOptions->getCommunicate("game_opponent's_ships") << std::endl;
    getPlayers()[(getCurrentPlayerIndex() + 1) % 2]->shipsInfo();
    std::cout << "\n" << langOptions->getCommunicate("game_player's_ships") << getPlayers()[getCurrentPlayerIndex()]->getName() 
    << langOptions->getCommunicate("game_turn") << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Game& game)
{
    os << game.currentPlayer << ' ' << game.numberOfTurns  << ' ' << game.turnStage  << ' ' <<
    game.isOn  << ' ' << game.action  << ' ' << game.destination  << ' ' << game.missile  << '\n';

    return os;
}


std::istream& operator>>(std::istream& is, Game& game)\
{
    int currentPlayer, numberOfTurns, turnStage, action, missle;
    bool isOn;
    Field destination;

    if (is >> currentPlayer >> numberOfTurns >> turnStage >> isOn >> action >> destination >> missle)
    {
        game.currentPlayer = currentPlayer;
        game.numberOfTurns = numberOfTurns;
        game.turnStage = turnStage;
        game.isOn = isOn;
        game.action = action;
        game.destination = destination;
        game.missile = missle;
    }
    else is.setstate(std::ios::failbit);

    return is;
}
