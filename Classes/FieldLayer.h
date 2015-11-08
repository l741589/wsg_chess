#pragma once

#include "util.h"
class Actor;

class FieldTile : public Sprite {
public:
	CREATE_FUNC(FieldTile);
	bool init() override {
		return Sprite::initWithFile("field_rect.png");
	}
	bool enable = true;
	int index;
};

class ColorF4B : public Color4B {
public:
	enum Flag {
		DISABLE = 0, 
		ALLOW = 1, 
		SHOW = 2
	};
	int f;
	ColorF4B(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) :Color4B(_r, _g, _b, _a),f(ALLOW|SHOW) {};
	explicit ColorF4B(const Color3B& color) :Color4B(color), f(ALLOW | SHOW) {}
	ColorF4B(const Color4F& color) :Color4B(color), f(ALLOW | SHOW) {}
	ColorF4B(GLubyte _r, GLubyte _g, GLubyte _b) :Color4B(_r, _g, _b, 255), f(ALLOW | SHOW) {};
	ColorF4B(Flag flag):f(flag){}
	ColorF4B withAlpha(GLubyte a) const { ColorF4B c(*this); c.a = a; return c; }
};

class FieldLayer : public cocos2d::Node{
public:	
	typedef std::function<void(Sprite*tile, const Vec2&pos)> onSelectedListener;
	typedef std::function<ColorF4B(const Vec2&,const Vec2&)> VecFilter;
	CREATE_FUNC(FieldLayer);
	bool init() override;
	enum {TileSize=96,SrcTileSize=64};
	static Vec2 fieldToLocal(Vec2 in) { return{ in.x*TileSize + TileSize / 2,in.y*TileSize + TileSize / 2 }; }
	static Vec2 localToField(Vec2 in) { return Vec2{ floorf(in.x / TileSize), floorf(in.y / TileSize) }; }
	static Vec2 fixLocal(Vec2 in) {return fieldToLocal(localToField(in));}
	FieldTile* createTile(Vec2 position, int index, Color4B color, onSelectedListener listener);
	Node* createTiles(Actor* actor, VecFilter filter, onSelectedListener listener);
	void clear(Node*group=nullptr, float time = 0.5f);

public:
	void createMoveTiles(Actor*actor, onSelectedListener listener);
};