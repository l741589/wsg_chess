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
		const Vec2&anchor = node->getAnchorPoint();
		const Vec2&pos = node->getPosition();
		const Size&size = node->getContentSize();
		Vec2 start = {
			pos.x - anchor.x*size.width,
			pos.y - anchor.y*size.height
		};
		Rect r = { start, size };
		return r.containsPoint(pt);
	}

	bool isPtInNodeEventCallback(Touch*t, Event*e) {
		return util::isPtInNode(t->getLocation(), e->getCurrentTarget());
	}

}
