#pragma once

#include"cocos2d.h"

class FightScene : public cocos2d::Scene {
public:
	CREATE_FUNC(FightScene);
	bool init() override;
	void bindActorEvent(Node*actor);
};