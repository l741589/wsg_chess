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

class FieldLayer : public cocos2d::Node{
public:
	enum{DISABLE=0,DISABLE_BUT_ALLOW=0x01000000};
	typedef std::function<void(Sprite*tile, const Vec2&pos)> onSelectedListener;
	typedef std::function<int(const Vec2&,const Vec2&)> VecFilter;
	CREATE_FUNC(FieldLayer);
	bool init() override;
	enum {TileSize=96,SrcTileSize=64};
	static Vec2 fieldToLocal(Vec2 in) { return{ in.x*TileSize + TileSize / 2,in.y*TileSize + TileSize / 2 }; }
	static Vec2 localToField(Vec2 in) { return Vec2{ floorf(in.x / TileSize), floorf(in.y / TileSize) }; }
	static Vec2 fixLocal(Vec2 in) {return fieldToLocal(localToField(in));}
	FieldTile* createTile(Vec2 position, int index, Color4B color, onSelectedListener listener);
	void createTiles(Actor* actor, VecFilter filter, onSelectedListener listener);
	void clear();

public:
	void createMoveTiles(Actor*actor, onSelectedListener listener);
};