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
	typedef std::function<void(Sprite*tile, const Vec2&pos)> onSelectedListener;
	typedef std::function<bool(const Vec2&)> VecFilter;
	CREATE_FUNC(FieldLayer);
	bool init() override;
	enum {TileSize=96,SrcTileSize=64};
	static Vec2 filedToLocal(Vec2 in) { return{ in.x*TileSize + TileSize / 2,in.y*TileSize + TileSize / 2 }; }
	FieldTile* createTile(Vec2 position, int index, Color3B color, onSelectedListener listener);
	void createMoveTiles(Actor*actor, onSelectedListener listener);
	void createTiles(Vec2 start, int glen, VecFilter filter, Color3B color, onSelectedListener listener);
	void clear();
};