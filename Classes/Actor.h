#pragma once
#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"
#include "Ship.h"

class FightScene;

class Actor : public cocos2d::Node {
private:
	void bindEvent();
	FightScene*fightScene;
	int _id;
	Ship*ship = nullptr;
	spine::SkeletonAnimation*anim;
	Vec2 fieldPosition;
public:	
	struct Anim{
		static const char* Antiaircraft;
		static const char* Attack;
		static const char* Damage;
		static const char* Normal;
		static const char* Throw;
		static const char* Wreck;
	};
	static struct Skin{
		static const char* Default;
		static const char* Damage;
		static const char* Normal;
	};
	const Vec2& getFieldPosition() const{ return fieldPosition; }
	void setFieldPositoin(Vec2 pos);
	float direction = 0;
	static Actor* create(FightScene*fightScene, int id);
	bool init(FightScene*scene,int id);
	Ship*getShip();
};