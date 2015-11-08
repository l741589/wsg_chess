#include "FieldLayer.h"
#include "Actor.h"

void FieldLayer::createMoveTiles(Actor*actor, onSelectedListener listener) {
	createTiles(actor, [=](const Vec2&sv,const Vec2&v) {
		ColorF4B color(128, 255, 255, 128);
		auto direction = actor->getDirection();
		int glen = (int)round(actor->getShip()->speed / 5);
		auto v2 = v - actor->getFieldPosition();
		if (v2 == Vec2::ZERO) return color;
		auto v1= Vec2::forAngle(direction);		
		auto angle = Vec2::angle(v1, v2);
		return sv.distanceSquared(v) <= glen*glen&&angle <= PI *0.26 ? color : ColorF4B::Flag::DISABLE;
	}, listener);
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

Node* FieldLayer::createTiles(Actor* actor, VecFilter filter, onSelectedListener listener)
{
	Node*group = Node::create();
	const Vec2&start = actor->getFieldPosition();
	removeAllChildren();
	addChild(group);
	std::set<Vec2, VecLess> flags;
	std::list<Vec2> queue;
	int cnt = 0;
	addVec(flags, queue, start);
	while (!queue.empty()) {
		Vec2 v = queue.front();
		queue.pop_front();
		if (v.x < 0 || v.y<0) continue;
		auto color = filter(start,v);
		if (color.f==ColorF4B::Flag::DISABLE) continue;
		if (color.f&ColorF4B::Flag::SHOW) 
			group->addChild(createTile(v, cnt++, color, listener));
		if (color.f &ColorF4B::Flag::ALLOW) {
			addVec(flags, queue, v + Vec2{ 1, 0 });
			addVec(flags, queue, v + Vec2{ 0, 1 });
			addVec(flags, queue, v + Vec2{ -1, 0 });
			addVec(flags, queue, v + Vec2{ 0, -1 });
		}
	}	
	return group;
}

FieldTile* FieldLayer::createTile(Vec2 position,int index, Color4B color, onSelectedListener listener) {
	FieldTile*sp = FieldTile::create();
	sp->setColor(Color3B(color));
	sp->setPosition(fieldToLocal(position));
	sp->index = index;
	if (listener) {
		EventListenerTouchOneByOne*e = EventListenerTouchOneByOne::create();
		e->onTouchBegan = G::isPtInNodeEventCallback;
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
		Spawn::create(
			FadeTo::create(0.5f,color.a),
			RotateTo::create(0.5f, 0),
			ScaleTo::create(0.5f, targetScale),
			nullptr
		),
		nullptr
	));
	return sp;
}

void FieldLayer::clear(Node*group, float time) {
	if (group == nullptr) {
		for (auto e : getChildren()) clear(e, time);
	} else {
		int max = 1;
		for (Node* e : group->getChildren()) {
			FieldTile*sp = dynamic_cast<FieldTile*>(e);
			if (sp->index > max) max = sp->index;
		}
		float es = time / max;
		for (Node* e : group->getChildren()) {
			FieldTile*sp = dynamic_cast<FieldTile*>(e);
			sp->enable = false;
			if (sp == nullptr) return;
			e->runAction(Sequence::create(
				DelayTime::create(es*sp->index),
				Spawn::create(
				FadeOut::create(0.5f),
				RotateTo::create(0.5f, 90),
				ScaleTo::create(0.5f, 0),
				nullptr
				),
				nullptr
				));
		}
		G::postDelay(this, time + 1, [=]() {
			if (this->getChildren().find(group)!=this->getChildren().end())
				group->removeFromParent(); 
		});
	}
}

bool FieldLayer::init()
{
	if (!Node::init()) return false;
	return true;
}

