#include "InfoBar.h"
#include "FightScene.h"
#include "layout/LayoutInflater.h"
#include "Actor.h"
#include "ActionMenu.h"
#include "FieldLayer.h"

InfoBar::InfoBar(FightScene*scene) {
	this->scene = scene;
	auto node = LayoutInflater::inflate("ctrl/InfoBar.json");
	scene->addChild(node);
	actionMenu = new ActionMenu();
	node->addChild(actionMenu->getMenu());
	node->setPosition(Vec2(Director::getInstance()->getWinSize()));
	avatarImage=util::find<ImageView>(node, "AvatarImage");
	shipClass = util::find<ImageView>(node, "Class");
	flag = util::find<ImageView>(node, "Flag");
	name = util::find<Text>(node, "Name");
	hp = util::find<Text>(node, "Hp");
	hpBar = util::find<LoadingBar>(node, "HpBar");
}

InfoBar::~InfoBar() {
	delete actionMenu;
}

void InfoBar::update(Actor*actor) {
	if (actor) {
		avatarImage->setVisible(true);
		char buf[64];
		sprintf(buf,"model/S_NORMAL_%d.png", actor->getShip()->picId);
		avatarImage->loadTexture(buf);
		sprintf(buf, "ui/st_%d.png", actor->getShip()->type);
		shipClass->setVisible(true);
		shipClass->loadTexture(buf);
		showActionMenu(actor);
		name->setString(actor->getShip()->title);
		
		sprintf(buf, "%d/%d", actor->getHp(), actor->getShip()->hpMax);
		hp->setString(buf);
		hpBar->setVisible(true);
		hpBar->setPercent(actor->getHp()*100.0f / actor->getShip()->hpMax);
	} else {
		actionMenu->hide();
		avatarImage->setVisible(false);
		shipClass->setVisible(false);
		name->setString("");
		hpBar->setVisible(false);
		hp->setString("");
	}
}


void InfoBar::showActionMenu(Actor*actor) {
	actionMenu->show(
		"battle.action.title",
		{
			{ "battle.action.move", [=](Ref*) {
				this->scene->fieldLayer->createMoveTiles(actor, [=](Sprite*, const Vec2&pos) {
					CCLOG("%f,%f", pos.x, pos.y);					
					scene->fieldLayer->clear();
					actor->moveTo(pos);
				});
			}
			},
			{ "battle.action.direct", [=](Ref*) {
				actionMenu->show(
					"",
					{
						{ "battle.action.direct.ml", [=](Ref*) {  actor->turn(-PI / 4); } },
						{ "battle.action.direct.mm", [=](Ref*) { actor->turn(-PI / 6); } },
						{ "battle.action.direct.ms", [=](Ref*) { actor->turn(-PI / 12); } },
						{ "battle.action.direct.pl", [=](Ref*) { actor->turn(PI / 4); } },
						{ "battle.action.direct.pm", [=](Ref*) { actor->turn(PI / 6); } },
						{ "battle.action.direct.ps", [=](Ref*) { actor->turn(PI / 12); } },
						{ "cancel", [=](Ref*) {showActionMenu(actor); } },
					}
				);
			}
			},
			{ "battle.action.attack", nullptr }
		}
	);
}
