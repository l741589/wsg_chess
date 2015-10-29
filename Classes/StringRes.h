#pragma once

#include "util.h"

namespace G {
	extern rapidjson::Document StringRes;
	void initStringRes();
	std::string getString(const char* key);
	std::string getString(const std::string& key);
}
