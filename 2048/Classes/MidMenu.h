#ifndef __H_MIDMENU_H__
#define __H_MIDMENU_H__
#include "cocos2d.h"
USING_NS_CC;

class MidMenu : public Layer
{
public:
	MidMenu();
	~MidMenu();
	CREATE_FUNC(MidMenu);
	bool init();
	static Scene *createScene();
	void menu(Ref *pSender);
public:

};



#endif