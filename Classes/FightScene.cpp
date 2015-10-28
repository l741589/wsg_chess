#include "FightScene.h"
#include "Actor.h"
#include "FieldLayer.h"

using namespace cocos2d;

bool FightScene::init() {
	if (!Scene::init()) return false;

	gameLayer = Layer::create();
	gameLayer->setPosition(0, 0);
	addChild(gameLayer);
	auto e=EventListenerTouchOneByOne::create();
	e->onTouchBegan = [](Touch*, Event*) {return true; };
	e->onTouchMoved = CC_CALLBACK_2(FightScene::moveGameLayer,this);
	gameLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(e, gameLayer);

	fieldLayer = FieldLayer::create();
	gameLayer->addChild(fieldLayer, 1);

	Node* ships = Node::create();
	gameLayer->addChild(ships,2);

	auto hood = Actor::create(this,1);
	ships->addChild(hood);
	hood->setFieldPositoin({ 0, 0 });

	auto lightWorm = Actor::create(this, 1082);
	ships->addChild(lightWorm);
	lightWorm->setFieldPositoin({ 5, 7 });
	
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
	return true;
}

void FightScene::moveGameLayer(Touch*t, Event*e)
{
	auto n = e->getCurrentTarget();
	n->setPosition(n->getPosition() - (t->getPreviousLocation() - t->getLocation()));
}
