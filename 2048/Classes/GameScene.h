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
	int m_map[GAME_ROWS][GAME_COLS]; //���
	MOVE_DIR m_dir; //�ƶ�����
	Vector<MoveTiled*> m_mtVector; //�������

	int m_moveX, m_moveY;
	int m_isMove;

	bool m_isSoundClear;//���Ż����������ǵ÷�����
	int m_score;//�÷�

	bool m_isNewMoveTiled;//�����ƶ����������������µĸ���


};


#endif