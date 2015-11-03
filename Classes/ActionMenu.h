#pragma once

#include "util.h"
class FightScene;
class Actor;
class Equip;

class BaseMenu {
protected:
	Node*menu = nullptr;
	Actor*actor = nullptr;
public:
	void hide();
	Node*getMenu() { return menu; }
};

class ActionMenu : public BaseMenu {
public:
	ActionMenu();
	Node*show(const char*title, std::initializer_list<std::pair<std::string, std::function<void(Button*button)> > > callback);
};

class AttackMenu :public BaseMenu{
public:
	AttackMenu();
	void addEquip(Equip*e);
	void show(Actor*actor);
};
