#include "LayoutInflater.h"
#include<string.h>
#include <map>
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;
typedef rapidjson::Value V;
V NullValue;

Node* inflate(V& v);

Node* LayoutInflater::inflate(std::string filename)
{
	std::string s = FileUtils::getInstance()->getStringFromFile(filename);
	rapidjson::Document doc;
	doc.Parse(s.c_str());
	return inflate(doc);
}



Node* LayoutInflater::inflate(rapidjson::Value& v)
{
	return ::inflate(v);
}
namespace lf {
	typedef const char* String;
	typedef bool True;
	typedef bool False;
	typedef int Int;
	typedef unsigned int Uint;
	typedef int64_t Int64;
	typedef uint64_t Uint64;
	typedef nullptr_t Null;
	typedef double Double;
}

#define U2I(ch) (ch>='0'&&ch<='9'?ch-'0': ch>='A'&&ch<='Z'?ch-'A'+10 : ch>='a'&&ch<='z'?ch-'a'+10 : -1)
#define ATTR(NAME,TYPE) lf::TYPE NAME;bool _has##NAME=false; if (v.HasMember(#NAME)) { V& _##NAME=v[#NAME]; if (_##NAME.Is##TYPE()) { NAME=_##NAME.Get##TYPE(); _has##NAME=true;}} if (_has##NAME)
#define OBJATTR(NAME,TYPE) V& NAME=v.HasMember(#NAME)?v[#NAME]:NullValue; if (NAME.Is##TYPE()) 
#define FUNC(TYPE) bool create(TYPE*w, V&v)


Rect parseRect(const char*s) {
	float l, r, t, b;
	int c=sscanf(s, "%f,%f,%f,%f", &l, &t, &r, &b);
#ifdef CC_PLATFORM_WIN32
	if (c == 1) return { l,l,l,l };
	else if (c == 2) return { l,t,l,t };
	else if (c == 4) return { l,t,r,b };
	else return { 0,0,0,0 };
#else
	return Rect{ l,r,t,b };
#endif // CC_PLATFORM_WIN32
}

Vec2 parseVec2(const char*s) {
	float x, y;
	int c = sscanf(s, "%f,%f", &x, &y);
	return { x,y };
}


Color4B parseColor(const char*s) {
	if (s[0] == '#') {
		int l = strlen(s);
		if (l == 9) {
			int a = U2I(s[1]) * 16 + U2I(s[2]);
			int r = U2I(s[3]) * 16 + U2I(s[4]);
			int g = U2I(s[5]) * 16 + U2I(s[6]);
			int b = U2I(s[7]) * 16 + U2I(s[8]);
			return Color4B(a,r, g, b);
		}
		else if (l == 7) {
			int r = U2I(s[1]) * 16 + U2I(s[2]);
			int g = U2I(s[3]) * 16 + U2I(s[4]);
			int b = U2I(s[5]) * 16 + U2I(s[6]);
			return Color4B(255,r, g, b);
		}
		else {
			return Color4B::BLACK;
		}
	}
	else {
		return Color4B::BLACK;
	}
}


FUNC(Node) {
	if (v.GetType() != rapidjson::Type::kObjectType) return false;
	ATTR(name,String) w->setName(name);
	OBJATTR(content,Array) {
		int count=content.Size();
		for (int i = 0; i < count; ++i) {
			auto e=inflate(content[i]);
			if (e) w->addChild(e);
		}
	}
	ATTR(size, String) {
		if (strcmp(size, "auto")==0) {
			Rect r = Rect::ZERO;
			for (Node*n : w->getChildren()) {
				r=r.unionWithRect(n->getBoundingBox());
			}
			w->setContentSize(r.size);
		}
		else {
			w->setContentSize(Size(parseVec2(size)));
		}
	}
	return true;
}

FUNC(Widget) {
	if(!create((Node*)w, v)) return false;
	ATTR(margin, String) {
		Rect r = parseRect(margin);
		LayoutParameter* lp = w->getLayoutParameter();
		if (lp == nullptr) lp = LayoutParameter::create();
		lp->setMargin(Margin(r.origin.x, r.origin.y, r.size.width, r.size.height));
		w->setLayoutParameter(lp);
	}

	ATTR(gravity, String) {
		LayoutParameter* lp = w->getLayoutParameter();
		if (lp == nullptr) lp = LinearLayoutParameter::create();
		if (lp->getLayoutType() != LayoutParameter::Type::LINEAR) {
			auto p= LinearLayoutParameter::create();
			p->setMargin(lp->getMargin());
			lp = p;
		}
		LinearLayoutParameter::LinearGravity g = LinearLayoutParameter::LinearGravity::NONE;
		if (strchr(gravity, 'l')) g = LinearLayoutParameter::LinearGravity::LEFT;
		if (strchr(gravity, 'r')) g = LinearLayoutParameter::LinearGravity::RIGHT;
		if (strchr(gravity, 't')) g = LinearLayoutParameter::LinearGravity::TOP;
		if (strchr(gravity, 'b')) g = LinearLayoutParameter::LinearGravity::BOTTOM;
		if (strchr(gravity, 'h')) g = LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL;
		if (strchr(gravity, 'v')) g = LinearLayoutParameter::LinearGravity::CENTER_VERTICAL;
		((LinearLayoutParameter*)lp)->setGravity(g);
		w->setLayoutParameter(lp);
	}
	return true;
}

FUNC(Layout) {
	if (!create((Widget*)w, v)) return false;
	ATTR(background,String) {
		if (background[0] == '#') {
			w->setBackGroundImageColor(Color3B(parseColor(background)));
			ATTR(backgroundOpacity,Int) w->setBackGroundColorOpacity(backgroundOpacity);
		}
		else {
			w->setBackGroundImage(background);
			ATTR(backgroundOpacity,Int) w->setBackGroundImageOpacity(backgroundOpacity);
		}
		
	}
	ATTR(scale9,String) {
		w->setBackGroundImageScale9Enabled(true);
		w->setBackGroundImageCapInsets(parseRect(scale9));		
	}	
	return true;
}

FUNC(Text) {
	if (!create((Widget*)w, v)) return false;
	ATTR(text, String) w->setString(text);
	ATTR(font, String) w->setFontName(font);
	ATTR(fontSize, Double) w->setFontSize((float)fontSize);
	ATTR(textSize, Double) w->setFontSize((float)fontSize);
	ATTR(textColor, String) w->setTextColor(parseColor(textColor));
	return true;
}

FUNC(Button) {
	if (!create((Widget*)w, v)) return false;
	ATTR(text, String) w->setTitleText(text);
	ATTR(font, String) w->setTitleFontName(font);
	ATTR(fontSize, Double) w->setTitleFontSize((float)fontSize);
	ATTR(textSize, Double) w->setTitleFontSize((float)textSize);
	ATTR(textColor, String) w->setTitleColor(Color3B(parseColor(textColor)));
	ATTR(texDisable, String) w->loadTextureDisabled(texDisable);
	ATTR(texNormal, String) w->loadTextureNormal(texNormal);
	ATTR(texPressed, String) w->loadTexturePressed(texPressed);
	return true;
}

template<class T>
T*create(V&v) {
	T*t = T::create();
	if (!create(t, v)) return nullptr;
	return t;
}

#define CREATOR(TYPE) {#TYPE, create<TYPE> }
std::map<std::string, std::function<Node*(V&)> > worker = {
	CREATOR(Widget),CREATOR(HBox),CREATOR(VBox),CREATOR(Button),CREATOR(Node),CREATOR(Sprite)
};

Node* inflate(V& v) {
	const char*type = v["type"].GetString();
	CCLOG("inflate type:%s", type);
	return worker[type](v);
}