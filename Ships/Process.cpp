#include "Process.h"
#ifdef _WIN32
    #include <windows.h>
#endif

Process::Process(std::shared_ptr<LanguageManager> language)
	: langOptions(language) , game(std::make_unique<Game>()) { }

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
    std::vector<Ship*> shipVec;
    std::vector<Player*> playerVec;

    // Add ships
    for (auto& ship : player1ShipContainer) {
        Ship* shipPtr = ship.get();
        shipVec.push_back(shipPtr);
    }
    playerContainer[0]->setShips(shipVec);
    shipVec.clear();

    for (auto& ship : player2ShipContainer) {
        Ship* shipPtr = ship.get();
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

    game = std::make_unique<Game>(playerVec);
    game->turnGameOn();
    game->generateBoard();

    playerVec[0]->setBoard(game->getBoard());
    playerVec[1]->setBoard(game->getBoard());
}

void Process::initializeNewGame(std::vector<std::string>& playerNames)
{
	if (playerNames.size() < 2) {
        throw std::invalid_argument(langOptions->getCommunicate("process_invalid_player_number"));
    }

    Board* board = nullptr;

    std::vector<Ship*> shipsPlayer1;
    shipsPlayer1.push_back(new Ship(20, 5, {Coords(1, 3), Coords(2, 3)}));
    shipsPlayer1.push_back(new Ship(20, 5, {Coords(1, 1), Coords(2, 1), Coords(3, 1)}));
    std::vector<CruiseMissile> missilesPlayer1 = {CruiseMissile(2, 3, 0), CruiseMissile(6, 2, 1)};
    player_1 = std::make_unique<Player>(playerNames[0], shipsPlayer1, 3, missilesPlayer1);

    std::vector<Ship*> shipsPlayer2;
    shipsPlayer2.push_back(new Ship(20, 5, {Coords(5, 5), Coords(6, 5)}));
    shipsPlayer2.push_back(new Ship(20, 5, {Coords(5, 7), Coords(6, 7), Coords(7, 7)}));
    std::vector<CruiseMissile> missilesPlayer2 = {CruiseMissile(2, 3, 0), CruiseMissile(6, 2, 1)};
    player_2 = std::make_unique<Player>(playerNames[1], shipsPlayer2, 3, missilesPlayer2);

    std::vector<Player*> players = {player_1.get(), player_2.get()};

    game = std::make_unique<Game>(players);

    game->turnGameOn();
    game->generateBoard();


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

void Process::startGame(void)
{
	int input;
    while (game->getIsOn()) {
        game->getBoard()->boardDisplay();
        std::cout << langOptions->getCommunicate("process_player_turn_first_half") << game->getCurrentPlayerIndex() + 1 << langOptions->getCommunicate("process_player_turn_second_half") << '\n';

        if (game->getTurnStage() == 0) {
            std::cout << langOptions->getCommunicate("process_player_enter_action_shoot_move");
            std::cin >> input; input -= 1;
        } else if (game->getTurnStage() == 1) {
            std::cout << "I have soiled myself. How embarassing. Choose ship to do stuff with";
            std::cin >> input;
        } else if (game->getTurnStage() == 2) {
            int x; int y;
            std::cout << langOptions->getCommunicate("process_choose_destination");
            std:: cin >> x >> y;
            input = x*100 + y;
        } else if (game->getTurnStage() == 3) {
            std::cout << langOptions->getCommunicate("process_choose_missle_id");
            std::cin >> input;
        } else {
            std::cout << "Press 1 to confirm\n";
            std::cin >> input;
        }
        game->mainGameProcess(input);
    }
    std::cout << "end" << std::endl;
}
