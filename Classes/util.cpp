#include "util.h"

namespace util {
	Rect operator+(const Rect&l, const Vec2&r) {
		return Rect(l.origin + r, l.size);
	}

	Rect operator-(const Rect&l, const Vec2&r) {
		return Rect(l.origin - r, l.size);
	}

	Vec2 rotate(const Vec2&vec, float rad) {
		return{
			vec.x*cos(rad) - vec.y*sin(rad),
			vec.x*sin(rad) + vec.y*cos(rad)
		};
	}

	bool isPtInNode(const Vec2&pt, Node*node) {
		const Rect&r = node->getBoundingBox();		
		return r.containsPoint(pt);
	}

	bool isPtInNodeEventCallback(Touch*t, Event*e) {
		auto node=e->getCurrentTarget();
		return util::isPtInNode(node->getParent()->convertTouchToNodeSpaceAR(t), node);
	}

	void setScale9Background(Layout*layout, std::string file)
	{
		layout->setBackGroundImage(file);
		Size size = layout->getBackGroundImageTextureSize();
		layout->setBackGroundImageScale9Enabled(true);
		Size sp = { size.width / 2 - 1,size.height / 2 - 1 };
		layout->setBackGroundImageCapInsets({ sp,size - sp - sp });
	}

	void setLayoutParameter(Widget*ctrl,Margin margin,LinearLayoutParameter::LinearGravity gravity) {
		if (gravity == LinearLayoutParameter::LinearGravity::NONE) {
			auto lp = ctrl->getLayoutParameter();
			if (!lp) lp = LayoutParameter::create();
			lp->setMargin(margin);
			ctrl->setLayoutParameter(lp);
		}
		else {
			LinearLayoutParameter* lp =(LinearLayoutParameter*) ctrl->getLayoutParameter(LayoutParameter::Type::LINEAR);
			if (!lp) lp = LinearLayoutParameter::create();
			lp->setMargin(margin);
			lp->setGravity(gravity);
			ctrl->setLayoutParameter(lp);
		}
		
	}



	void __jsonSet(const char*&s, rapidjson::Value&val) {
		if (val.IsString()) {
			s = val.GetString();
		} else {
			char *buf = new char[16];
			if (val.IsDouble()) {
				sprintf(buf, "%g", val.GetDouble());
				s = buf;
			} else  if (val.IsInt()){
				sprintf(buf, "%d", val.GetDouble());
				s = buf;
			}
		}		
	}

	void __jsonSet(int&s, rapidjson::Value&val) {
		if (val.IsInt()) s = val.GetInt();
		else if (val.IsString()) s = atoi(val.GetString());
		else if(val.IsNumber()) s = (int)val.GetDouble();
	}

	void __jsonSet(float&s, rapidjson::Value&val) {
		if (val.IsInt()) s = val.GetInt();
		else if (val.IsString()) s = atof(val.GetString());
		else s = (float)val.GetDouble();
	}

	void __jsonSet(double&s, rapidjson::Value&val) {
		if (val.IsInt()) s = val.GetInt();
		if (val.IsString()) s = atof(val.GetString());
		else s = val.GetDouble();
	}

	void bindTouchEvent(Node*node, EventListenerTouchOneByOne::ccTouchBeganCallback onBegin, EventListenerTouchOneByOne::ccTouchCallback onMove, EventListenerTouchOneByOne::ccTouchCallback onEnd, EventListenerTouchOneByOne::ccTouchCallback onCancel /*= nullptr*/) {
		auto e=EventListenerTouchOneByOne::create();
		e->onTouchBegan = onBegin;
		e->onTouchMoved = onMove;
		e->onTouchEnded = onEnd;
		e->onTouchCancelled = onCancel;
		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(e, node);
	}

}
