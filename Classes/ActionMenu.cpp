#include "ActionMenu.h"
#include "StringRes.h"
#include "FightScene.h"
#include "FieldLayer.h"
#include "Actor.h"
#include "ControlSet.h"
#include "layout/LayoutInflater.h"
#include "StringRes.h"

ActionMenu::ActionMenu() {
	menu = LayoutInflater::inflate("ctrl/Panel1.json");
	util::setLayoutParameter((Widget*)menu, Margin::ZERO, LinearLayoutParameter::LinearGravity::RIGHT);
	menu->retain();
}

ActionMenu::~ActionMenu() {
	if (menu) {
		menu->removeFromParent();
		menu->release();
	}
}

Node* ActionMenu::show(const char*title,std::initializer_list<std::pair<std::string,std::function<void(Button*button)> > > menuDef) {
	hide();
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
	menu->setVisible(true);
	menu->setContentSize({ 200, 70.0f * menuDef.size() });			
	auto parent = menu->getParent();
	menu->removeFromParent();
	parent->addChild(menu);
	
	return menu;
}

void ActionMenu::hide() {
	menu->removeAllChildren();
	menu->setVisible(false);
	menu->setContentSize({ 216, 0 });
}
