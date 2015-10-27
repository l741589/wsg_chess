#include "Actor.h"
#include "util.h"
#include "FightScene.h"
#include "FieldLayer.h"
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

const Rect bound = { -48, -48, 96, 96 };

Actor* Actor::create(FightScene*fightScene, int id) {
	Actor *pRet = new(std::nothrow) Actor();
	if (pRet && pRet->init(fightScene, id)) {
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
		Ship*ship = getShip();
		this->fightScene->fieldLayer->createMoveTiles(this, [this](Sprite*, const Vec2&pos) {
			CCLOG("%f,%f",pos.x, pos.y);
			anim->getSkeleton()->flipX = pos.x<fieldPosition.x;
			direction = rand_0_1() * 2 * PI;
			auto move = Sequence::create(
				MoveTo::create(0.5f, FieldLayer::filedToLocal(pos)),CallFunc::
				create([=]() {setFieldPositoin(pos); 
			fightScene->fieldLayer->clear();
			}),
				nullptr);
			move->setTag(0x307E);
			stopActionByTag(0x307E);
			runAction(move);
			anim->setAnimation(0, Anim::Throw,false);
			
		});
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(e, this);


}

bool Actor::init(FightScene*fightScene, int id) {
	this->_id = id;
	this->fightScene = fightScene;
	char buf1[32], buf2[32];
	sprintf(buf1, "Ship_girl_%d.json", id);
	sprintf(buf2, "Ship_girl_%d.atlas", id);
	anim = spine::SkeletonAnimation::createWithFile(buf1, buf2, 0.5);
	anim->setSkin(Skin::Normal);
	anim->setAnimation(0, Anim::Normal, true);
	addChild(anim);
	bindEvent();
	return true;
}

Ship* Actor::getShip() {
	if (!ship) ship = G::gameData->shipMapById[_id];
	return ship;
}

void Actor::setFieldPositoin(Vec2 pos) {
	fieldPosition = pos;
	setPosition(fightScene->fieldLayer->filedToLocal(pos));
}

