#pragma once

#include "util.h"
class Actor;

class FieldLayer : public cocos2d::Layer{
public:
	typedef std::function<void(Sprite*tile, const Vec2&pos)> onSelectedListener;
	typedef std::function<bool(const Vec2&)> VecFilter;
	CREATE_FUNC(FieldLayer);
	enum {TileSize=96,SrcTileSize=64};
	static Vec2 filedToLocal(Vec2 in) { return in*TileSize; }
	Sprite* createTile(Vec2 position, Color3B color, onSelectedListener listener);
	void createMoveTiles(Actor*actor, onSelectedListener listener);
	void createTiles(Vec2 start, int glen, VecFilter filter, Color3B color, onSelectedListener listener);
	void clear();
};