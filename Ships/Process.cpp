#include "Process.h"
#ifdef _WIN32
    #include <windows.h>
#endif

Process::Process(std::shared_ptr<LanguageManager> language) 
    : langOptions(language) { }


Process::~Process() {}


void Process::clearScreen(void)
{
    #ifdef WINDOWS
    std::system("cls");
    #else
    std::system ("clear");
    #endif
}

void Process::sleep(unsigned int milliseconds) {
    #ifdef _WIN32
        // Windows
        Sleep(milliseconds);
    #else
        // Unix-like system
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    #endif
}

void Process::loadGameState(void)
{
	FileHandler handler("saved/players.txt");
	std::vector<std::unique_ptr<Player>> playerContainer = handler.loadPlayerInfo();
    handler.setFilename("saved/player_1_ships.txt");
	std::vector<std::unique_ptr<Ship>> player1ShipContainer = handler.loadShipInfo();
	handler.setFilename("saved/player_2_ships.txt");
	std::vector<std::unique_ptr<Ship>> player2ShipContainer = handler.loadShipInfo();
    handler.setFilename("saved/player_1_missiles.txt");
	std::vector<std::unique_ptr<CruiseMissile>> player1missleContainer = handler.loadMissileInfo();
	handler.setFilename("saved/player_2_missiles.txt");
	std::vector<std::unique_ptr<CruiseMissile>> player2missleContainer = handler.loadMissileInfo();
    // 5 Containers;

    std::vector<CruiseMissile> missleVec;
    std::vector<std::shared_ptr<Ship>> shipVec;
    std::vector<std::shared_ptr<Player>> playerVec;

    // Add ships
    for (auto& ship : player1ShipContainer) {
        std::shared_ptr<Ship> shipPtr = std::make_shared<Ship>();
        shipVec.push_back(shipPtr);
    }
    playerContainer[0]->setShips(shipVec);
    shipVec.clear();

    for (auto& ship : player2ShipContainer) {
        std::shared_ptr<Ship> shipPtr = std::make_shared<Ship>();
        shipVec.push_back(shipPtr);
    }

    playerContainer[1]->setShips(shipVec);

    // Add missiles
    for (const auto& mis : player1missleContainer) {
        missleVec.push_back(*mis);
    }
    playerContainer[0]->setAllMissiles(missleVec);
    missleVec.clear();
    for (const auto& mis : player2missleContainer) {
        missleVec.push_back(*mis);
    }
    playerContainer[1]->setAllMissiles(missleVec);
    int maxBoardSize = 10;
    game = std::make_unique<Game>(playerVec, maxBoardSize);
    game->turnGameOn();
    
    game->generateBoard(maxBoardSize);

    playerVec[0]->setBoard(game->getBoard());
    playerVec[1]->setBoard(game->getBoard());
}

void Process::initializeNewGame(std::vector<std::string>& playerNames, const int& maxBoardSize)
{
	if (playerNames.size() < 2) {
        throw std::invalid_argument(langOptions->getCommunicate("process_invalid_player_number"));
    }

    std::unique_ptr<Board> board = nullptr;

    std::vector<std::shared_ptr<Ship>> shipsPlayer1;
    std::vector<Coords> ship1Coords = {Coords(6, 6), Coords(7, 6)};
    std::vector<Coords> ship2Coords = {Coords(5, 3), Coords(6, 3), Coords(7, 3)};
    shipsPlayer1.push_back(std::make_shared<Ship>(20, 5, 'A', ship1Coords));
    shipsPlayer1.push_back(std::make_shared<Ship>(20, 5, 'B', ship2Coords));
    std::vector<CruiseMissile> missilesPlayer1 = {CruiseMissile(2, 3, 0), CruiseMissile(6, 2, 1)};
    std::shared_ptr<Player> player_1 = std::make_shared<Player>(playerNames[0], shipsPlayer1, 3, missilesPlayer1);

    std::vector<std::shared_ptr<Ship>> shipsPlayer2;
    std::vector<Coords> ship3Coords = {Coords(3, 6), Coords(4, 6)};
    std::vector<Coords> ship4Coords = {Coords(5, 8), Coords(6, 8), Coords(7, 8)};
    shipsPlayer2.push_back(std::make_shared<Ship>(20, 5, 'a', ship3Coords));
    shipsPlayer2.push_back(std::make_shared<Ship>(20, 5, 'b', ship4Coords));
    std::vector<CruiseMissile> missilesPlayer2 = {CruiseMissile(2, 3, 0), CruiseMissile(6, 2, 1)};
    std::shared_ptr<Player> player_2 = std::make_shared<Player>(playerNames[1], shipsPlayer2, 3, missilesPlayer2);

    std::vector<std::shared_ptr<Player>> players = {player_1, player_2};

    game = std::make_unique<Game>(players, maxBoardSize);

    game->turnGameOn();
    game->generateBoard(maxBoardSize);


    game->getPlayers()[0]->setBoard(game->getBoard());
    game->getPlayers()[1]->setBoard(game->getBoard());
}

void Process::saveGameState(void)
{
    std::vector<std::unique_ptr<Player>> playerContainer;
    std::vector<std::unique_ptr<Ship>> shipContainer;
    std::vector<std::unique_ptr<CruiseMissile>> missleContainer;
    FileHandler handler;

    size_t num = 0;
    std::string filenameSave;
    for (auto& player : this->game->getPlayers()) {
        playerContainer.emplace_back(std::make_unique<Player>(*player));
        ++num;

        shipContainer.clear();
        for (auto& ship : player->getShips()) {
            shipContainer.emplace_back(std::make_unique<Ship>(*ship));
        }

        filenameSave = "saved/player_" + std::to_string(num) + "_ships.txt";
        handler.setFilename(filenameSave);
        handler.saveInfo<Ship>(shipContainer);

        missleContainer.clear();
        for (auto& missle : player->getAllMissilies()) {
            missleContainer.emplace_back(std::make_unique<CruiseMissile>(missle));
        }
        filenameSave = "saved/player_" + std::to_string(num) + "_missiles.txt";
        handler.setFilename(filenameSave);
        handler.saveInfo<CruiseMissile>(missleContainer);

        filenameSave = "saved/players.txt";
        handler.setFilename(filenameSave);
        handler.saveInfo<Player>(playerContainer);
    }
}

void Process::startGame(const int& maxBoardSize)
{
	int input;
    bool correctMoveFlag = true;
    while (game->getIsOn()) {
        clearScreen();
        game->getBoard()->boardDisplay();
        game->displayInfo();
        if (game->getTurnStage() == 0) {
            if (!correctMoveFlag) std::cout << "Invalid action!" << std::endl;
            std::cout << "Enter action (1: Move, 2: Fire): ";
            std::cin >> input; input -= 1;
        } else if (game->getTurnStage() == 1) {
            std::cout << "Choose ship: ";
            std::cin >> input;
        } else if (game->getTurnStage() == 2) {
            int x; int y;
            std::cout << "Choose destination (x, y): ";
            std:: cin >> x >> y;
            input = x*100 + y;
        } else if (game->getTurnStage() == 3) {
            std::cout << "Choose missile ID: ";
            std::cin >> input;
        } else {
            std::cout << "Press 1 to confirm or 0 to cancel: ";
            std::cin >> input;
        }
        game->mainGameProcess(input, maxBoardSize, correctMoveFlag);
    }
    std::cout << "End" << std::endl;
}
