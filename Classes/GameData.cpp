#include "GameData.h"

USING_NS_CC;

GameData*G::gameData = new GameData();

#define DEL(ITER) for (auto t : ITER) delete t;

GameData::GameData() {
	std::string&& s=FileUtils::getInstance()->getStringFromFile("GameData.json");
	doc.Parse(s.c_str());
	read<Ship>("shipCard", ships, shipMapById,[](Ship*ship) {return ship->cid < 20000000; });
	read<Equipment>("shipEquipmnt", equipments, equipmentsMapById);
}

GameData::~GameData() {
	DEL(ships);
	DEL(equipments);
}
