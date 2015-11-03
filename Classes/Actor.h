#pragma once
#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"
#include "GameData.h"

class FightScene;
class Actor;

class Equip {
private:
	const Equipment*equipment = nullptr;
	int id;
public:
	Equip(int id) {this->id = id;}
	int getId() { return id; }
	const Equipment*getEquipment() { if (!equipment)equipment = G::gameData->equipmentsMapById[id]; return equipment; }

	void createTiles(Actor*actor);
};

class Actor : public cocos2d::Node {
private:
	void bindEvent();
	FightScene*fightScene;
	int _id;
	const Ship*ship = nullptr;
	spine::SkeletonAnimation*anim;
	Vec2 fieldPosition;
	Sprite*directionArrow;
	float direction = 0;
	int hp;
	std::vector<Equip*> equips;
public:	
	struct Anim{
		static const char* Antiaircraft;
		static const char* Attack;
		static const char* Damage;
		static const char* Normal;
		static const char* Throw;
		static const char* Wreck;
	};
	struct Skin{
		static const char* Default;
		static const char* Damage;
		static const char* Normal;
	};
	const Vec2& getFieldPosition() const{ return fieldPosition; }
	void setFieldPositoin(Vec2 pos);
	float getDirection() { return direction; }
	void setDirection(float degree);
	static Actor* create(FightScene*fightScene, int id);
	bool init(FightScene*scene,int id);
	spine::SkeletonAnimation*getAnim() { return anim; }
	const Ship*getShip();
	int getHp() { return hp; }
	void moveTo(const Vec2 &pos);
	void turn(float radius);
	void addEquip(int id);
	const std::vector<Equip*>& getEquips() const { return equips; };
	FightScene*getFightScene() { return fightScene; }
	~Actor();
};