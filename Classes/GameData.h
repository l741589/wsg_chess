#pragma once

#include<map>
#include<list>
#include "json/rapidjson.h"
#include "json/document.h"
class Ship;

class GameData {
public:
	GameData();
	~GameData();
	rapidjson::Document doc;
	std::list<const Ship*> ships;		
	std::map<int, Ship*> shipMapById;
};

namespace G {
	extern GameData*gameData;
}