#pragma once
#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"


class Actor : public spine::SkeletonAnimation {
private:
	void bindEvent();
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
	static Actor* create(int id);
	bool init(int id);
};