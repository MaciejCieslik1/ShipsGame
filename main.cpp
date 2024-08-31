﻿#include <iostream>
#include <utility>
#include <thread>
#include <cstdlib>
#include "Ships/LanguageManager.h"
#include "Ships/Menu.h"
#include "Ships/Process.h"

int main()
{
    try {
    std::shared_ptr<LanguageManager> language = std::make_shared<LanguageManager>("languages/en.txt");
    language->loadCommunicates();
    Process::clearScreen();
    std::cout << language->getCommunicate("program_name_start") <<'\n';
    Process::sleep(1000);

    Menu menu(language);
    Process process(language);

    std::vector<std::string> playerNames;
    int maxBoardSize;
    std::pair<bool, bool> gameOpts = menu.generateMenu(playerNames, maxBoardSize);
    std::cout << maxBoardSize << std::endl;
    if (gameOpts.first && !gameOpts.second) {
        process.initializeNewGame(playerNames, maxBoardSize);
    }
    else if (gameOpts.first && gameOpts.second) {
        process.loadGameState();
    }
    process.startGame(maxBoardSize);
    }

    catch (const std::exception& e) {
        std::cerr << "An error occured: " << e.what() << '\n';
        return -1;
    }

    return 0;
}
