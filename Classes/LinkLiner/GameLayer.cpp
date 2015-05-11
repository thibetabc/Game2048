//
//  GameLayer.cpp
//  LinkLinker
//
//  Created by jun on 13-8-20.
//
//

#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"

using namespace CocosDenshion;
#define TAG_START_SPRITE                    100
#define TAG_LABEL_CONNER                    501
#define TAG_LABEL_NUMBER                    502
#define OFFSET_X							-40
#define OFFSET_Y							60
#define SIZE_W								40
#define SIZE_H								40
#define TOTAL_X								10
#define TOTAL_Y								10
#define TOTAL_IMG							16
#define MAX_CLEARED                         24


static int imgMap[64] = {
    1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 ,
    5 , 5 , 5 , 5 , 6 , 6 , 0 , 0 ,
    7 , 7 , 7 , 7 , 8 , 8 , 0 , 0 ,
    9 , 9 , 9 , 9 , 10, 10, 10, 10,
    11, 11, 11, 11, 12, 12, 12, 12,
    13, 13, 13, 13, 14, 14, 14, 14,
	15, 15, 16, 16, 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
};

using namespace cocos2d;
using namespace CocosDenshion;

Scene* Game::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    Game *layer = Game::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


Game::~Game()
{
		arrayMap.clear();
    
    
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

Game::Game(): prePoint(Vec2::ZERO)
,counter(0)
,countCleared(0)
{
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->initSound();
    this->initData();
    this->initView();
     
    return true;
}

void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Game::initSound()
{
   //SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);
   SimpleAudioEngine::getInstance()->playBackgroundMusic("LinkLiner/back2.mp3", true);
}

void Game::initData()
{
	prePoint = CCPointMake(-1, -1);
	countCleared = 0;
	counter = 0;
	//cocos2d::CCArray *array = cocos2d::CCArray::create();
	Vector<MapNode*>array;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < (TOTAL_X - 2) * (TOTAL_Y - 2); ++i) {
		MapNode *mapnode = new MapNode();
        mapnode->autorelease();
		mapnode->order = (int)(CCRANDOM_0_1() * INT_MAX) % (int)(CCRANDOM_0_1() * INT_MAX);
		mapnode->imgid = imgMap[i];
        array.pushBack(mapnode);
	}
    
//	qsort(array.at(0), array.size(), sizeof(long), compare);
	
	for (int x = 0; x < TOTAL_X; ++x) {
		for (int y = 0; y < TOTAL_Y; ++y) {
			if (x == 0 || x == (TOTAL_X - 1) || y == 0 || (y == TOTAL_Y - 1)) {
				MapNode *mapnode = new MapNode();
                mapnode->autorelease();
				mapnode->order = 0;
				mapnode->imgid = 0;
                this->arrayMap.pushBack(mapnode);
			} else {
				int i = (y - 1) * (TOTAL_Y - 2) + x - 1;
				this->arrayMap.pushBack(array.at(i));
			}
		}
	}
}


void Game::initView()
{
	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [&](Touch *pTouch, Event*event)
	{
		Vec2 ptouch = pTouch->getLocation();
		if (ptouch.x > 250 && ptouch.y > 420) {
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			this->schedule(schedule_selector(Game::exitGame), 0);
			return true;
		}

		Vec2 pointcurrent = this->pointOfView(pTouch->getLocationInView());

		if (this->isValiableNode(pointcurrent) == false) {
			return false;
		}

		if (this->isEmptyNode(pointcurrent)) {
			return false;
		}
		SimpleAudioEngine::getInstance()->playEffect("LinkLiner/choose.wav");

		if (this->isSamePoints(pointcurrent, prePoint)) {
			return false;
		}

		Sprite *spritecurrent = (Sprite *)this->getChildByTag(TAG_START_SPRITE + this->indexFromPoint(pointcurrent));

		spritecurrent->setScale(0.6);

		if (this->isValiableNode(prePoint)) {
			Sprite *spritepre = (Sprite *)this->getChildByTag(TAG_START_SPRITE + this->indexFromPoint(prePoint));
			if (this->canClearTwo(prePoint, pointcurrent)) {
				SimpleAudioEngine::getInstance()->playEffect("LinkLiner/disappear1.wav");
				this->clearNode(prePoint);
				this->clearNode(pointcurrent);
				spritepre->setVisible(false);
				spritecurrent->setVisible(false);
				if (++countCleared >= MAX_CLEARED) {
					SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
					SimpleAudioEngine::getInstance()->playEffect("LinkLiner/win.mp3");
					this->showWin();
				}
				LabelTTF *label = (LabelTTF *)this->getChildByTag(TAG_LABEL_CONNER);
				cocos2d::String *str = String::createWithFormat("Loading:%d%%", (int)(countCleared * 100 / MAX_CLEARED));
				label->setString(str->getCString());
			}
			else {
				spritepre->setScale(0.5);
			}
		}

		prePoint = pointcurrent;
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    Size size = Director::getInstance()->getWinSize();
    
	Sprite *background = Sprite::create("LinkLiner/bg.png");
    background->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(background);
    ;
	for (int y = 0; y < TOTAL_Y; ++y) {
		for (int x = 0; x < TOTAL_X; ++x) {
			int index = y * TOTAL_Y + x;
            if(this->imageFilename(index)){
                Sprite *sprite = Sprite::create(this->imageFilename(index)->getCString());
                sprite->setScale(0.5f);
                sprite->setPosition(ccp(OFFSET_X + (SIZE_W / 2) + SIZE_W * x, OFFSET_Y + (SIZE_H / 2) + SIZE_H * y));
                this->addChild(sprite, 0, (TAG_START_SPRITE + index));
            }
		}
	}
	
	Sprite *button = Sprite::create("LinkLiner/play.png");
    button->setPosition(ccp(size.width - 55, 25));
	this->addChild(button);
	
	LabelTTF *label = LabelTTF::create("进度:0%", "Arial", 20.0);
	label->setPosition(ccp(50, 15));
    this->addChild(label,0,TAG_LABEL_CONNER);
	
	LabelTTF *labelnum1 = LabelTTF::create("1", "Marker Felt", 64.0);
    labelnum1->setPosition(ccp( size.width /2 , size.height/2 ));
	this->addChild(labelnum1);
    
	LabelTTF *labelnum2 = LabelTTF::create("2", "Marker Felt", 64.0);
    labelnum2->setPosition(ccp( size.width /2 , size.height/2 ));
    labelnum2->setVisible(false);
	this->addChild(labelnum2);
    
    LabelTTF *labelnum3 = LabelTTF::create("3", "Marker Felt", 64.0);
    labelnum3->setPosition(ccp( size.width /2 , size.height/2 ));
    labelnum3->setVisible(false);
	this->addChild(labelnum3);
    
    LabelTTF *labelnum4 = LabelTTF::create("Go", "Marker Felt", 64.0);
    labelnum4->setPosition(ccp( size.width /2 , size.height/2 ));
    labelnum4->setVisible(false);
	this->addChild(labelnum4);
    
    void* ac1a = labelnum1->runAction(cocos2d::Show::create());
	void* ac1b = labelnum1->runAction(cocos2d::ScaleBy::create(0.5, 2.0));
    void* ac1c = labelnum1->runAction(cocos2d::Hide::create());
    
    void* ac2a = labelnum2->runAction(cocos2d::Show::create());
	void* ac2b = labelnum2->runAction(cocos2d::ScaleBy::create(0.5, 2.0));
    void* ac2c = labelnum2->runAction(cocos2d::Hide::create());
    
    void* ac3a = labelnum3->runAction(cocos2d::Show::create());
	void* ac3b = labelnum3->runAction(cocos2d::ScaleBy::create(0.5, 2.0));
    void* ac3c = labelnum3->runAction(cocos2d::Hide::create());
    
    
    void* ac4a = labelnum4->runAction(cocos2d::Show::create());
	void* ac4b = labelnum4->runAction(cocos2d::ScaleBy::create(0.5, 2.0));
    void* ac4c = labelnum4->runAction(cocos2d::Hide::create());
    
    labelnum1->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(0.5),ac1a,ac1b,ac1c,NULL));
    labelnum2->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(0.5),ac2a,ac2b,ac2c,NULL));
    labelnum3->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(0.5),ac3a,ac3b,ac3c,NULL));
    labelnum4->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(0.5),ac4a,ac4b,ac4c,NULL));
     
}

cocos2d::String* Game::imageFilename(int index)
{
    cocos2d::Ref *o = this->arrayMap.at(index);
    int n = ((MapNode *)o)->imgid;
    if (n >= 1 && n <= TOTAL_IMG){
        return cocos2d::String::createWithFormat("LinkLiner/%d.png",n);
    }else{
        return NULL;
    }
}

cocos2d::Vec2 Game::pointOfView(cocos2d::Vec2 point)
{
	int x = -1;
	int y = -1;
	if (point.x > OFFSET_X && point.x < TOTAL_X * SIZE_W + OFFSET_X)
	{
        x = (point.x - OFFSET_X) / SIZE_W;
    }
    if (point.y > 480 - OFFSET_Y - TOTAL_Y * SIZE_H && point.y < 480 - OFFSET_Y)
    {
        y = (480 - point.y - OFFSET_Y) / SIZE_H;
    }
    return CCPointMake(x, y);
}


void Game::showWin()
{
	LabelTTF *label = LabelTTF::create("GameWin!!", "Arial", 36.0f);
    
	Size s = Director::getInstance()->getWinSize();
	label->setPosition(s.width/2, s.height/2);
    this->addChild(label);
    this->scheduleOnce(schedule_selector(Game::exitGame), 2.0);
}

int Game::indexFromPoint(cocos2d::Vec2 point)
{
	return point.y * TOTAL_Y + point.x;
}

void Game::clearNode(cocos2d::Vec2 point)
{
	int index = this->indexFromPoint(point);
	MapNode *mapnode = (MapNode *)(this->arrayMap.at(index));
	mapnode->imgid = 0;
}

bool Game::isSamePoints(cocos2d::Vec2 p1, cocos2d::Vec2 p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}

bool Game::isValiableNode(cocos2d::Vec2 point)
{
	return point.x >= 0 && point.x < TOTAL_X && point.y >= 0 && point.y < TOTAL_Y;
}

bool Game::isEmptyNode(cocos2d::Vec2 point)
{
	int index = this->indexFromPoint(point);
	MapNode *mapnode = (MapNode *)(this->arrayMap.at(index));
	return (mapnode->imgid == 0);
}

#pragma mark link

bool Game::match_direct(cocos2d::Vec2 a, cocos2d::Vec2 b)
{
	if (!(a.x == b.x || a.y == b.y)) {
		return false;
	}
	
	int i;
	bool match_x = false;
	if(a.x == b.x) {
		match_x = true;
		if(a.y > b.y) {
			for(i = a.y - 1; i > b.y; --i) {
				Vec2 point = CCPointMake(a.x, i);
                if(!this->isValiableNode(point) || !this->isEmptyNode(point)){
					match_x = false;
				}
			}
		}
		if(b.y > a.y) {
			for(i = b.y - 1; i > a.y; --i) {
				Vec2 point = CCPointMake(a.x, i);
				if(!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_x = false;
				}
			}
		}
	}
	
	bool match_y = false;
	if(a.y == b.y) {
		match_y = true;
		if(a.x > b.x) {
			for(i = a.x - 1; i > b.x; --i) {
				Vec2 point = CCPointMake(i, a.y);
				if(!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_y = false;
				}
			}
		}
		if(b.x > a.x) {
			for(i = b.x - 1; i > a.x; --i) {
				Vec2 point = CCPointMake(i, a.y);
				if(!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_y = false;
				}
			}
		}
	}
	
	return match_x || match_y;
}

bool Game::match_one_corner(cocos2d::Vec2 a, cocos2d::Vec2 b)
{
	Vec2 point = CCPointMake(b.x, a.y);

    if( this->isValiableNode(point) && this->isEmptyNode(point) && this->match_direct(a, point) && this->match_direct(b, point)){
        return true;
    }
	
	point = CCPointMake(a.x, b.y);
	if( this->isValiableNode(point) && this->isEmptyNode(point) && this->match_direct(a, point) && this->match_direct(b, point)){
        return true;
    }
	
	return false;
}

bool Game::match_two_corner(cocos2d::Vec2 a, cocos2d::Vec2 b)
{
	for(int i = a.x - 1; i >= 0; --i) {
		Vec2 point = CCPointMake(i, a.y);        
        if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
            break;
        } else {
            if (this->match_one_corner(point, b)) {
                return true;
            }
        }
	}
	
	for(int i = a.x + 1; i < TOTAL_X; ++i) {
		Vec2 point = CCPointMake(i, a.y);        
        if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
            break;
        } else {
            if (this->match_one_corner(point, b)) {
                return true;
            }
        }
	}
	
	for(int i = a.y - 1; i >= 0; --i) {
		Vec2 point = CCPointMake(a.x ,i);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
            break;
        } else {
            if (this->match_one_corner(point, b)) {
                return true;
            }
        }
	}
	
	for(int i = a.y + 1; i < TOTAL_Y; ++i) {
		Vec2 point = CCPointMake(a.x ,i);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
            break;
        } else {
            if (this->match_one_corner(point, b)) {
                return true;
            }
        }
	}
	
	return false;
}

bool Game::match(cocos2d::Vec2 a,cocos2d::Vec2 b)
{
    if (this->match_direct(a, b)) {
        return true;
    }
    if (this->match_one_corner(a, b)) {
        return true;
    }
    if (this->match_two_corner(a, b)) {
        return true;
    }
	
	return false;
}


bool Game::canClearTwo(cocos2d::Vec2 pointpre, cocos2d::Vec2 pointcurrent)
{
	bool bMatch = false;
	int pre = this->indexFromPoint(pointpre);
	int current = this->indexFromPoint(pointcurrent);
	int p = ((MapNode *)(this->arrayMap.at(pre)))->imgid;
	int c = ((MapNode *)(this->arrayMap.at(current)))->imgid;
	
    if (p == c && this->match(pointcurrent, pointpre)) {
		bMatch = true;
	}
	
	return bMatch;
}


bool Game::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    Vec2 ptouch = pTouch->getLocationInView();
	if (ptouch.x > 250 && ptouch.y > 420) {
       SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        this->schedule(schedule_selector(Game::exitGame), 0);
        return true;
	}
	
	Vec2 pointcurrent = this->pointOfView(pTouch->getLocationInView());
    
    if (this->isValiableNode(pointcurrent) == false) {
        return false;
    }
	
	if (this->isEmptyNode(pointcurrent)) {
		return false;
	}
	SimpleAudioEngine::getInstance()->playEffect("LinkLiner/choose.wav");
    
	if (this->isSamePoints(pointcurrent, prePoint)) {
		return false;
	}
	
	Sprite *spritecurrent = (Sprite *)this->getChildByTag(TAG_START_SPRITE + this->indexFromPoint(pointcurrent));
    
	spritecurrent->setScale(0.6f);
	
	if (this->isValiableNode(prePoint)) {
		Sprite *spritepre = (Sprite *)this->getChildByTag(TAG_START_SPRITE + this->indexFromPoint(prePoint));
		if (this->canClearTwo(prePoint, pointcurrent)) {
           SimpleAudioEngine::getInstance()->playEffect("LinkLiner/disappear1.wav");
            this->clearNode(prePoint);
            this->clearNode(pointcurrent);
            spritepre->setVisible(false);
            spritecurrent->setVisible(false);
			if (++countCleared >= MAX_CLEARED) {
               SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
               SimpleAudioEngine::getInstance()->playEffect("LinkLiner/win.mp3");
                this->showWin();
			}
			LabelTTF *label = (LabelTTF *)this->getChildByTag(TAG_LABEL_CONNER);
            cocos2d::String *str = String::createWithFormat("进度:%d%%", (int)(countCleared * 100 / MAX_CLEARED));
            label->setString(str->getCString());
		} else {
			spritepre->setScale(0.5);
		}
	}
	
	prePoint = pointcurrent;
    return true;
}

void Game::exitGame(float f)
{
    Scene *pScene = MenuScene::scene();
    TransitionFade* transitionScene = TransitionFade::create(1.0, pScene,Color3B::WHITE);
    Director::getInstance()->replaceScene(transitionScene);
}



int compare(const void* a, const void* b){
    MapNode *self = (MapNode *)a;
    MapNode *other = (MapNode *)b;
	if (self->order > other->order) {
		return 1;
	} else if (self->order == other->order) {
		return 0;
	} else {
		return -1;
	}
}





