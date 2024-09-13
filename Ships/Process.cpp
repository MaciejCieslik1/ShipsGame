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


bool Process::loadGameState()
{
    std::string fileName;
    std::cout << langOptions->getCommunicate("process_load_game");
    std::cin >> fileName;
    std::string filePath = "saved/" + fileName;
    std::ifstream file(filePath);
    if (!file) 
    {
        std::cerr << langOptions->getCommunicate("process_file_error") << std::endl;
        return false;
    }
    std::string line;
    if (std::getline(file, line))
    {
        std::vector<std::string> words = splitLine(line);
    }
    file.close();
    return true;
}


void Process::initializeNewGame(std::vector<std::string>& playerNames, const int& maxBoardSize)
{
	if (playerNames.size() < 2) throw std::invalid_argument(langOptions->getCommunicate("process_invalid_player_number"));

    std::vector<std::shared_ptr<Ship>> shipsPlayer1;
    shipsPlayer1.push_back(std::make_shared<Destroyer>('A', std::vector<Coords>({Coords(9, 11), Coords(10, 11)}), maxBoardSize));
    shipsPlayer1.push_back(std::make_shared<Cruiser>('B', std::vector<Coords>({Coords(4, 4), Coords(5, 4), Coords(6, 4)}), maxBoardSize));
    std::shared_ptr<Player> player_1 = std::make_shared<Player>(playerNames[0], shipsPlayer1, langOptions);

    std::vector<std::shared_ptr<Ship>> shipsPlayer2;
    shipsPlayer2.push_back(std::make_shared<Destroyer>('a', std::vector<Coords>({Coords(2, 6), Coords(3, 6)}), maxBoardSize));
    shipsPlayer2.push_back(std::make_shared<Cruiser>('b', std::vector<Coords>({Coords(5, 6), Coords(6, 6), Coords(7, 6)}), maxBoardSize));
    std::shared_ptr<Player> player_2 = std::make_shared<Player>(playerNames[1], shipsPlayer2, langOptions);

    std::vector<std::shared_ptr<Player>> players = {player_1, player_2};

    std::shared_ptr<Island> island2 = std::make_shared<Island>(std::vector<Coords>({Coords(5, 5), Coords(6, 5), Coords(10, 5)}), 3, maxBoardSize);
    std::shared_ptr<Island> island1 = std::make_shared<Island>(std::vector<Coords>({Coords(3, 7), Coords(3, 8), Coords(3, 9)}), 2, maxBoardSize); 
    std::shared_ptr<Island> island0 = std::make_shared<Island>(std::vector<Coords>({Coords(2, 7), Coords(2, 8), Coords(4, 11), Coords(5, 11)}), 0, maxBoardSize);  
    std::vector<std::shared_ptr<Island>> islands = {island0, island1, island2};

    game = std::make_unique<Game>(players, islands, maxBoardSize, langOptions);

    game->turnGameOn();

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
