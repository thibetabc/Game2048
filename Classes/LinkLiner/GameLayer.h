//
//  GameLayer.h
//  LinkLinker
//
//  Created by jun on 13-8-20.
//
//

#ifndef __LinkLinker__GameLayer__
#define __LinkLinker__GameLayer__

#include "cocos2d.h"
class MapNode;

int compare(const void* a, const void* b);
class Game : public cocos2d::CCLayer
{
public:
    Game();
	~Game();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::Scene* scene();
    
    
    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Game);
private:
    cocos2d::Vec2 prePoint;
	int countCleared;
	cocos2d::Vector<MapNode*> arrayMap;
	int counter;
private:
    
    void initSound();
    void initData();
    void initView();
    cocos2d::String* imageFilename(int);
    
	void exitGame(float f);
    cocos2d::Vec2 pointOfView(cocos2d::Vec2 point);
    void showWin();
    void clearNode(cocos2d::Vec2 point);
    int indexFromPoint(cocos2d::Vec2 point);
    bool isSamePoints(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
    bool isValiableNode(cocos2d::Vec2 point);
    bool isEmptyNode(cocos2d::Vec2 point);
    bool canClearTwo(cocos2d::Vec2 pointpre, cocos2d::Vec2 pointcurrent);
    bool match_direct(cocos2d::Vec2 a, cocos2d::Vec2 b);
    bool match_one_corner(cocos2d::Vec2 a, cocos2d::Vec2 b);
    bool match_two_corner(cocos2d::Vec2 a, cocos2d::Vec2 b);
    bool match(cocos2d::Vec2 a,cocos2d::Vec2 b);
};


class MapNode : public cocos2d::Ref
{
public:
    int order;
    int imgid;
};

#endif /* defined(__LinkLinker__GameLayer__) */