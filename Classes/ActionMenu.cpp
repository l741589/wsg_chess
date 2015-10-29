#include "ActionMenu.h"
#include "StringRes.h"
Button* ActionMenu::addButton(std::string text, std::function<void(Ref*)>callback)
{
	Button*b = Button::create("ui/newBtnBlue01.png", "ui/newBtnBlue02.png", "ui/newGray.png");
	b->setTitleText(G::getString(text));
	b->addClickEventListener([=](Ref*ref) {
		this->runAction(Sequence::create(ScaleTo::create(0.2f, 0),Hide::create(),nullptr));
		if (callback)  callback(ref);
	});
	b->setTitleFontSize(20);
	util::setLayoutParameter(b, { 0, 0, 0, -6 }, LinearGravity::CENTER_HORIZONTAL);
	buttons.push_back(b);
	addChild(b);
	return b;
}


bool ActionMenu::init()
{
	if (!VBox::init()) return false;
	util::setScale9Background(this, "ui/panelBG2.png");
	this->setAnchorPoint({ 0.5f,0.5f });
	return true;
}

bool ActionMenu::show(Vec2 position,std::string title, std::list<std::pair<std::string, std::function<void(Ref*)> > > items)
{
	this->removeAllChildren();
	buttons.clear();
	this->setPosition(position);

	Text*t = Text::create();
	t->setString(G::getString(title));
	t->setPosition({ 70,16 });

	auto l = Layout::create();
	addChild(l);
	l->addChild(t);
	util::setScale9Background(l, "ui/panelBG4.png");
	l->setContentSize({ 140,32 });
	util::setLayoutParameter(l, { 0,10,0,0 }, LinearGravity::CENTER_HORIZONTAL);

	for (auto item : items) {
		auto b=addButton(item.first, item.second);
		if (!item.second) {
			b->setEnabled(false);
		}
	}

	
	this->setContentSize({ 160,(float)(buttons.size() * 64 + 52) });

	
	this->setVisible(true);
	this->setScale(0);
	this->runAction(ScaleTo::create(0.2f,1));
	return true;
}
