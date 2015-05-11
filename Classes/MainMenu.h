#ifndef __H_MENU_H__
#define __H_MENU_H__
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class MainMenu : public Layer
{
public:
	bool init();
	CREATE_FUNC(MainMenu);
	static Scene *createScene();
	void jumpToGame(float f);
	void menuCallback(Ref *pSender);//C:\Program Files (x86)\Visual Leak Detector
public:
protected:
private:
};
#endif