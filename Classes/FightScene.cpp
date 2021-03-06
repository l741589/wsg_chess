#include "FightScene.h"
#include "Actor.h"
#include "FieldLayer.h"
#include "ActionMenu.h"
#include "layout/LayoutInflater.h"
#include "InfoBar.h"
#include "Weapon.h"

bool FightScene::init() {
	if (!Scene::init()) return false;

	gameLayer = Layer::create();
	gameLayer->setScale(0.5f);
	gameLayer->setAnchorPoint({ 0,0 });
	gameLayer->setPosition(0, 0);
	
	addChild(gameLayer);

	G::bindTouchEvent(gameLayer, [](Touch*, Event*) {return true; }, CC_CALLBACK_2(FightScene::moveGameLayer, this), nullptr);
	auto e=EventListenerMouse::create();
	e->onMouseScroll = [=](Event*e) {
		auto em = (EventMouse*)e;
		auto y=em->getScrollY();
		auto pos=em->getLocationInView();
		auto nodePos = gameLayer->convertToNodeSpace(pos);
		float scale = gameLayer->getScale()*pow(0.9f, y);
		gameLayer->setScale(scale);
		gameLayer->setPosition(pos - nodePos*scale);
	};
	gameLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(e, gameLayer);

	fieldLayer = FieldLayer::create();
	gameLayer->addChild(fieldLayer, 1);

	Node* ships = Node::create();
	gameLayer->addChild(ships,2);

	auto hood = Actor::create(this,1);
	ships->addChild(hood);
	hood->setFieldPositoin({ 0, 0 });
	hood->addEquip(1);
	hood->addEquip(2);
	hood->addEquip(3);
	hood->addEquip(4);
	
	auto glowWorm = Actor::create(this, 1082);
	ships->addChild(glowWorm);
	glowWorm->setFieldPositoin({ 5, 7 });
	glowWorm->addEquip(110);
	glowWorm->addEquip(120);
	glowWorm->addEquip(130);
	glowWorm->addEquip(140);
	glowWorm->addEquip(150);


	selector = Sprite::create("fieldRectSelector.png");
	selector->setScale(1.5f);
	selector->setColor({ 0xc0, 0xc0, 0xc0 });
	gameLayer->addChild(selector, 1);


	infoBar=new InfoBar(this);
	auto x=cocos2d::TMXTiledMap::create("map/1.tmx");
	x->setScale(3);
	
	Director::getInstance()->getScheduler()->schedule([x](float) {
		auto tl = x->getLayer("layer1");
		for (int i = 0; i < 100; ++i) {
			for (int j = 0; j < 100; ++j) {
				int gid = tl->getTileGIDAt({(float)i,(float)j });
				int id = -1;
				switch (gid)
				{
				case 26:id = 32; break;
				case 32:id = 26; break;
				default:break;
				}
				if (id >= 0) tl->setTileGID(id, { (float)i,(float)j });
			}
		}
	}, x, 1.0f, false, "updateTile");
	
	gameLayer->addChild(x);	
	G::bindTouchEvent(gameLayer, [=](Touch*t, Event*e) {
		auto n = e->getCurrentTarget();
		auto pos = n->convertTouchToNodeSpace(t);
		Vec2 v = FieldLayer::fixLocal(pos);
		selector->setPosition(v);
		auto actor=getActorAt(FieldLayer::localToField(pos));
		infoBar->update(actor);
		return true;
	},nullptr,nullptr);
	return true;
}

void FightScene::moveGameLayer(Touch*t, Event*e)
{
	auto n = e->getCurrentTarget();
	n->setPosition(n->getPosition() - (t->getPreviousLocation() - t->getLocation()));
}

FightScene::~FightScene() {
	delete infoBar;
}

Actor* FightScene::getActorAt(Vec2 fieldPosition) {
	for (Actor*a : actors) {
		if ((fieldPosition - a->getFieldPosition()).length() < 0.1f) {
			return a;
		}
	}
	return nullptr;
}
