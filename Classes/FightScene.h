#pragma once

#include"cocos2d.h"

class FieldLayer;

class FightScene : public cocos2d::Scene {
public:
	FieldLayer*fieldLayer;
	CREATE_FUNC(FightScene);
	bool init() override;
	void bindActorEvent(Node*actor);
};