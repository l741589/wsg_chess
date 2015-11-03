#include "ActionMenu.h"
#include "StringRes.h"
#include "FightScene.h"
#include "FieldLayer.h"
#include "Actor.h"
#include "ControlSet.h"
#include "layout/LayoutInflater.h"
#include "StringRes.h"

void BaseMenu::hide() {
	menu->removeAllChildren();
	menu->setVisible(false);
	menu->setContentSize({ MENU_WIDTH, 0 });
}
//////////////////////////////////////////////////////////////////////////

ActionMenu::ActionMenu() : BaseMenu() {
	menu = LayoutInflater::inflate("ctrl/Panel1.json");
	util::setLayoutParameter((Widget*)menu, Margin::ZERO, LinearLayoutParameter::LinearGravity::RIGHT);
	menu->retain();
	hide();
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
	menu->setContentSize({ MENU_WIDTH, 70.0f * menuDef.size() });
	auto parent = menu->getParent();
	menu->removeFromParent();
	parent->addChild(menu);
	
	return menu;
}
//////////////////////////////////////////////////////////////////////////
AttackMenu::AttackMenu() : BaseMenu()
{
	menu = LayoutInflater::inflate("ctrl/Panel1.json");
	util::setLayoutParameter((Widget*)menu, Margin::ZERO, LinearLayoutParameter::LinearGravity::RIGHT);
	menu->retain();
	hide();
}

void AttackMenu::addEquip(Equip*e) {
	auto n = LayoutInflater::inflate("ctrl/EquipmentItem.json");
	Button*button = util::find<Button>(n,"Button");
	Text*name = util::find<Text>(n, "Name");
	Text*range = util::find<Text>(n, "Range");
	Text*type = util::find<Text>(n, "Type");
	ImageView*image = util::find<ImageView>(n, "Image");
	ImageView*level = util::find<ImageView>(n, "Level");
	auto eq = e->getEquipment();
	name->setString(eq->title);
	image->loadTexture(util::format("equip/equip_L_%d.png", eq->picId));
	level->loadTexture(util::format("ui/equipBG%d.png", eq->star));
	menu->addChild(n);
	type->setString(G::getString("equipment.type", eq->type));
	if (eq->type == 1) {
		range->setString(G::getString("equipment.range", eq->range));
	}
	else {
		range->setString("");
	}
	button->addClickEventListener([=](Ref*) {
		e->createTiles(actor);
	});
}

void AttackMenu::show(Actor*actor)
{
	hide();
	this->actor = actor;
	menu->removeAllChildren();
	for (auto e : actor->getEquips()) {
		addEquip(e);
	}
	menu->setVisible(true);
	menu->setContentSize({ MENU_WIDTH,64.0f * actor->getEquips().size() });
	auto parent = menu->getParent();
	menu->removeFromParent();
	parent->addChild(menu);

}
