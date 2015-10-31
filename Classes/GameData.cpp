#include "GameData.h"

#include "Ship.h"

USING_NS_CC;

GameData*G::gameData = new GameData();



GameData::GameData() {
	std::string&& s=FileUtils::getInstance()->getStringFromFile("GameData.json");
	doc.Parse(s.c_str());
	auto&shipcards = doc["shipCard"];
	for (auto i = shipcards.Begin(); i != shipcards.End(); ++i) {
		Ship*ship = new Ship(*i);
		if (ship->cid >= 20000000) {
			delete ship;
			continue;
		}
		ships.push_back(ship);
		shipMapById[ship->shipIndex] = ship;
	}
	
	

}

GameData::~GameData() {
	for (const Ship*ship : ships) delete ship;
}
