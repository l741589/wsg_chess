#include "FightScene.h"
#include "Actor.h"
#include "FieldLayer.h"

using namespace cocos2d;

bool FightScene::init() {
	if (!Scene::init()) return false;
	fieldLayer = FieldLayer::create();
	this->addChild(fieldLayer, 1);

	Layer* ships = Layer::create();
	this->addChild(ships,2);

	auto hood = Actor::create(this,1);
	ships->addChild(hood);
	hood->setFieldPositoin({ 5, 5 });


	
	return true;
}