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



}
