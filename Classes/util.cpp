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

}
