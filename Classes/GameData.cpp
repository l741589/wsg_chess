#include "GameData.h"

#include "Ship.h"


GameData*G::gameData = new GameData();

GameData::GameData() {
	Ship*ship = new Ship();
	ship->_Id = 1;
	ship->_Speed = 30;
	ship->_TurningRaduis = 700;
	ship->_Name = "Hood";
	ships.push_back(ship);
	shipMapById[ship->_Id] = ship;

	ship = new Ship();
	ship->_Id = 1082;
	ship->_Speed = 39;
	ship->_TurningRaduis = 700;
	ship->_Name = "LightWorm";
	ships.push_back(ship);
	shipMapById[ship->_Id] = ship;

}

GameData::~GameData() {
	for (Ship*ship : ships) delete ship;
}
