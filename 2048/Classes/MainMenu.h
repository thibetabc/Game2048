#ifndef __H_MENU_H__
#define __H_MENU_H__
#include "cocos2d.h"
USING_NS_CC;
class MainMenu : public Layer
{
public:
	bool init();
	CREATE_FUNC(MainMenu);
	static Scene *createScene();
	void jumpToGame(float f);
public:
protected:
private:
};
#endif