#include "Actor.h"
#include "util.h"
USING_NS_CC;
using namespace util;

const char* Actor::Anim::Antiaircraft = "Antiaircraft";
const char* Actor::Anim::Attack = "attack";
const char* Actor::Anim::Damage = "damage";
const char* Actor::Anim::Normal = "normal";
const char* Actor::Anim::Throw = "throw";
const char* Actor::Anim::Wreck = "wreck";
const char* Actor::Skin::Default = "default";
const char* Actor::Skin::Damage = "damage";
const char* Actor::Skin::Normal = "normal";

const Rect bound = {-48,-48,96,96};

Actor* Actor::create(int id) {
	Actor *pRet = new(std::nothrow) Actor();
	if (pRet && pRet->init(id)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void Actor::bindEvent() {
	EventListenerTouchOneByOne*e = EventListenerTouchOneByOne::create();
	e->onTouchBegan = [this](Touch*t, Event*e) {
		auto&& r = bound + this->getPosition();
		if (!r.containsPoint(t->getLocation()))  return false;
		this->runAction(ScaleTo::create(0.1f, 1.2f));
		return true;
	};
	e->onTouchEnded = e->onTouchCancelled = [this](Touch*t, Event*e) {
		this->runAction(ScaleTo::create(0.1f, 1));

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(e, this);
}

bool Actor::init(int id) {
	char buf1[32], buf2[32];
	sprintf(buf1, "Ship_girl_%d.json", id);
	sprintf(buf2, "Ship_girl_%d.atlas", id);
	initWithFile(buf1, buf2, 0.5);
	initialize();
	setSkin(Skin::Normal);
	setAnimation(0, Anim::Normal, true);
	bindEvent();
	return true;
}


