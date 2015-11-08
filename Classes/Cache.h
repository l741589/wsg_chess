#pragma once
#include "util.h"

class Cache {
private:
	std::list<std::string> preloadList;
	std::list<std::string>::iterator iter;

	void onLoad(Texture2D*) {
		if (iter == preloadList.end()) return;
		CCLOG("load texture: %s", iter->c_str());
		TextureCache::getInstance()->addImageAsync(*iter++, [this](Texture2D*t) {this->onLoad(t); });
	}

	void preload() {
		auto str = FileUtils::getInstance()->getStringFromFile("pngs.txt");
		auto ss = str.c_str();
		char buf[128];
		char space[128];
		int start = 0;
		while (sscanf(ss + start, "%[,\r\t\n ]%s", space, buf)) {
			preloadList.push_back(buf);
			start += strlen(space) + strlen(buf);
		}
		iter = preloadList.begin();
		onLoad(nullptr);
	}

	std::map<std::string, spSkeletonData*> skeletonData;
public:
	Cache() {
		G::cache = this;
	}

	spine::SkeletonAnimation*createSkeletonAnimation(const char*name,float scale=1.0f) {
		spSkeletonData*data = nullptr;
		if (skeletonData.find(name)!=skeletonData.end()) {
			data = skeletonData[name];
		} else {
			auto _atlas = spAtlas_createFromFile(G::format("%s.atlas", name), 0);
			CCASSERT(_atlas, "Error reading atlas file.");
			spSkeletonJson* json = spSkeletonJson_create(_atlas);
			json->scale = scale;
			data = spSkeletonJson_readSkeletonDataFile(json, G::format("%s.json", name));
			CCASSERT(data, json->error ? json->error : "Error reading skeleton data file.");
			spSkeletonJson_dispose(json);
			skeletonData[name] = data;
		}
		if (data == nullptr) return nullptr;
		return spine::SkeletonAnimation::createWithData(data);
	}
};