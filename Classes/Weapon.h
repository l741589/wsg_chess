#pragma once
#include"util.h"
class FightScene;
class Actor;

class Weapon : public Node{
private:
	CallFunc*removeAction;
	Vec2 fromL,toL,from,to;
	Actor*aFrom, *aTo;
public:
	enum Type {
		None=0,GunFire, Bomb, DeepWaterBomb, Torpedo, SubmarineTorpedo,
	};
	Weapon();
	~Weapon();
	CREATE_FUNC(Weapon);
	static Weapon* create(FightScene*scene, const Vec2&from, const Vec2&to, Type type);
	bool initialize(FightScene*scene, const Vec2&from, const Vec2&to, Type type);

	void AnimTorpedo();

	void AnimGunfire();


};

