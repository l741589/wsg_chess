#pragma once

#include<map>
#include<list>

class Ship;

class GameData {
public:
	GameData();
	~GameData();
	std::list<Ship*> ships;		
	std::map<int, Ship*> shipMapById;
};

namespace G {
	extern GameData*gameData;
}