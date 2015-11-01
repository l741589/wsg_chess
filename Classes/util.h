#pragma once
#include "stdafx.h"

#define READONLY_PROP(type,name) private: type _##name;public: type get##name(){return _##name;}

namespace util {
	USING_NS_CC;
	Rect operator+(const Rect&l, const Vec2&r);
	Rect operator-(const Rect&l, const Vec2&r);
	Vec2 rotate(const Vec2&vec, float rad);
	bool isPtInNode(const Vec2&pt, Node*node);
	bool isPtInNodeEventCallback(Touch*t, Event*e);
	void setScale9Background(Layout*layout,std::string file);
	void setLayoutParameter(Widget*ctrl, Margin margin, LinearLayoutParameter::LinearGravity gravity = LinearLayoutParameter::LinearGravity::NONE);


	void __jsonSet(const char*&s, rapidjson::Value&val);
	void __jsonSet(int&s, rapidjson::Value&val);
	void __jsonSet(float&s, rapidjson::Value&val);
	void __jsonSet(double&s, rapidjson::Value&val);
	void __jsonSet(std::set<int>&s, rapidjson::Value&val);

	template<class T = Node>
	T*find(Node*node, const char*name) {
		if (node->getName()==name) return (T*)node;
		for (auto e : node->getChildren()) {
			T*t=find<T>(e, name);
			if (t) return t;
		}
		return nullptr;
	}

	void bindTouchEvent(Node*node, EventListenerTouchOneByOne::ccTouchBeganCallback onBegin, EventListenerTouchOneByOne::ccTouchCallback onMove, EventListenerTouchOneByOne::ccTouchCallback onEnd, EventListenerTouchOneByOne::ccTouchCallback onCancel = nullptr);
}

#define JSON_SET(PROP) util::__jsonSet(this->PROP,json[#PROP]);