#include "Game.h"

Game::Game() {
    std::vector<Player*> newPlayers;
    players = newPlayers;
    currentPlayer = 0;
    numberOfTurns = 1;
    winner = nullptr;
    int maxBoardSize = 10;
    turnGameOn();
    generateBoard(maxBoardSize);
}
Game::Game(const std::vector<Player*>& newPlayers, const int& maxBoardSize) {
    players = newPlayers;
    currentPlayer = 0;
    numberOfTurns = 1;
    winner = nullptr;
    turnGameOn();
    generateBoard(maxBoardSize);
}
Game::~Game() {
    for (Player* player : players) { delete player; }
    delete board;
}

Board* Game::getBoard() const {
    return board;
}
const std::vector<Player*>& Game::getPlayers() const {
    return players;
}
int	Game::getCurrentPlayerIndex() const {
    return currentPlayer;
}
int Game::getNumberOfTurns() const {
    return numberOfTurns;
}
Player* Game::getWinner() const {
    return winner;
}
int Game::getTurnStage() const {
    return turnStage;
}
bool Game::getIsOn() const {
    return isOn;
}

void Game::setBoard(Board* new_board) {
    board = new_board;
}
void Game::setPlayers(const std::vector<Player*>& new_players) {
    players = new_players;
}
void Game::setCurrentPlayerIndex(const int& new_player) {
    if (new_player >= players.size() || new_player < 0) {
        throw std::invalid_argument("Player index must be in range [0, <number of players>)");
    } else currentPlayer = new_player;
}
void Game::setNumberOfTurns(const int& new_number_of_turns) {
    numberOfTurns = new_number_of_turns;
}
void Game::setWinner(Player* new_winner) {
    for (Player* player : players) {
        if (player == new_winner) {
            winner = new_winner; return;
        }
    } throw std::invalid_argument("New winner must be one of the active players");
}
void Game::setTurnStage(const int& newStage) {
    turnStage = newStage;
}

void Game::turnGameOn() {
    isOn = true;
}
void Game::turnGameOff() {
    isOn = false;
}

void Game::mainGameProcess(const int& input, const int& maxBoardSize, bool& correctMoveFlag) {
    switch (turnStage) {
        case 0: pickAction(input); break;
        case 1: pickShip(input); break;
        case 2: pickDestination(input, maxBoardSize); break;
        case 3: pickMissile(input); break;
        case 4: confirm(input, correctMoveFlag); break;
    }
}

void Game::pickAction(const int& input) {
    if (input == 0 || input == 1) {
        action = input;
        turnStage = 1;
    }
}
void Game::pickShip(const int& input) {
    if (input >= 0 && input < players[currentPlayer]->getShips().size()) {
        ship = players[currentPlayer]->getShips()[input];
        turnStage = 2;
    }
}
void Game::pickDestination(const int& input, const int& maxBoardSize) {
    int x = input/100; int y = input%100;
    if (x >= 1 && x <= maxBoardSize && y >= 1 && y <= maxBoardSize) {
        destination = board->findField(Coords(x, y));
        switch (action) {
            case 0: turnStage = 4; break;
            case 1: turnStage = 3; break;
        }
    }
}
void Game::pickMissile(const int& input) {
    if (ship->hasMissile(input)) {
        missile = input;
        turnStage = 4;
    }
}
void Game::confirm(const int& input, bool& correctMoveFlag) {
    if (input == 1) {
        switch (action) {
            case 0: correctMoveFlag = players[currentPlayer]->move(ship, destination); break;
            case 1: correctMoveFlag = players[currentPlayer]->fire(ship, destination, missile); checkIfShipSunked();  break;
        }
        turnStage = 0;
        if (correctMoveFlag) newTurn();
        else std::cout << "Incorrect action!" << std::endl;
    }
    else if (input==0) turnStage = 0;
}

void Game::checkIfShipSunked() {
    for (Player* player : players) {   
        std::vector<Ship*> ships = player->getShips();
        for (Ship* ship : ships) {
            if (!ship->isAlive()) {
                player->forgetShip(ship);
                board->removeShip(ship, ship->getCoords());
            }
        }
    }
}

void Game::newTurn() {
    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getShips().size() == 0) {
            if (i == players.size()-1) {
                setWinner(players[0]);
            } else setWinner(players[i+1]);
            #ifdef _WIN32
            // Windows
                Sleep(milliseconds);
                std::system("cls");
             #else
            // Unix-like system
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::system ("clear");
            #endif
            std::cout << "Winner: " << getWinner()->getName() << std::endl;
            turnGameOff();
        }
    }
    if (currentPlayer == players.size()-1) {
        setCurrentPlayerIndex(0);
    } else setCurrentPlayerIndex(currentPlayer + 1);
}

void Game::generateBoard(const int& maxBoardSize) {
    board = new Board(maxBoardSize);
    for (Player* player : players) {
        for (Ship* ship : player->getShips()) {
            board->putShip(ship, ship->getCoords());
        }
    }
}


void Game::displayInfo() {
    std::vector<CruiseMissile> allMissilies;
    for (Player* player : players) 
    {
        for(CruiseMissile missile : player->getAllMissilies())
        {
            auto it = std::find(allMissilies.begin(), allMissilies.end(), missile);
            if (it == allMissilies.end()) 
            {
                allMissilies.push_back(missile);
            }
        }
    }
    std::cout << "Missiles: " << std::endl;
    for (CruiseMissile missile : allMissilies)
    {
        std::cout << "Missile ID: " << missile.getMissileID() << ", damage: " << missile.getDamage() << ", range: " << missile.getRange() << std::endl;
    }
    std::cout << "\nYour's ships: " << std::endl;
    getPlayers()[getCurrentPlayerIndex()]->shipsInfo();
    std::cout << "Opponent's ships: " << std::endl;
    getPlayers()[(getCurrentPlayerIndex() + 1) % 2]->shipsInfo();
    std::cout << "\nPlayer's " << getPlayers()[getCurrentPlayerIndex()]->getName() << " turn" << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Game& game)
{
    // int	currentPlayer;
	// int numberOfTurns;
	// Player* winner;
	// int turnStage;
	// bool isOn;

	// int action; Ship* ship; Field destination; int missile;
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
