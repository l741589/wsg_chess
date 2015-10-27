#include "ShipManager.h"

using namespace cocos2d;

ShipManager*ShipManager::instance = nullptr;

ShipManager* ShipManager::getInstance() {
	if (!instance) instance = new ShipManager();
	return instance;
}

spine::SkeletonAnimation* ShipManager::createActor(int id) {
	char buf1[32],buf2[32];
	sprintf(buf1, "Ship_girl_%d.json", id);
	sprintf(buf2, "Ship_girl_%d.atlas", id);
	auto sp = spine::SkeletonAnimation::createWithFile(buf1, buf2);
	sp->setSkin(Skin::Ship::Normal);
	sp->setAnimation(0,Anim::Ship::Normal,true);
	return sp;
}
