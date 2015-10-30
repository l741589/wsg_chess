#pragma once

#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"
#include <string>
#include <list>
#include <vector>


class LayoutInflater {
public:
	static cocos2d::Node*inflate(std::string filename);
	static cocos2d::Node*inflate(rapidjson::Value& doc);
};