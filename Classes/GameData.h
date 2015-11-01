#pragma once

#include "util.h"
class Ship;
class Equipment;

class GameData {
public:
	GameData();
	~GameData();
	rapidjson::Document doc;
	std::list<const Ship*> ships;
	std::map<int,const Ship*> shipMapById;
	std::list<const Equipment*> equipments;
	std::map<int, const Equipment*> equipmentsMapById;

private:
	template<class T>
	void read(const char*field, std::list<const T*>& target, std::map<int, const T*>& map,
		std::function<bool(T*)> filter = nullptr, std::function<void(T*)> after = nullptr) {
		auto&vals = doc[field];
		for (auto i = vals.Begin(); i != vals.End(); ++i) {
			T*t = new T(*i);
			if (filter&&!filter(t)) {
				delete t;
				continue;
			}
			target.push_back(t);
			map[t->getId()] = t;
			if (after) after(t);
		}
	}
};

namespace G {
	extern GameData*gameData;
}


class Ship {
	friend class GameData;
public:
	int cid;
	int star;
	const char*	title;
	int	country;
	int	type;
	int	hp;
	int atk;
	int	def;
	int torpedo;
	int miss;
	int hit;
	int	capacity;
	int	antisub;
	float	speed;
	int radar;
	int range;
	int luck;
	const char*desc;
	const char*vow;
	const char*mainDialogue;
	int shipIndex;
	int shipTon;
	const char*titleClass;
	const char*classNo;
	int picId;
	int hpMax;
	int atkMax;
	int defMax;
	int torpedoMax;
	int missMax;
	int hitMax;
	int airDef;
	int airDefMax;
	int antisubMax;
	int radarMax;
	int luckMax;
	int evoLevel;
	int evoCid;
	int evoNeedItemCid;
	int evoToCid;
	int borderId;
	int canEvo;
	int maxOil;
	int maxAmmo;
	float repairOilModulus;
	float repairSteelModulus;
	float repairTime;
	std::set<int> equipmentType;
	int evoClass;
	const char*getDialogue;

	int getId() { return shipIndex; }
	Ship(rapidjson::Value&json) {
		JSON_SET(cid);
		if (cid >= 20000000) return;
		JSON_SET(star);
		JSON_SET(title);
		JSON_SET(country);
		JSON_SET(type);
		JSON_SET(hp);
		JSON_SET(atk);
		JSON_SET(def);
		JSON_SET(torpedo);
		JSON_SET(miss);
		JSON_SET(hit);
		JSON_SET(capacity);
		JSON_SET(antisub);
		JSON_SET(speed);
		JSON_SET(radar);
		JSON_SET(range);
		JSON_SET(luck);
		JSON_SET(desc);
		JSON_SET(vow);
		JSON_SET(mainDialogue);
		JSON_SET(shipIndex);
		JSON_SET(shipTon);
		JSON_SET(titleClass);
		JSON_SET(classNo);
		JSON_SET(picId);
		JSON_SET(hpMax);
		JSON_SET(atkMax);
		JSON_SET(defMax);
		JSON_SET(torpedoMax);
		JSON_SET(missMax);
		JSON_SET(hitMax);
		JSON_SET(airDef);
		JSON_SET(airDefMax);
		JSON_SET(antisubMax);
		JSON_SET(radarMax);
		JSON_SET(luckMax);
		JSON_SET(evoLevel);
		JSON_SET(evoCid);
		JSON_SET(evoNeedItemCid);
		JSON_SET(evoToCid);
		JSON_SET(borderId);
		JSON_SET(canEvo);
		JSON_SET(maxOil);
		JSON_SET(maxAmmo);
		JSON_SET(repairOilModulus);
		JSON_SET(repairSteelModulus);
		JSON_SET(repairTime);
		JSON_SET(equipmentType);
		JSON_SET(evoClass);
		JSON_SET(getDialogue);
		CCLOG("Ship Loaded: %s", title);
	}
};

class Equipment {
public:
	int cid;
	int star;
	const char*title;
	int country;
	int type;
	int atk;
	int	def;
	int	torpedo;
	int	antisub;
	int	radar;
	int hit;
	int	range;
	int	miss;
	int	luck;
	int	correction;
	int	effect;
	int author;
	const char*desc;
	int equipIndex;
	int picId;
	int aircraftAtk;
	int airDef;
	float airDefCorrect;
	std::set<int> shipType;
	int specialEffect;
	int aluminiumUse;
	int getId() { return equipIndex; }
	Equipment(rapidjson::Value&json) {
		JSON_SET(cid);
		JSON_SET(star);
		JSON_SET(title);
		JSON_SET(country);
		JSON_SET(type);
		JSON_SET(atk);
		JSON_SET(def);
		JSON_SET(torpedo);
		JSON_SET(antisub);
		JSON_SET(radar);
		JSON_SET(hit);
		JSON_SET(range);
		JSON_SET(miss);
		JSON_SET(luck);
		JSON_SET(correction);
		JSON_SET(effect);
		JSON_SET(author);
		JSON_SET(desc);
		JSON_SET(equipIndex);
		JSON_SET(picId);
		JSON_SET(aircraftAtk);
		JSON_SET(airDef);
		JSON_SET(airDefCorrect);
		JSON_SET(shipType);
		JSON_SET(specialEffect);
		JSON_SET(aluminiumUse);
		CCLOG("Equipment Loaded: %s", title);
	}
};