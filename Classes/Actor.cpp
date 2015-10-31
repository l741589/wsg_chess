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
		auto node = e->getCurrentTarget();
		auto p = node->convertTouchToNodeSpace(t);
		if (!bound.containsPoint(p)) return false;
		this->runAction(ScaleTo::create(0.1f, 1.2f));
		return true;
	};
	e->onTouchEnded = e->onTouchCancelled = [this](Touch*t, Event*e) {
		this->runAction(ScaleTo::create(0.1f, 1));
		Ship*ship = getShip();
		this->fightScene->actionMenu->show(
			"battle.action.title", 
			{
				{ "battle.action.move", [=](Ref*) {
						this->fightScene->fieldLayer->createMoveTiles(this, [this](Sprite*, const Vec2&pos) {
							CCLOG("%f,%f", pos.x, pos.y);

							if (pos!=fieldPosition) setDirection((pos - fieldPosition).getAngle());
							fightScene->fieldLayer->clear();
							auto move = Sequence::create(
								MoveTo::create(0.5f, FieldLayer::fieldToLocal(pos)),
								CallFunc::create([=]() {setFieldPositoin(pos); }),
								nullptr);
							move->setTag(0x307E);
							stopActionByTag(0x307E);
							runAction(move);
							if (abs(pos.x - fieldPosition.x) > 2) {
								anim->setAnimation(1, Anim::Throw, false);
							}
						});
					}
				},
				{ "battle.action.direct", [=](Ref*) {
						this->fightScene->actionMenu->show(
							"",
							{
								{ "battle.action.direct.ml", [=](Ref*) { setDirection(getDirection() - PI / 4); } },
								{ "battle.action.direct.mm", [=](Ref*) { setDirection(getDirection() - PI / 6); } },
								{ "battle.action.direct.ms", [=](Ref*) { setDirection(getDirection() - PI / 12); } },
								{ "battle.action.direct.pl", [=](Ref*) { setDirection(getDirection() + PI / 4); } },
								{ "battle.action.direct.pm", [=](Ref*) { setDirection(getDirection() + PI / 6); } },
								{ "battle.action.direct.ps", [=](Ref*) { setDirection(getDirection() + PI / 12); } },
							}
						);
					} 
				},
				{ "battle.action.attack", nullptr },
				{ "cancel", [](Ref*) {} },
			}
		);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(e, this);

}

bool Actor::init(FightScene*fightScene, int id) {
	this->_id = id;
	this->fightScene = fightScene;
	char buf1[32], buf2[32];
	sprintf(buf1, "qver/Ship_girl_%d.json", id);
	sprintf(buf2, "qver/Ship_girl_%d.atlas", id);
	anim = spine::SkeletonAnimation::createWithFile(buf1, buf2, 0.5);
	anim->setSkin(Skin::Normal);
	anim->setAnimation(0, Anim::Normal, true);
	addChild(anim, 5);
	bindEvent();
	directionArrow = Sprite::create("directionArrow.png");
	directionArrow->setColor({ 0,0,255 });
	directionArrow->setAnchorPoint({ 0,0 });
	addChild(directionArrow, 3);
	setDirection(direction);
	return true;
}

Ship* Actor::getShip() {
	if (!ship) ship = G::gameData->shipMapById[_id];
	return ship;
}

void Actor::setFieldPositoin(Vec2 pos) {
	fieldPosition = pos;
	setPosition(fightScene->fieldLayer->fieldToLocal(pos));
}

void Actor::setDirection(float raduis)
{	
	while (raduis >= PI) raduis -= 2*PI;
	while (raduis < -PI) raduis += 2*PI;
	this->direction = raduis;
	auto trans = AffineTransform::IDENTITY;
	trans = AffineTransformTranslate(trans, 0, -20);
	trans = AffineTransformScale(trans, 2, 0.7f);
	trans = AffineTransformRotate(trans, raduis);
	trans = AffineTransformTranslate(trans, -32, -32);
	directionArrow->setAdditionalTransform(trans);
	anim->getSkeleton()->flipX = raduis >= PI / 2 || raduis < -PI / 2;
}
