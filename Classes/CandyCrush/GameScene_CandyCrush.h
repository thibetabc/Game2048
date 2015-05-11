#ifndef __GAMESCENE_CANDYCRUSH_H__  
#define __GAMESCENE_CANDYCRUSH_H__  
#include "cocos2d.h"  
#include "GameDefine.h"
#include "SpriteShape_CandyCrush.h"

USING_NS_CC;
class GameScene_CandyCrush : public cocos2d::Layer
{
public:
	GameScene_CandyCrush();
	~GameScene_CandyCrush();
	static cocos2d::Scene* createScene();
	virtual bool init();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void update(float dt);
	// ���ػ�ӭ���溯��  
	void menuBackCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameScene_CandyCrush);

	void initMap();
	void createSprite(int row, int col);
	cocos2d::Vec2 positionOfItem(int row, int col);
	/***** ����Ƴ����� *****/
	// ����Ƿ��п���������
	void checkAndRemoveSprite();
	// ��ǿ����Ƴ��ľ���  
	void markRemove(SpriteShape_CandyCrush *spr);
	// �Ƴ����� 
	void removeSprite();
	// ����ı�ը�Ƴ�  
	void explodeSprite(SpriteShape_CandyCrush *spr);
	// ����ĺ�������  
	void explodeSpecialH(Vec2 vec2);
		// �������������  
	void explodeSpecialV(Vec2 vec2);
	// ���Ƴ��ľ�����еĲ���  
	void actionEndCallback(Node *node);
	// ������  
	void getColChain(SpriteShape_CandyCrush *spr, std::list<SpriteShape_CandyCrush *> &chainList);
	// ������  
	void getRowChain(SpriteShape_CandyCrush *spr, std::list<SpriteShape_CandyCrush *> &chainList);
	// ���ȱ  
	void fillSprite();

	// ���ݴ����ĵ�λ�ã������ǵ�ͼ���ĸ�����
	SpriteShape_CandyCrush *spriteOfPoint(cocos2d::Vec2 *vec2);
	void swapSprite();
	void myClock(float ft);
	void gameOver(float f);

	void onEnterTransitionDidFinish();
	void onExit();

private:

	/***** ȫ����Ҫ���� *****/
	// ��ͼ��ά����
	SpriteShape_CandyCrush* map[ROWS][COLS];
	// Դ���飬Ŀ�꾫��
	SpriteShape_CandyCrush* staSprite;
	SpriteShape_CandyCrush* endSprite;
	// ʱ��
	int m_time;
	// ����
	int m_score;



	/***** ���߱��� *****/
	// ����һ��ͼƬ
	SpriteBatchNode* spriteSheet;
	// ��ͼ�����½�����λ��
	float mapLBX, mapLBY;



	/***** ��־���� ****/
	// ��־ �Ƿ���ִ�ж���
	bool isAction;
	// ��־ �Ƿ��п�ȱ��Ҫ�
	bool isFillSprite;
	// ��־ �Ƿ���Դ���
	bool isTouchEna;
	// ��־ ���������������Ƿ�Ϊ����
	bool isRow;
};

#endif // __GAMESCENE_CANDYCRUSH_H__ 