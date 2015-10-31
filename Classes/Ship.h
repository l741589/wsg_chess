#pragma once

#include "cocos2d.h"
#include "util.h"
#include "GameData.h"

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
		//JSON_SET(equipmentType);
		JSON_SET(evoClass);
		JSON_SET(getDialogue);
		CCLOG("Ship Loaded: %s", title);
	}
};