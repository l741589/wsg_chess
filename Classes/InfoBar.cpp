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
	attackMenu = new AttackMenu();
	node->addChild(attackMenu->getMenu());
	node->setPosition(Vec2(Director::getInstance()->getWinSize()));
	avatarImage=G::find<ImageView>(node, "AvatarImage");
	shipClass = G::find<ImageView>(node, "Class");
	flag = G::find<ImageView>(node, "Flag");
	name = G::find<Text>(node, "Name");
	hp = G::find<Text>(node, "Hp");
	hpBar = G::find<LoadingBar>(node, "HpBar");
}

InfoBar::~InfoBar() {
	delete actionMenu;
	delete attackMenu;
}

void InfoBar::update(Actor*actor) {
	if (actor) {
		avatarImage->setVisible(true);
		avatarImage->loadTexture(G::format("model/S_NORMAL_%d.png", actor->getShip()->picId));
		shipClass->setVisible(true);
		shipClass->loadTexture(G::format("ui/st_%d.png", actor->getShip()->type));
		showActionMenu(actor);
		name->setString(actor->getShip()->title);
		hp->setString(G::format("%d/%d", actor->getHp(), actor->getShip()->hpMax));
		hpBar->setVisible(true);
		hpBar->setPercent(actor->getHp()*100.0f / actor->getShip()->hpMax);
	} else {
		actionMenu->hide();
		attackMenu->hide();
		avatarImage->setVisible(false);
		shipClass->setVisible(false);
		name->setString("");
		hpBar->setVisible(false);
		hp->setString("");
	}
}


void InfoBar::showActionMenu(Actor*actor) {
	attackMenu->hide();
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
				attackMenu->hide();
				actionMenu->show(
					"",
					{
						{ "battle.action.direct.ml", [=](Ref*) { actor->turn(-PI / 4); } },
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
			{ "battle.action.attack", [=](Ref*) {
				actionMenu->hide();
				attackMenu->show(actor);
			} }
		}
	);
}
