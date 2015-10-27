#include "FieldLayer.h"
#include "Actor.h"

void FieldLayer::createMoveTiles(Actor*actor, onSelectedListener listener) {
	while (actor->direction >= 2 * PI) actor->direction -= 2 * PI;
	while (actor->direction < 0) actor->direction += 2 * PI;
	int glen = (int)round(actor->getShip()->getSpeed() / 5);
	const Vec2&v = actor->getFieldPosition();
	int al = (int)(v.x + v.y);
	int ar = (int)(v.x - v.y);
	if (actor->direction > PI * 7 / 4 || actor->direction < PI / 4) {
		createTiles(v, glen, [=](const Vec2&v) {return v.x + v.y >= al&&v.x - v.y >= ar; }, { 128, 255, 255 },listener);
	} else if (actor->direction>PI / 4 && actor->direction < PI * 3 / 4) {
		createTiles(v, glen, [=](const Vec2&v) {return v.x + v.y >= al&&v.x - v.y <= ar; }, { 128, 255, 255 }, listener);
	} else if (actor->direction > PI * 3 / 4 && actor->direction < PI * 5 / 4) {
		createTiles(v, glen, [=](const Vec2&v) {return v.x + v.y <= al&&v.x - v.y <= ar; }, { 128, 255, 255 }, listener);
	} else if (actor->direction>PI * 5 / 4 && actor->direction < PI * 7 / 4) {
		createTiles(v, glen, [=](const Vec2&v) {return v.x + v.y <= al&&v.x - v.y >= ar; }, { 128, 255, 255 }, listener);
	}
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

void FieldLayer::createTiles(Vec2 start, int glen, std::function<bool(const Vec2&)> filter, Color3B color, onSelectedListener listener) {
	if (this->getChildrenCount()) this->removeAllChildren();
	std::set<Vec2, VecLess> flags;
	std::list<Vec2> queue;
	int cnt = 0;
	addVec(flags, queue, start);
	while (!queue.empty()) {
		Vec2 v = queue.front();
		queue.pop_front();
		if (abs(v.x - start.x) + abs(v.y - start.y) > glen) continue;
		if (!filter(v)) continue;
		auto sp = createTile(v,color,listener);
		sp->setOpacity(0);
		sp->runAction(Sequence::createWithTwoActions(DelayTime::create(0.01f*cnt++), FadeIn::create(0.5f)));
		addVec(flags, queue, v + Vec2{ 1, 0 });
		addVec(flags, queue, v + Vec2{ 0, 1 });
		addVec(flags, queue, v + Vec2{ -1, 0 });
		addVec(flags, queue, v + Vec2{ 0, -1 });

	}
}

Sprite* FieldLayer::createTile(Vec2 position, Color3B color, onSelectedListener listener) {
	Sprite*sp = Sprite::create("field_rect.png");
	sp->setScale(TileSize / (float)SrcTileSize);
	sp->setColor(color);
	sp->setOpacity(0.5f);
	sp->setPosition(filedToLocal(position));
	addChild(sp);
	if (listener) {
		EventListenerTouchOneByOne*e = EventListenerTouchOneByOne::create();
		e->onTouchBegan = util::isPtInNodeEventCallback;
		e->onTouchEnded = [=](Touch*t, Event*e) {
			listener((Sprite*)e->getCurrentTarget(), position); 
		};
		sp->getEventDispatcher()->addEventListenerWithSceneGraphPriority(e, sp);
	}
	return sp;
}

void FieldLayer::clear() {
	for (Node* e : getChildren()) {
		e->runAction(Sequence::create(
			FadeOut::create(0.5f),
			CallFunc::create([=]() {e->removeFromParentAndCleanup(true); }),
			nullptr));
	}
	
}

