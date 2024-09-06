#include "Process.h"
#ifdef _WIN32
    #include <windows.h>
#endif


Process::Process(std::shared_ptr<LanguageManager> language) 
    : langOptions(language) {}


void Process::clearScreen(void)
{
    #ifdef WINDOWS
    std::system("cls");
    #else
    std::system ("clear");
    #endif
}


void Process::sleep(unsigned int milliseconds) 
{
    #ifdef _WIN32
        // Windows
        Sleep(milliseconds);
    #else
        // Unix-like system
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    #endif
}


void Process::initializeNewGame(std::vector<std::string>& playerNames, const int& maxBoardSize)
{
	if (playerNames.size() < 2) throw std::invalid_argument(langOptions->getCommunicate("process_invalid_player_number"));

    std::vector<std::shared_ptr<Ship>> shipsPlayer1;
    shipsPlayer1.push_back(std::make_shared<Destroyer>('A', std::vector<Coords>({Coords(6, 6), Coords(7, 6)}), maxBoardSize));
    shipsPlayer1.push_back(std::make_shared<Cruiser>('B', std::vector<Coords>({Coords(5, 3), Coords(6, 3), Coords(7, 3)}), maxBoardSize));
    std::shared_ptr<Player> player_1 = std::make_shared<Player>(playerNames[0], shipsPlayer1, langOptions);

    std::vector<std::shared_ptr<Ship>> shipsPlayer2;
    shipsPlayer2.push_back(std::make_shared<Destroyer>('a', std::vector<Coords>({Coords(3, 6), Coords(4, 6)}), maxBoardSize));
    shipsPlayer2.push_back(std::make_shared<Cruiser>('b', std::vector<Coords>({Coords(5, 8), Coords(6, 8), Coords(7, 8)}), maxBoardSize));
    std::shared_ptr<Player> player_2 = std::make_shared<Player>(playerNames[1], shipsPlayer2, langOptions);

    std::vector<std::shared_ptr<Player>> players = {player_1, player_2};

    game = std::make_unique<Game>(players, maxBoardSize, langOptions);

    game->turnGameOn();
    game->generateBoard(maxBoardSize);


    game->getPlayers()[0]->setBoard(game->getBoard());
    game->getPlayers()[1]->setBoard(game->getBoard());
}


void Process::startGame(const int& maxBoardSize)
{
	int input;
    bool correctMoveFlag = true;
    while (game->getIsOn()) 
    {
        clearScreen();
        game->getBoard()->boardDisplay();
        game->displayInfo();
        if (game->getTurnStage() == 0) 
        {
            if (!correctMoveFlag) std::cout << langOptions->getCommunicate("process_invalid_action") << std::endl;
            std::cout << langOptions->getCommunicate("process_player_enter_action_shoot_move");
            std::cin >> input; input -= 1;
        } 
        else if (game->getTurnStage() == 1) 
        {
            std::cout << langOptions->getCommunicate("process_choose_ship");
            std::cin >> input;
        } 
        else if (game->getTurnStage() == 2) 
        {
            int x; int y;
            std::cout << langOptions->getCommunicate("process_choose_destination");
            std:: cin >> x >> y;
            input = x*100 + y;
        } 
        else if (game->getTurnStage() == 3) 
        {
            std::cout << langOptions->getCommunicate("process_choose_missle_id");
            std::cin >> input;
        } 
        else 
        {
            std::cout << langOptions->getCommunicate("process_press_1");
            std::cin >> input;
        }
        game->mainGameProcess(input, maxBoardSize, correctMoveFlag);
    }
    std::cout << langOptions->getCommunicate("process_congratulations") << std::endl;
}
