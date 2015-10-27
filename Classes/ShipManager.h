#pragma once
#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"

namespace Skin {
	namespace Ship {
		const char Default[] = "default";
		const char Damage[] = "normal";
		const char Normal[] = "normal";
	}
}

namespace Anim {
	namespace Ship {
		const char Antiaircraft[] = "Antiaircraft";
		const char Attack[] = "attack";
		const char Damage[] = "damage";
		const char Normal[] = "normal";
		const char Throw[] = "throw";
		const char Wreck[] = "wreck";
	}	
}

class ShipManager {
private:
	static ShipManager*instance;
public:
	static ShipManager*getInstance();

	spine::SkeletonAnimation*createActor(int id);

};