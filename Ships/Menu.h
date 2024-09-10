#pragma once
#include <utility>
#include "Process.h"

class Menu
{
	enum MenuOptions { Start, Options, Credits, exitOpt};
	enum StartOptions { NewGame, LoadGame, GoBack };
	enum CurrentMenuState { MainMenu, StartMenu, ShowCredits, ShowOptions, CreateNewGame, CreateGameFromFile};

	void generateCommunicationKeys(void);
	void display(void) const;
	CurrentMenuState getCurrentState(void) const;

	std::pair<std::string, std::string> createNameEntryBox(void);
	int getMaxBoardSize(void) const;
	void handleStartSelection(int idx);
	void handleMainSelection(int idx);
	void handleOptionsSelection(int idx);
	void handleCreditsSelection(char quit);

	template <typename T>
	T choiceInput(void);

	Menu& operator=(const Menu& other) = delete;

	std::shared_ptr<LanguageManager> langOptions;
	CurrentMenuState currentState;
	std::vector<std::string> optionTable;

	void changeState(CurrentMenuState newState);
	std::string determineLangFile(int input) const;

public:
	Menu(std::shared_ptr<LanguageManager> langOptions);
	std::pair<bool, bool> generateMenu(std::vector<std::string>& playerNames, int& maxBoardSize);
};
