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


bool Process::loadGameState(int& maxBoardSize)
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
    int currentPlayerIndex;
    bool newPart;
    std::vector<std::string> words;
    std::vector<std::shared_ptr<Island>> islands;
    std::vector<std::shared_ptr<Ship>> ships1;
    std::vector<std::shared_ptr<Ship>> ships2;
    std::string player1name;
    std::string player2name;

    if (std::getline(file, line))
    {
        words = splitLine(line);
        if (words[0] == "Game" && words.size() == 3)
        {
            try
            {
                maxBoardSize = std::stoi(words[1]);
                currentPlayerIndex = std::stoi(words[2]);
            } 
            catch (const std::invalid_argument& e) 
            {
                throw file_failed_string_to_int_convertion("Failed to convert string to int while loading data from the file");
            }
        }
        else throw invalid_file_format("Invalid structure of data in game state file");
    }
    else return throwExceptionAndReturn();
    if (std::getline(file, line) && line == "Islands;") newPart = false;
    else return throwExceptionAndReturn();
    while (!newPart)
    {
        if(std::getline(file, line))
        {
            words = splitLine(line);
            if (words.size() == 1) 
                {
                    if (words[0] == "Ships1") newPart = true;
                    else return throwExceptionAndReturn();
                }
            else 
            {   
                try
                {
                    if (words.size() == std::stoi(words[1]) * 2 + 2)
                    {
                        int height = std::stoi(words[0]);
                        int coordsNumber = std::stoi(words[1]);
                        std::vector<Coords> coords;
                        for (int i=2; i<coordsNumber*2+1; i=i+2)
                        {
                            Coords coord = Coords(std::stoi(words[i]), std::stoi(words[i+1]));
                            coords.push_back(coord);
                        }
                        std::shared_ptr<Island> island = std::make_shared<Island>(coords, height, maxBoardSize);
                        islands.push_back(island);
                    }
                    else throw invalid_file_format("Invalid structure of data in game state file");
                } 
                catch (const std::invalid_argument& e) 
                {
                    throw file_failed_string_to_int_convertion("Failed to convert string to int while loading data from the file");
                }
                
            }
        }
        else return throwExceptionAndReturn();
    }
    if (words[0] == "Ships1" && words.size() == 1) newPart = false;
    else return throwExceptionAndReturn();
    while (!newPart)
    {
        if(std::getline(file, line))
        {
            words = splitLine(line);
            if (words[0] == "Player1") newPart = true;
            else 
            {   
                loadShip(words, ships1, maxBoardSize);
            }
        }
        else return throwExceptionAndReturn();
    }
    if (std::getline(file, line)) newPart = false;
    else return throwExceptionAndReturn();
    if (words[0] == "Player1" && words.size() == 2 && line == "Ships2;") player1name = words[1];
    else return throwExceptionAndReturn();
    while (!newPart)
    {
        if(std::getline(file, line))
        {
            words = splitLine(line);
            if (words[0] == "Player2") newPart = true;
            else 
            {   
                loadShip(words, ships2, maxBoardSize);
            }
        }
        else return throwExceptionAndReturn();
    }
    if (words[0] == "Player2" && words.size() == 2) player2name = words[1];
    else return throwExceptionAndReturn();
    file.close();
    std::shared_ptr<Player> player1 = std::make_shared<Player>(player1name, ships1, langOptions);
    std::shared_ptr<Player> player2 = std::make_shared<Player>(player2name, ships2, langOptions);
    std::vector<std::shared_ptr<Player>> players = {player1, player2};
    game = std::make_unique<Game>(players, islands, maxBoardSize, langOptions);
    finishGamePreparation();
    game->setCurrentPlayerIndex(currentPlayerIndex);
    return true;
}


bool Process::throwExceptionAndReturn()
{
    throw invalid_file_format("Invalid structure of data in game state file");
    return false;
}


void Process::loadShip(const std::vector<std::string>& words, std::vector<std::shared_ptr<Ship>>& ships, const int& maxBoardSize)
{
    try
    {
        if (words.size() == std::stoi(words[2]) * 2 + 3)
        {
            std::string shipType = words[0];
            char name = words[1][0];
            int coordsNumber = std::stoi(words[2]);
            std::vector<Coords> coords;
            for (int i=3; i<=coordsNumber*2+1; i=i+2)
            {
                Coords coord = Coords(std::stoi(words[i]), std::stoi(words[i+1]));
                coords.push_back(coord);
            }
            if (shipType == "Battleship")
            {
                std::shared_ptr<Battleship> ship = std::make_shared<Battleship>(name, coords, maxBoardSize);
                ships.push_back(ship);
            }
            else if (shipType == "Cruiser") 
            {
                std::shared_ptr<Cruiser> ship = std::make_shared<Cruiser>(name, coords, maxBoardSize);
                ships.push_back(ship);
            }
            else if (shipType == "Destroyer")
            {
                std::shared_ptr<Destroyer> ship = std::make_shared<Destroyer>(name, coords, maxBoardSize);
                ships.push_back(ship);
            }
            else if (shipType == "Submarine")
            {
                std::shared_ptr<Submarine> ship = std::make_shared<Submarine>(name, coords, maxBoardSize);
                ships.push_back(ship);
            }
            else throw invalid_file_format("Invalid structure of data in game state file");
        }
        else 
        {   
            throw invalid_file_format("Invalid structure of data in game state file");
        }
    } 
    catch (const std::invalid_argument& e) 
    {
       throw file_failed_string_to_int_convertion("Failed to convert string to int while loading data from the file");
    }
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
    finishGamePreparation();
}


void Process::finishGamePreparation()
{
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
