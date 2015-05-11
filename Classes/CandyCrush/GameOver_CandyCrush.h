#ifndef __H_GAMEOVER_CANDYCRUSH_SCENE_H__
#define __H_GAMEOVER_CANDYCRUSH_SCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class GameOver_CandyCrush : public Layer
{
public:

	/***** 一些初始化函数 *****/
	static Scene* createScene();
	CREATE_FUNC(GameOver_CandyCrush);
	virtual bool init();



	/***** 工具函数 *****/
	// 获取当前游戏获得的分数
	void setScore(int sc);



	/***** 按钮的返回函数 *****/
	void menuExitCallback(Ref *pSender);
	void menuRestartCallback(Ref *pSender);
	void menuBackCallback(Ref *pSender);
};




#endif //__H_GAMEOVER_CANDYCRUSH_SCENE_H__