#include "StringRes.h"

namespace G {
	rapidjson::Document StringRes;

	void initStringRes() {
		auto str = FileUtils::getInstance()->getStringFromFile("strings.json");
		StringRes.Parse(str.c_str());
	}

	std::string getString(const char* key) {
		return StringRes[key].GetString();
	}

	std::string getString(const std::string& key) {
		return StringRes[key.c_str()].GetString();
	}

	std::string getString(const char* key, int index)
	{
		return StringRes[key][index].GetString();
	}
}





