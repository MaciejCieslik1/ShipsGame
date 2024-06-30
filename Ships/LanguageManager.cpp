#include "LanguageManager.h"

LanguageManager::LanguageManager(const std::string fileHandle)
	: fileHandle(fileHandle) { }

void LanguageManager::setFilename(const std::string& name) {
	this->fileHandle = name;
}

std::vector<std::string> LanguageManager::splitString(const std::string& s, char delimiter) {
	std::vector<std::string> lineVec;
	std::string line;
	std::istringstream lineStream(s);
	while (std::getline(lineStream, line, delimiter)) {
		lineVec.push_back(line);
	}

	return lineVec;
}

void LanguageManager::loadCommunicates(void) {
	std::ifstream file(fileHandle);
	if (!file.is_open()) throw std::runtime_error("Unable to open the file");

	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> keyAndValue = splitString(line, '=');
		if (keyAndValue.size() == 2) {
			container[keyAndValue[0]] = keyAndValue[1];
		} else {
			throw invalid_line_in_file("Invalid line in language file");
		}
	}

	file.close();
}

std::string LanguageManager::getCommunicate(const std::string& key) const {
	auto it = container.find(key);
	if (it != container.end()) {
		return it->second;
	}

	throw key_not_found("Key not found in communicate hash map");
}