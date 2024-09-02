#include "Menu.h"
#include "ShipsExceptions.h"

Menu::Menu(std::shared_ptr<LanguageManager> langOptions) :
	langOptions(langOptions){

	currentState = CurrentMenuState::MainMenu;
    this->generateCommunicationKeys();
}

void Menu::display(void) const
{
	switch (currentState) {
		case CurrentMenuState::MainMenu:
			for (int i = 0; i < 4; ++i) {
				std::cout << i +1 << ". ";
				std::cout << optionTable[i] << '\n';
			}
			break;
		case CurrentMenuState::StartMenu:
			for (int i = 0; i < 3; ++i) {
				std::cout << i + 1 << ". ";
				std::cout << optionTable[i + 4] << '\n';
			}
			break;
		case CurrentMenuState::ShowCredits:
            std::cout << langOptions->getCommunicate("menu_credits") << ":\n";
			for (int i = 0; i < 3; ++i) {
				std::cout << optionTable[i + 7] << '\n';
			}
			break;
		case CurrentMenuState::ShowOptions:
            std::cout << '\t' <<optionTable[1] << '\n';
            std::cout << langOptions->getCommunicate("menu_options_choose_language") << "\n";
            for (int i = 0; i < 10; ++i) {
                std::cout << i + 1 << ". ";
                std::cout << optionTable[i + 10] << '\n';
            }
            std::cout << "0. Go Back\n";
			break;
	}
}

void Menu::generateCommunicationKeys(void) {
    this->optionTable.clear();
    std::vector<std::string> communicateKeys = {
            "menu_start",
            "menu_options",
            "menu_credits",
            "menu_exit",
            "menu_new_game",
            "menu_load_game",
            "menu_go_back",
            "menu_credits_authors",
            "menu_credits_faculty_and_date",
            "menu_credits_project_info",
            "menu_language_english",
            "menu_language_spanish",
            "menu_language_german",
            "menu_language_polish",
            "menu_language_ukrainian",
            "menu_language_russian",
            "menu_language_french",
            "menu_language_japanese",
            "menu_language_korean",
            "menu_language_chinese",
        };
        for (const std::string& v : communicateKeys) {
            this->optionTable.push_back(langOptions->getCommunicate(v));
        }
}

Menu::CurrentMenuState Menu::getCurrentState(void) const
{
	return currentState;
}

void Menu::changeState(Menu::CurrentMenuState newState) {
	currentState = newState;
}

std::pair<std::string, std::string> Menu::createNameEntryBox() {
	std::string name1, name2;
	std::cout << langOptions->getCommunicate("menu_choose_player_one") << ' ';
	std::cin >> name1;
	Process::clearScreen();
	std::cout << langOptions->getCommunicate("menu_choose_player_two") << ' ';
	std::cin >> name2;

	if (name1 == name2) {
		name2 += "(0)";
	}

	Process::clearScreen();
	std::cout << langOptions->getCommunicate("menu_welcome")<< ' '<< name1 <<
        langOptions->getCommunicate("menu_and") << ' '<< name2 << '\n' <<
        langOptions->getCommunicate("menu_lets_start_the_game") << '\n';

    Process::sleep(2000);
    Process::clearScreen();
	return std::make_pair(name1, name2);
}


int Menu::getMaxBoardSize(void) const
{
    int maxBoardSize = 0;
    while (maxBoardSize < 10 || maxBoardSize > 30)
    {
        std::cout << "Enter board size from range [10, 30]: ";
        std::cin >> maxBoardSize;
    }
    Process::sleep(2000);
    Process::clearScreen();
    return maxBoardSize;
}


void Menu::handleStartSelection(int idx) {
    switch (idx) {
        case StartOptions::NewGame:
			this->changeState(CreateNewGame);
        break;
        case StartOptions::LoadGame:
			this->changeState(CreateGameFromFile);
        break;
        case StartOptions::GoBack:
			this->changeState(MainMenu);
        break;
    }
}

void Menu::handleMainSelection(int idx) {
    switch (idx) {
        case MenuOptions::Start:
            this->changeState(StartMenu);
            break;
		case MenuOptions::Options:
            this->changeState(ShowOptions);
            break;
        case MenuOptions::Credits:
            this->changeState(ShowCredits);
            break;
        case MenuOptions::exitOpt:
            exit(0);
            break;
    }
}

void Menu::handleOptionsSelection(int idx) {

}

void Menu::handleCreditsSelection(char quit) {
	if (quit == 'Q' || quit == 'q')
		this->changeState(MainMenu);
}

template <typename T>
T Menu::choiceInput(void) {
	T input;
    std::cout << langOptions->getCommunicate("menu_choice_input") << ' ';
    std::cin >> input;
	return input;
}

std::string Menu::determineLangFile(int input) const {
    enum language { english, spanish, german, polish, ukrainian, russian, french, japanese, chinese, korean};
    switch(input) {
        case english:
            return "languages/en.txt";
        case german:
            return "languages/de.txt";
        case spanish:
            return "languages/es.txt";
        case polish:
            return "languages/pl.txt";
        case french:
            return "languages/fr.txt";
        case ukrainian:
            return "languages/uk.txt";
        case russian:
            return "languages/ru.txt";
        case japanese:
            return "languages/jp.txt";
        case chinese:
            return "languages/zh.txt";
        case korean:
            return "languages/ko.txt";
        default:
            return "languages/unknown.txt";
    }
}

std::pair<bool, bool> Menu::generateMenu(std::vector<std::string>& playerNames, int& maxBoardSize) {
	bool createGame = false;
    bool createGameFromFile = false;

	bool decisionMade=false;
    while (!decisionMade) {
		this->currentState = CurrentMenuState::MainMenu;
		bool continueFlag = false;
        Process::clearScreen();

        this->display();

        int input = choiceInput<int>();
		if (!(0 <= input && input <= 4)) continue;

        switch (input) {
            case 1:
                this->handleMainSelection(Menu::Start);

                if (this->getCurrentState() == Menu::CurrentMenuState::StartMenu) {
					int startInputInt;
                    do {
                        Process::clearScreen();
                        this->display();
                        startInputInt = choiceInput<int>();
                    } while (startInputInt < 1 || startInputInt > 3);

					StartOptions startInput = static_cast<StartOptions>(startInputInt - 1);
                	this->handleStartSelection(startInput);

                    if (this->getCurrentState() == Menu::CurrentMenuState::CreateNewGame) {
						Process::clearScreen();
                        createGame = true;
                        createGameFromFile = false;

						std::pair<std::string, std::string> nameBox = this->createNameEntryBox();
                        maxBoardSize = this->getMaxBoardSize();
						playerNames.push_back(nameBox.first);
						playerNames.push_back(nameBox.second);

						decisionMade = true;
						break;
                    }

                    else if (this->getCurrentState() == Menu::CurrentMenuState::CreateGameFromFile) {
						Process::clearScreen();
                        createGame = true;
                        createGameFromFile = true;
						decisionMade = true;
						break;
                    }

					else if (this->getCurrentState() == Menu::CurrentMenuState::MainMenu) {
						continueFlag = true;
						break;
					}
                }
                break;
            case 2:
                this->handleMainSelection(Menu::Options);
				if (this->getCurrentState() == Menu::CurrentMenuState::ShowOptions) {
                    int optionInput;
                    do {
                        Process::clearScreen();
                        this->display();
                        optionInput = choiceInput<int>();
                    } while (optionInput < 0 || optionInput > 10);

                    if (optionInput == 0) { continueFlag = true; break; }

                    --optionInput;
                    std::string langFile = this->determineLangFile(optionInput);
                    langOptions->setFilename(langFile);
                    langOptions->loadCommunicates();
                    this->generateCommunicationKeys();
                    continueFlag = true;
                    break;
                }
                break;
            case 3:
                this->handleMainSelection(Menu::Credits);
                if (this->getCurrentState() == Menu::CurrentMenuState::ShowCredits) {

                char quit;
                do {
                        Process::clearScreen();
                        this->display();
                        std::cout << '\n' << langOptions->getCommunicate("menu_type_to_quit") << ' ';
                        std::cin >> quit;
                        this->handleCreditsSelection(quit);
                    } while (quit != 'Q' && quit != 'q');
                }
				continueFlag = true;
                break;
            case 4:
                this->handleMainSelection(Menu::exitOpt);
				break;
            default:
                std::cout << langOptions->getCommunicate("menu_try_again") <<'\n';
                break;
        }

		if (continueFlag) {Process::clearScreen(); continue;}
    }

	return std::make_pair(createGame, createGameFromFile);
}
