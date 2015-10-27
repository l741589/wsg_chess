#pragma once

#include "cocos2d.h"
#include "util.h"
#include "GameData.h"

class Ship {
	friend class GameData;
	READONLY_PROP(int, Id);
	READONLY_PROP(float, TurningRaduis);
	READONLY_PROP(float, Speed);
	READONLY_PROP(std::string, Name);
};