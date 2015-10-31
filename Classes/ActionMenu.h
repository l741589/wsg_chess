#pragma once

#include "util.h"
class FightScene;
class Actor;

class ActionMenu {
private:
	Node*menu;
	Node*directMenu;
	Node*attackMenu;
	Actor*actor;
public:
	ActionMenu();
	~ActionMenu();
	Node*show(const char*title, std::initializer_list<std::pair<std::string, std::function<void(Button*button)> > > callback);
	void hide();
	Node*getMenu() { return menu; }
};