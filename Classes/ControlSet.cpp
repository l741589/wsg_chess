#include "ControlSet.h"

ControlSet*ControlSet::instance = nullptr;

ControlSet* ControlSet::getInstance() {
	if (!instance) instance = new ControlSet();
	return instance;
}


ControlSet::ControlSet() {
	root = CSLoader::createNode("ControlSet1.csb");
	root->retain();
}

ControlSet::~ControlSet() {
	root->release();
}
