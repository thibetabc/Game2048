#ifndef __H_GAMEOVER_H__
#define __H_GAMEOVER_H__
#include "cocos2d.h"
USING_NS_CC;

class GameOver : public Layer
{
public:
	GameOver();
	~GameOver();
	CREATE_FUNC(GameOver);
	bool init();
	static Scene *createScene();
public:

};

#endif 