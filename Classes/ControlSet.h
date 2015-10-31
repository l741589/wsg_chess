#pragma once
#include "util.h"

class ControlSet {
private:
	static ControlSet*instance;
	std::map<std::string, Node*> ctrls;
	Node* root;
	ControlSet();
	~ControlSet();
public:
	static ControlSet*getInstance();
	template<class T = Widget>
	T*create(const char* name) {
		if (ctrls.find(name)) return ctrls[name];
		auto e = util::find<T>(root, name);
		if (e) ctrls[name] = e;
		return e->clone();
	}
};