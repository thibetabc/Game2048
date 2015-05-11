#ifndef __H_WELCOMESCENE_CANDYCRUSH_H__
#define __H_WELCOMESCENE_CANDYCRUSH_H__
#include "cocos2d.h"


USING_NS_CC;

class WelcomeScene_CandyCrush:public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	void menuStartCallback(Ref* pSender);
	CREATE_FUNC(WelcomeScene_CandyCrush);
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
};

#endif //__H_WELCOMESCENE_CANDYCRUSH_H__