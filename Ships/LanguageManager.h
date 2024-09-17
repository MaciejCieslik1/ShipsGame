#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "ShipsExceptions.h"

class LanguageManager {

	using languageHash = std::unordered_map<std::string, std::string>;
	languageHash container;
	std::string fileHandle;

	std::vector<std::string> splitString(const std::string& s, char delimiter);

public:

	LanguageManager(const std::string fileHandle);
	~LanguageManager() = default;

	void setFilename(const std::string& name);

	void loadCommunicates(void);
	std::string getCommunicate(const std::string& key) const;
	
};