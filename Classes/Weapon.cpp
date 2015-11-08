#include "Weapon.h"
#include "FightScene.h"
#include "FieldLayer.h"
#include "Actor.h"
#include "Cache.h"

namespace S {
	const char* Torpedo_under_sea = "Torpedo_under_sea";
	const char* Torpedo = "Torpedo";
	const char* Gunfire = "Gunfire";
	const char* Deep_water_bomb = "Deep_water_bomb";
	const char* Bomb = "Bomb";


	const char*WeaponName = "anim/Weapon";
	const char*WeaponJson = "anim/Weapon.json";
	const char*WeaponAtlas = "anim/Weapon.atlas";


	const char*	Aircraft_explosion = "Aircraft_explosion";
	const char*	Anti_aircraft_fire = "Anti_aircraft_fire";
	const char*	Base_blue = "Base_blue";
	const char*	Base_yellow = "Base_yellow";
	const char*	Big_bang_at_sea = "Big_bang_at_sea";
	const char*	Big_bang_ubder_sea = "Big_bang_ubder_sea";
	const char*	Bomb_at_sea = "Bomb_at_sea";
	const char*	Bomb_under_sea = "Bomb_under_sea";
	const char*	Bubble = "Bubble";
	const char*	Buff_effect = "Buff_effect";
	const char*	Lock_On = "Lock_On";
	const char*	Sank = "Sank";
	const char*	Shield = "Shield";
	const char*	Ship_fire = "Ship_fire";
	const char*	Small_bang_at_sea = "Small_bang_at_sea";
	const char*	Small_bang_under_sea = "Small_bang_under_sea";
	const char*	Smoke_L = "Smoke_L";
	const char*	Smoke_R = "Smoke_R";
	const char*	Splash = "Splash";
	const char*	Spray = "Spray";
	const char*	Torpedo_wave_at_sea = "Torpedo_wave_at_sea";
	const char*	Torpedo_wave_at_sea_by_air = "Torpedo_wave_at_sea_by_air";
	const char*	Waterlines = "Waterlines";


	const char*EffectName = "anim/Effect_All";
	const char*EffectJson = "anim/Effect_All.json";
	const char*EffectAtlas = "anim/Effect_All.atlas";
}

using namespace S;

spine::SkeletonAnimation*createWeapon(const char*type,bool loop,spine::CompleteListener listener) {
	auto w = G::cache->createSkeletonAnimation(WeaponName);
	w->setAnimation(0,type,loop);
	if (listener) w->setCompleteListener(listener);
	return w;

}

spine::SkeletonAnimation*createEffect(const char*type, bool loop, spine::CompleteListener listener) {
	auto w = G::cache->createSkeletonAnimation(EffectName);
	w->setAnimation(0, type, loop);
	if (listener) w->setCompleteListener(listener);
	return w;
}


Weapon::Weapon()
{
	removeAction = CallFunc::create(CC_CALLBACK_0(Weapon::removeFromParent, this));
	removeAction->retain();
}

Weapon::~Weapon()
{
	removeAction->release();
}

Weapon* Weapon::create(FightScene*scene, const Vec2&from, const  Vec2&to, Type type)
{
	auto w = create();
	if (!w->initialize(scene,from,to,type)) return nullptr;
	return w;
}

bool Weapon::initialize(FightScene*scene, const Vec2&f, const Vec2&t, Type type) {
	this->from = f;
	this->to = t;
	scene->gameLayer->addChild(this, 20);
	fromL = FieldLayer::fieldToLocal(from);
	toL = FieldLayer::fieldToLocal(to);
	scene->fieldLayer->clear();
	aFrom = scene->getActorAt(from);
	aTo = scene->getActorAt(to);
	
	runAction(Sequence::createWithTwoActions(DelayTime::create(5), removeAction));
	switch (type) {
	case GunFire: AnimGunfire();break;
	case Torpedo: AnimTorpedo();break;
	default:return false;
	}
	return true;
}

void Weapon::AnimTorpedo() {
	auto anim = createWeapon(S::Torpedo, true, nullptr);
	if (aFrom != nullptr) {
		anim->getSkeleton()->flipX = aFrom->getAnim()->getSkeleton()->flipX = from.x > to.x;
		aFrom->getAnim()->setAnimation(2, Actor::Anim::Throw, false);
	}
	float angle = (to - from).getAngle();
	anim->setPosition(fromL + Vec2{ 0,32 });
	anim->setVisible(false);
	addChild(anim);
	auto fromLQ = fromL + Vec2::forAngle(angle) * 48;
	anim->runAction(Sequence::create(
		DelayTime::create(0.5f),
		Show::create(),
		JumpTo::create(0.3, fromLQ, 16, 1),
		CallFunc::create([=]() {
			anim->removeFromParent();
			auto e = createEffect(S::Torpedo_wave_at_sea, false, nullptr);
			e->setPosition(fromLQ);
			e->setRotation(-CC_RADIANS_TO_DEGREES(angle));
			addChild(e);
			e->runAction(Sequence::create(
				MoveTo::create(1.0f, toL),
				CallFunc::create([=]() {
					e->removeFromParent();
					if (aTo != nullptr) {
						auto e2 = createEffect(S::Small_bang_at_sea, false, nullptr);
						aTo->getAnim()->setAnimation(3, Actor::Anim::Damage, false);
						e2->setPosition(toL);
						addChild(e2);
					}
				}),
				nullptr));
		}),
		nullptr));
}

void Weapon::AnimGunfire() {
	auto anim = createWeapon(Gunfire, true, nullptr);
	int fromRotate = from.x < to.x ? -90 : from.x>to.x ? 90 : 90;
	int toRotate = from.x < to.x ? 90 : from.x>to.x ? -90 : 90;
	if (aFrom != nullptr) {
		aFrom->getAnim()->getSkeleton()->flipX = from.x > to.x;
		aFrom->getAnim()->setAnimation(2, Actor::Anim::Throw, false);
	}
	anim->setRotation(fromRotate);
	anim->setPosition(fromL);
	anim->setVisible(false);
	addChild(anim);
	anim->runAction(Sequence::create(
		DelayTime::create(0.75f),
		Show::create(),
		Spawn::create(
			JumpTo::create(1.0f, toL, fromL.distance(toL) / 3, 1),
			RotateTo::create(1.0f, toRotate),
			nullptr),
		CallFunc::create([=]() {
		if (aTo == nullptr) {
			anim->removeFromParent();
			auto e = createEffect(S::Splash, false, nullptr);
			addChild(e);
			e->setPosition(toL);
		} else {
			anim->removeFromParent();
			auto e = createEffect(S::Small_bang_at_sea, false, nullptr);
			addChild(e);
			aTo->getAnim()->setAnimation(3, Actor::Anim::Damage, false);
			e->setPosition(toL);
		}
	}),
		nullptr
		));
}

