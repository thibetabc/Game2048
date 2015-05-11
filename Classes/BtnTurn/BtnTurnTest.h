#ifndef _BTN_TURN_TEST_
#define _BTN_TURN_TEST_

#include "cocos2d.h"

USING_NS_CC;

class BtnTurnTest : public Layer
{
public:
	BtnTurnTest();
	~BtnTurnTest();

	static cocos2d::Scene * create();
	virtual bool init();

};

#endif