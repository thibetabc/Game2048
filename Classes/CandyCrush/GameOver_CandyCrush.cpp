#include "GameOver_CandyCrush.h"
#include "GameScene_CandyCrush.h"
#include "WelcomeScene_CandyCrush.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
using namespace CocosDenshion;


Scene* GameOver_CandyCrush::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver_CandyCrush::create();
	scene->addChild(layer);
	return scene;
}


bool GameOver_CandyCrush::init()
{
	if (!Layer::init()){
		return false;
	}


	// 添加背景图片
	auto sprite = Sprite::create("CandyCrush/scene_end.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// 添加重新开始按钮
	auto restartItem = MenuItemImage::create(
		"CandyCrush/btn_restart01.png",
		"CandyCrush/btn_restart02.png",
		CC_CALLBACK_1(GameOver_CandyCrush::menuRestartCallback, this));

	restartItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 6));

	// 添加返回主菜单按钮
	auto backItem = MenuItemImage::create(
		"CandyCrush/btn_back01.png",
		"CandyCrush/btn_back02.png",
		CC_CALLBACK_1(GameOver_CandyCrush::menuBackCallback, this));

	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, backItem->getContentSize().height / 2));

	// 添加退出游戏按钮
	auto exitItem = MenuItemImage::create(
		"CandyCrush/btn_exit01.png",
		"CandyCrush/btn_exit02.png",
		CC_CALLBACK_1(GameOver_CandyCrush::menuExitCallback, this));
	exitItem->setPosition(Vec2(GAME_SCREEN_WIDTH - exitItem->getContentSize().width / 2, exitItem->getContentSize().height / 2));

	auto menu = Menu::create(restartItem, backItem, exitItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	// 分数
	TTFConfig config("fonts/yuehei.otf", 48);
	auto labelScore = Label::createWithTTF(config, "  0  ");
	labelScore->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 1.4));
	labelScore->setTag(13);
	this->addChild(labelScore);

	return true;
}


void GameOver_CandyCrush::menuRestartCallback(Ref *pSender)
{
	auto scene = GameScene_CandyCrush::createScene();
	TransitionScene* reScene = TransitionMoveInL::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
}

void GameOver_CandyCrush::menuBackCallback(Ref *pSender)
{
	auto scene = WelcomeScene_CandyCrush::createScene();
	TransitionScene* reScene = TransitionSplitRows::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
}

void GameOver_CandyCrush::menuExitCallback(Ref *pSender)
{
	//Director::getInstance()->end();
	auto scene = MainMenu::createScene();
	TransitionScene* reScene = TransitionSplitRows::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
}

void GameOver_CandyCrush::setScore(int sc)
{
	auto labelScore = (Label *)this->getChildByTag(13);
	labelScore->setString(StringUtils::format(" %d ", sc));

	if (userDefault->getIntegerForKey("Int") < sc){

		// 新纪录
		userDefault->setIntegerForKey("Int", sc);
		userDefault->flush();
		auto newRecord = Sprite::create("CandyCrush/sprite_newRecord.png");
		newRecord->setPosition(Point(GAME_SCREEN_WIDTH / 3.05, GAME_SCREEN_HEIGHT / 1.22));
		newRecord->setScale(10.0f);// start size
		newRecord->runAction(ScaleTo::create(1.2f, 1.0f));
		this->addChild(newRecord);
		// 音效
		SimpleAudioEngine::getInstance()->playEffect("CandyCrush/music_win.wav");
	}
	else
	{
		// 音乐
		SimpleAudioEngine::getInstance()->playEffect("CandyCrush/music_fail.mp3");
	}
}