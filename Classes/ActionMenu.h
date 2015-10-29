#pragma once

#include "util.h"

class ActionMenu : public VBox {
private:
	std::vector<Button*> buttons;
	Button* addButton(std::string text, std::function<void(Ref*)>callback);
public:
	CREATE_FUNC(ActionMenu);
	bool show(Vec2 psoition,std::string title, std::list<std::pair<std::string, std::function<void(Ref*)> > > items);
	
	bool init() override;

};