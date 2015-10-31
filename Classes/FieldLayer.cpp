#include "FieldLayer.h"
#include "Actor.h"

void FieldLayer::createMoveTiles(Actor*actor, onSelectedListener listener) {
	auto direction = actor->getDirection();
	//while (direction >= 360) direction -= 360;
	//while (direction < 0) direction += 360;
	int glen = (int)round(actor->getShip()->speed / 5);
	const Vec2&v = actor->getFieldPosition();
	int al = (int)(v.x + v.y);
	createTiles(v, glen, [=](const Vec2&v) {
		auto v2 = v - actor->getFieldPosition();
		if (v2 == Vec2::ZERO) return true;
		auto v1= Vec2::forAngle(direction);		
		auto angle = Vec2::angle(v1, v2);
		return angle <= PI *0.26;
	}, { 128, 255, 255 }, listener);
}

struct VecLess {
	bool operator()(Vec2 l, Vec2 r) {
		if (l.x < r.x) return true;
		if (l.x == r.x) return l.y < r.y;
		return false;
	}
};

void addVec(std::set<Vec2, VecLess>& flags, std::list<Vec2>& queue,Vec2 p) {
	if (flags.find(p)!=flags.end()) return;
	queue.push_back(p);
	flags.insert(p);
}

void FieldLayer::createTiles(Vec2 start, int glen, VecFilter filter, Color3B color, onSelectedListener listener) {
	if (this->getChildrenCount()) this->removeAllChildren();
	std::set<Vec2, VecLess> flags;
	std::list<Vec2> queue;
	int cnt = 0;
	addVec(flags, queue, start);
	while (!queue.empty()) {
		Vec2 v = queue.front();
		queue.pop_front();
		if (v.x < 0 || v.y<0) continue;
		if (abs(v.x - start.x) + abs(v.y - start.y) > glen) continue;
		if (filter(v)) createTile(v,cnt++,color,listener);
		addVec(flags, queue, v + Vec2{ 1, 0 });
		addVec(flags, queue, v + Vec2{ 0, 1 });
		addVec(flags, queue, v + Vec2{ -1, 0 });
		addVec(flags, queue, v + Vec2{ 0, -1 });

	}
}

FieldTile* FieldLayer::createTile(Vec2 position,int index, Color3B color, onSelectedListener listener) {
	FieldTile*sp = FieldTile::create();
	sp->setColor(color);
	sp->setPosition(fieldToLocal(position));
	sp->index = index;
	addChild(sp);
	if (listener) {
		EventListenerTouchOneByOne*e = EventListenerTouchOneByOne::create();
		e->onTouchBegan = util::isPtInNodeEventCallback;
		e->onTouchMoved = [=](Touch*t, Event*e) {			
			clear();
		};
		e->onTouchEnded = [=](Touch*t, Event*e) {
			auto ft = dynamic_cast<FieldTile*>(e->getCurrentTarget());
			if (ft->enable)listener(ft, position);
		};
		sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(e, sp);
	}
	sp->setOpacity(0);
	sp->setRotation(-90);
	sp->setScale(0);
	auto targetScale=TileSize / (float)SrcTileSize;
	sp->runAction(Sequence::create(
		DelayTime::create(0.01f*sp->index),
		Spawn::create(
			FadeIn::create(0.5f),
			RotateTo::create(0.5f, 0),
			ScaleTo::create(0.5f, targetScale),
			nullptr
		),
		nullptr
	));
	return sp;
}

void FieldLayer::clear() {
	for (Node* e : getChildren()) {
		FieldTile*sp = dynamic_cast<FieldTile*>(e);
		sp->enable = false;
		if (sp == nullptr) return;
		e->runAction(Sequence::create(
			DelayTime::create(0.01f*sp->index),
			Spawn::create(
				FadeOut::create(0.5f),
				RotateTo::create(0.5f, 90),
				ScaleTo::create(0.5f, 0),
				nullptr
				),
			CallFunc::create([=]() {e->removeFromParent(); }),
			nullptr
		));
	}
	
}

bool FieldLayer::init()
{
	if (!Node::init()) return false;
	return true;
}

