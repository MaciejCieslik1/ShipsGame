#include "FileHandler.h"


FileHandler::FileHandler()
	: name("") { }


FileHandler::FileHandler(const std::string &name)
    : name(name) { }


bool FileHandler::isInteger(const std::string& s) 
{
    std::istringstream iss(s);
    int val;
    iss >> std::noskipws >> val;
    return iss.eof() && !iss.fail();
}


bool FileHandler::isDouble(const std::string& s) 
{
    std::istringstream iss(s);
    double val;
    iss >> std::noskipws >> val;
    return iss.eof() && !iss.fail();
}


std::vector<std::string> FileHandler::parseObject(const std::string& str) 
{
	std::stringstream streamStream(str);
	std::vector<std::string> strVec;
	std::string word;

	while (streamStream >> word) 
	{
		strVec.push_back(word);
	}

	return strVec;
}


std::vector<std::unique_ptr<Player>> FileHandler::loadPlayerInfo(void)
{
	std::ifstream file(this->name);
	std::vector<std::unique_ptr<Player>> container;

	if (!file.is_open()) throw std::runtime_error("Failed to open the file");

	std::string line;
	while (std::getline(file, line)) 
	{
		std::vector<std::string> argv = parseObject(line);
		if (argv.size() != 3) throw improper_vector_size("Unable to load player class from file");

		// TODO Parse for its data-type
		std::string name = argv[0];
		int intArg1 = std::stoi(argv[1]);
		int intArg2 = std::stoi(argv[2]);

		std::unique_ptr<Player> object = std::make_unique<Player>(name, intArg1, intArg2);
		container.push_back(std::move(object));
	}
	file.close();
	return container;
}


std::vector<std::unique_ptr<Ship>> FileHandler::loadShipInfo(void) 
{
	std::ifstream file(this->name);
	std::vector<std::unique_ptr<Ship>> container;

	if (!file.is_open()) throw std::runtime_error("Failed to open the file");

	std::string line;
	while (std::getline(file, line)) 
	{
		std::vector<std::string> argv = parseObject(line);

		if (argv.size() < 5) throw improper_vector_size("Failed to load Ship class from file");

		int movement = std::stoi(argv[0]);
        int hitPoints = std::stoi(argv[1]);
		char name = argv[2][0];
        int coordsSize = std::stoi(argv[3]);
        int missileIDSize = std::stoi(argv[4]);

        std::vector<Coords> coords;
        coords.reserve(coordsSize);
        for (int i = 4; i < 4 + coordsSize * 2; i += 2) 
		{
            int x = std::stoi(argv[i]);
            int y = std::stoi(argv[i + 1]);
            coords.push_back(Coords(x, y));
        }

        std::vector<int> missileIDs;
        missileIDs.reserve(missileIDSize);
        for (int i = 4 + coordsSize * 2; i < 4 + coordsSize * 2 + missileIDSize; ++i) 
		{
            missileIDs.push_back(std::stoi(argv[i]));
        }

        std::unique_ptr<Ship> ship = std::make_unique<Ship>(movement, hitPoints, name, coords);
        ship->setMissileIDs(missileIDs);
        container.push_back(std::move(ship));
	}
	file.close();
	return container;
}


std::vector<std::unique_ptr<CruiseMissile>> FileHandler::loadMissileInfo(void) 
{
	std::ifstream file(this->name);
	std::vector<std::unique_ptr<CruiseMissile>> container;

	if (!file.is_open()) throw std::runtime_error("Failed to open the file");

	std::string line;
	while (std::getline(file, line)) 
	{
		std::vector<std::string> argv = parseObject(line);

		if (argv.size() != 3) throw improper_vector_size("Failed to load Cruise Missile object from file");

		// TODO Parse for its data-type
		int range = std::stoi(argv[0]);
		int damage = std::stoi(argv[1]);
		int missileID = std::stoi(argv[2]);

		std::unique_ptr<CruiseMissile> object = std::make_unique<CruiseMissile>(range, damage, missileID);
		container.push_back(std::move(object));
	}
	file.close();
	return container;
}


void FileHandler::setFilename(const std::string& name) 
{
	this->name = name;
}
