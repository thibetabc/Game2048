#ifndef __H_CAPTURESCREEN_H__
#define __H_CAPTURESCREEN_H__
#include "cocos2d.h"
USING_NS_CC;
class captureScreen : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();
	CREATE_FUNC(captureScreen);
	void captureEvent(Ref *pSender);
	void afterCaptureScreen(bool issuccess, const std::string &filename);
	void capturesc(std::string &filename);
};
#endif