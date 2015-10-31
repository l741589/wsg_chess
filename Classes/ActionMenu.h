#pragma once

#include "util.h"
class FightScene;
class Actor;

class ActionMenu {
private:
	Node*menu;
	Node*directMenu;
	Node*attackMenu;
	FightScene*scene;
	Actor*actor;
public:
	ActionMenu(FightScene* scene);
	~ActionMenu();
	Node*show(const char*title, std::initializer_list<std::pair<std::string, std::function<void(Button*button)> > > callback);
	void hide();
};