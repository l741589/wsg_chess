#pragma once

#include"util.h"

class ActionMenu;
class FieldLayer;
class InfoBar;
class Actor;

class FightScene : public cocos2d::Scene {
private:
	void moveGameLayer(Touch*t, Event*e);
public:
	std::list<Actor*> actors;
	InfoBar*infoBar;
	cocos2d::Layer*gameLayer;
	FieldLayer*fieldLayer;
	Node*selector;
	CREATE_FUNC(FightScene);
	bool init() override;
	~FightScene();

	Actor*getActorAt(Vec2 fieldPosition);
};