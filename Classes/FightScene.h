#pragma once

#include"util.h"
#include "ActionMenu.h"

class FieldLayer;

class FightScene : public cocos2d::Scene {
private:
	void moveGameLayer(Touch*t, Event*e);
public:
	cocos2d::Layer*gameLayer;
	FieldLayer*fieldLayer;
	ActionMenu*actionMenu;
	CREATE_FUNC(FightScene);
	bool init() override;
	
};