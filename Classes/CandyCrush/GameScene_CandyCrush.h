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
	// 返回欢迎界面函数  
	void menuBackCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameScene_CandyCrush);

	void initMap();
	void createSprite(int row, int col);
	cocos2d::Vec2 positionOfItem(int row, int col);
	/***** 检查移除填补相关 *****/
	// 检测是否有可消除精灵
	void checkAndRemoveSprite();
	// 标记可以移除的精灵  
	void markRemove(SpriteShape_CandyCrush *spr);
	// 移除精灵 
	void removeSprite();
	// 精灵的爆炸移除  
	void explodeSprite(SpriteShape_CandyCrush *spr);
	// 精灵的横向消除  
	void explodeSpecialH(Vec2 vec2);
		// 精灵的纵向消除  
	void explodeSpecialV(Vec2 vec2);
	// 对移除的精灵进行的操作  
	void actionEndCallback(Node *node);
	// 纵向检查  
	void getColChain(SpriteShape_CandyCrush *spr, std::list<SpriteShape_CandyCrush *> &chainList);
	// 横向检查  
	void getRowChain(SpriteShape_CandyCrush *spr, std::list<SpriteShape_CandyCrush *> &chainList);
	// 填补空缺  
	void fillSprite();

	// 根据触摸的点位置，返回是地图中哪个精灵
	SpriteShape_CandyCrush *spriteOfPoint(cocos2d::Vec2 *vec2);
	void swapSprite();
	void myClock(float ft);
	void gameOver(float f);

	void onEnterTransitionDidFinish();
	void onExit();

private:

	/***** 全局重要变量 *****/
	// 地图二维数组
	SpriteShape_CandyCrush* map[ROWS][COLS];
	// 源精灵，目标精灵
	SpriteShape_CandyCrush* staSprite;
	SpriteShape_CandyCrush* endSprite;
	// 时间
	int m_time;
	// 分数
	int m_score;



	/***** 工具变量 *****/
	// 绘制一批图片
	SpriteBatchNode* spriteSheet;
	// 绘图的最下角坐标位置
	float mapLBX, mapLBY;



	/***** 标志变量 ****/
	// 标志 是否在执行动作
	bool isAction;
	// 标志 是否有空缺需要填补
	bool isFillSprite;
	// 标志 是否可以触摸
	bool isTouchEna;
	// 标志 产生的四消精灵是否为横向
	bool isRow;
};

#endif // __GAMESCENE_CANDYCRUSH_H__ 