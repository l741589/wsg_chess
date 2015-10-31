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
	Sprite*directionArrow;
	float direction = 0;
	int hp;
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
	Ship*getShip();
	int getHp() { return hp; }
	void moveTo(const Vec2 &pos);
	void turn(float radius);
	~Actor();
};