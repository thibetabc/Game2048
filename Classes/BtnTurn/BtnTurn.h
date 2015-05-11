#ifndef __BTN_TURN_H__
#define __BTN_TURN_H__

#include "cocos2d.h"

USING_NS_CC;

enum BtnPos
{
	Pos_Bottom = 1,
	Pos_Left,
	Pos_Top,
	Pos_Right,
};


class BtnTurn : public cocos2d::Layer
{
public:
	BtnTurn();
	~BtnTurn();

	virtual bool init();
	CREATE_FUNC(BtnTurn)

protected:
	virtual bool onTouchBegan(Touch* touch, Event* pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	//�����ť֮��Ķ���
	void runTouchedAmt(Sprite * btn);
	//��������Ķ���
	void runSlidedAmt(bool isLeft,float ratio,float judgePosX);
private:
	Sprite * m_btn1;
	Sprite * m_btn2;
	Sprite * m_btn3;
	Sprite * m_btn4;

	Vec2 m_posBottom;
	Vec2 m_posLeft;
	Vec2 m_posTop;
	Vec2 m_posRight;

	Point m_firstPos;
	
	Size m_winSize;
	bool m_valid;//�ȵ����Ч����
	bool m_invalid;//�ȵ����Ч����
	
};

#endif