#ifndef __OPENINGANIMATION_SCENE_H__
#define __OPENINGANIMATION_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class OpeningAnimation : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuCloseCallback(Ref* sender);

	// implement the "static node()" method manually
	CREATE_FUNC(OpeningAnimation);

	void doTrans(float dt);
	static std::vector<std::string> sResVector;
	static bool sResReady;
	static unsigned int sIndex;
};

#endif // __OPENINGANIMATION_SCENE_H__
