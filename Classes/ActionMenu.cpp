#include "ActionMenu.h"
#include "StringRes.h"
#include "FightScene.h"
#include "FieldLayer.h"
#include "Actor.h"
#include "ControlSet.h"
#include "layout/LayoutInflater.h"
#include "StringRes.h"

ActionMenu::ActionMenu(FightScene* scene) {
	this->scene = scene;
	this->menu = nullptr;
}

ActionMenu::~ActionMenu() {
	if (menu) menu->removeFromParent();
}

Node* ActionMenu::show(const char*title,std::initializer_list<std::pair<std::string,std::function<void(Button*button)> > > menuDef) {
	hide();
	menu = LayoutInflater::inflate("ctrl/Panel1.json");
	for (auto p : menuDef) {
		Button*b = (Button*)LayoutInflater::inflate("ctrl/ButtonBlue1.json");
		b->setTitleText(G::getString(p.first));
		menu->addChild(b);
		if (!p.second) b->setEnabled(false);
		b->addClickEventListener([=](Ref*ref) {
			hide();
			if (p.second) p.second((Button*)ref);
		});
	}
	menu->setContentSize({ 160, 70.0f * menuDef.size() });
	this->scene->addChild(menu);
	menu->setPosition({ 200, 200 });
	menu->setScale(0);
	menu->runAction(ScaleTo::create(0.2f, 1));

	return menu;
}

void ActionMenu::hide() {
	if (!this->menu) return;
	auto menu = this->menu;
	this->menu->runAction(Sequence::createWithTwoActions(
		ScaleTo::create(0.2f, 0),
		CallFunc::create([menu]() {menu->removeFromParent(); })
		));
	this->menu = nullptr;
}
