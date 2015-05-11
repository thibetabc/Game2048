//
//  MenuScene.cpp
//  LinkLinker
//
//  Created by jun on 13-8-11.
//
//

#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* MenuScene::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    MenuScene *layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

MenuScene::~MenuScene()
{

	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

MenuScene::MenuScene()
:isEnter(false)
{
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // ask director the window size
    Size size = Director::getInstance()->getWinSize();
    Sprite* pSprite = Sprite::create("LinkLiner/bg.png");
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    LabelTTF* label = LabelTTF::create("LinkLiner~~", "Marker Felt", 48.0f);
	label->setPosition(  ccp( size.width /2 , size.height/2 ) );
    this->addChild(label, 1);
	
	Sprite* button = Sprite::create("LinkLiner/play.png");
    button->setPosition(  ccp(size.width/2, size.height/2 - 80) );
    this->addChild(button, 2);
	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [&](Touch *touch, Event*event)
	{
		return true;
	};
	eventListener->onTouchEnded = [&](Touch *touch, Event *event)
	{

		Scene *pScene = Game::scene();
		TransitionFade* transitionScene = TransitionFade::create(1.0, pScene, Color3B::WHITE);
		Director::getInstance()->replaceScene(transitionScene);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, button);
    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}





















