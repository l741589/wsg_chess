#include "FightScene.h"
#include "ShipManager.h"
#include "Actor.h"

using namespace cocos2d;




bool FightScene::init() {
	if (!Scene::init()) return false;
	Layer* fields = Layer::create();
	this->addChild(fields,1);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			auto fr = Sprite::create("field_rect.png");
			fr->setPosition({ 400.0f + i * 96, 300.0f + j * 96 });
			fr->setColor({ 0, 255, 255 });
			fr->setScale(1.5f);
			fields->addChild(fr);
			
		}
	}

	Layer* ships = Layer::create();
	this->addChild(ships,2);

	auto hood = Actor::create(1);
	ships->addChild(hood);
	hood->setPosition({ 400, 300 });


	
	return true;
}