#pragma once

#include "util.h"

class FightScene;
class Actor;
class ActionMenu;

class InfoBar {
private:
	ImageView* avatarImage;
	ImageView* shipClass;
	ImageView* flag;
	ActionMenu* actionMenu; 
	Text*hp;
	LoadingBar*hpBar;
	Text*name;
	FightScene*scene;
public:
	InfoBar(FightScene*scene);
	~InfoBar();
	void update(Actor*actor);
	void showActionMenu(Actor*actor);

	

};
