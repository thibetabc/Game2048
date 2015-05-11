#ifndef __H_GAMESCENE_H__
#define __H_GAMESCENE_H__
#include "cocos2d.h"
#include "GameDefine.h"
#include "MoveTiled.h"

USING_NS_CC;

class GameScene:public Layer
{
public:
	GameScene();
	~GameScene();
	bool init();
	CREATE_FUNC(GameScene);
	static Scene *createScene();
	void moveAllTiled(MOVE_DIR dir);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void newMoveTiled();
	void removeMoveTiled(int row, int col);
	void gameOver();
public:
	LayerColor *m_bgColor;
	int m_map[GAME_ROWS][GAME_COLS]; //块的
	MOVE_DIR m_dir; //移动方向
	Vector<MoveTiled*> m_mtVector; //块的容器

	int m_moveX, m_moveY;
	int m_isMove;

	bool m_isSoundClear;//播放滑动声音还是得分声音
	int m_score;//得分

	bool m_isNewMoveTiled;//格子移动过，才重新生成新的格子


};


#endif