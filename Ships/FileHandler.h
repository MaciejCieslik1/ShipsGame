#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "ShipsExceptions.h"
#include "CruiseMissile.h"
#include "Ship.h"
#include "Coords.h"
#include "Player.h"

class FileHandler
{
	std::string name;

	bool isInteger(const std::string& str);
	bool isDouble(const std::string& str);

	std::vector<std::string> parseObject(const std::string& str);

public:
	FileHandler();
	FileHandler(const std::string& name);

	void setFilename(const std::string& name);
	std::vector<std::unique_ptr<Player>> loadPlayerInfo(void);
	std::vector<std::unique_ptr<Ship>> loadShipInfo(void);
	std::vector<std::unique_ptr<CruiseMissile>> loadMissileInfo(void);

	template <typename T>
	void saveInfo(std::vector<std::unique_ptr<T>>& container);
};

template<typename T>
void FileHandler::saveInfo(std::vector<std::unique_ptr<T>>& container) {
    std::ofstream file(this->name);
    if (!file.is_open())
        throw std::runtime_error("Failed to open the file");

    for (const auto& obj : container) {
        file << *obj;
    }

    file.close();
}

#endif