#ifndef __H_GAMEOVER_CANDYCRUSH_SCENE_H__
#define __H_GAMEOVER_CANDYCRUSH_SCENE_H__

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class GameOver_CandyCrush : public Layer
{
public:

	/***** һЩ��ʼ������ *****/
	static Scene* createScene();
	CREATE_FUNC(GameOver_CandyCrush);
	virtual bool init();



	/***** ���ߺ��� *****/
	// ��ȡ��ǰ��Ϸ��õķ���
	void setScore(int sc);



	/***** ��ť�ķ��غ��� *****/
	void menuExitCallback(Ref *pSender);
	void menuRestartCallback(Ref *pSender);
	void menuBackCallback(Ref *pSender);
};




#endif //__H_GAMEOVER_CANDYCRUSH_SCENE_H__