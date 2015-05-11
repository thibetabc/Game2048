#include "WelcomeScene_CandyCrush.h"
#include "GameDefine.h"  
#include "GameScene_CandyCrush.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

Scene* WelcomeScene_CandyCrush::createScene()  {
	auto scene = Scene::create();
	auto layer = WelcomeScene_CandyCrush::create();
	scene->addChild(layer);
	return scene;
}

// 欢迎界面 初始化函数  
bool WelcomeScene_CandyCrush::init()  
{
	// 先初始化父类，不成功返回false  
	if (!Layer::init())    {
		return false;
	}

	auto sprite = Sprite::create("CandyCrush/scene_sta.png");
	sprite->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	auto startSprite = MenuItemImage::create(
		"CandyCrush/btn_start01.png",
		"CandyCrush/btn_start02.png",
		CC_CALLBACK_1(WelcomeScene_CandyCrush::menuStartCallback, this));
	startSprite->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6));
	auto menu = Menu::create(startSprite, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void WelcomeScene_CandyCrush::menuStartCallback(Ref* pSender)
{
	// 跳转到游戏界面   // 跳转到游戏界面  
	auto scene = GameScene_CandyCrush::createScene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void WelcomeScene_CandyCrush::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE);
}
void WelcomeScene_CandyCrush::onExit()
{
	Layer::onExit();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(MUSIC_FILE);
}
