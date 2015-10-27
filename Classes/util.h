#pragma once
#include "cocos2d.h"
#include "spine/spine-cocos2dx.h"
#include "spine/extension.h"
#include<stdio.h>
#include<map>
#include<string>
#include<list>
#include<vector>
#include<set>


USING_NS_CC;

#define READONLY_PROP(type,name) private: type _##name;public: type get##name(){return _##name;}

namespace util {
	USING_NS_CC;
	Rect operator+(const Rect&l, const Vec2&r);
	Rect operator-(const Rect&l, const Vec2&r);
	Vec2 rotate(const Vec2&vec, float rad);
	bool isPtInNode(const Vec2&pt, Node*node);
	bool isPtInNodeEventCallback(Touch*t, Event*e);;
}