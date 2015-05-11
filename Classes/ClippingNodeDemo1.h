#ifndef __H_CLIPPINGNODEDEMO1_H__
#define __H_CLIPPINGNODEDEMO1_H__
#include "cocos2d.h"

USING_NS_CC;

class ClippingNodeDemo1 : public Layer
{
public:
	enum class State
	{
		idle,
		playing,
	};
public:
	ClippingNodeDemo1();
	~ClippingNodeDemo1();
	CREATE_FUNC(ClippingNodeDemo1);
	static Scene *createScene();
	bool init();
	void show(std::string);
	void addMessage(const std::string text);
public:
	CC_SYNTHESIZE(std::string, m_font, Font);
	CC_SYNTHESIZE(float, m_fontSize, FontSize);
	CC_SYNTHESIZE(Rect, m_showRect, ShowRect);
	CC_SYNTHESIZE(State, m_state, State);

private:
	std::queue<std::string> _texts;
	Label *m_label;
	int m_count;

};

#endif
