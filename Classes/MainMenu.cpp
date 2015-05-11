#include "MainMenu.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "OpeningAnimation/OpeningAnimation.h"
#include "BtnTurn/BtnTurnTest.h"
#include "captureScreen/captureScreen.h"
#include "CandyCrush/WelcomeScene_CandyCrush.h"
#include "LinkLiner/MenuScene.h"
#include "ClippingNodeDemo1.h"
#include "Csv/Csv.h"
#include "AStar/SceneMapWalk.h"

using namespace CocosDenshion;

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//auto label = Label::createWithTTF(TTF_RES_PATH, "2048");
	//auto visbleSize = Director::getInstance()->getVisibleSize();
	//label->setSystemFontSize(TTF_FONT_SIZE);
	//label->setPosition(visbleSize / 2);
	//this->addChild(label);

	//auto name = Label::createWithTTF(TTF_RES_PATH, "2015.02.12");
	//name->setSystemFontSize(label->getSystemFontSize());
	//name->setPosition(Vec2(label->getPositionX(), label->getPositionY() - label->getSystemFontSize() - 20));
	//this->addChild(name);
	//if (false)
	//{
	//	this->scheduleOnce(schedule_selector(MainMenu::jumpToGame), 1);
	//}
	//else
	//{
	//	auto event = EventListenerTouchOneByOne::create();
	//	event->onTouchBegan = [&](Touch *touch, Event *event)
	//	{
	//		return true;
	//	};
	//	event->onTouchEnded = [&](Touch *touch, Event *event)
	//	{
	//		jumpToGame(0);
	//	};
	//	_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
	//}
	const char *g_aTestNames[] =
	{
		"2048",
		"OpeningAnimation",
		"BtnTurnTest",
		"captureScreen",
		"CandyCrush",
		"LinkLiner",
		"ClippingNodeDemo1",
		"CSV_Demo",
		"AStar_Demo",

	};
	static int g_testCount = sizeof(g_aTestNames) / sizeof(g_aTestNames[0]);
	auto visbleSize = Director::getInstance()->getVisibleSize(); 
	const int LINE_SPACE = 40;
	auto menu = Menu::create();
	for (int i = 0; i < g_testCount; i++)
	{
		auto label = Label::createWithTTF(g_aTestNames[i], "fonts/msyh.ttf", 20.0f);
		auto labelItem = MenuItemLabel::create(label, CC_CALLBACK_1(MainMenu::menuCallback, this));
		labelItem->setTag(i);
		menu->addChild(labelItem); 
	}
	//menu->setContentSize(Size(visbleSize.width, (g_testCount + 1) * (LINE_SPACE)));
	//menu->setPosition(Vec2::ZERO);
	menu->alignItemsVerticallyWithPadding(4);
	menu->setPosition(Vec2(visbleSize.width / 2, visbleSize.height / 2));
	this->addChild(menu, 1);


	return true;
}

Scene *MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

void MainMenu::jumpToGame(float f)
{

	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_PLAY_PATH);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_MOVE_PATH);

	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, GameScene::createScene()));
}

void MainMenu::menuCallback(Ref *pSender)
{

	Director::getInstance()->purgeCachedData();

	//auto menuItem = static_cast<MenuItem *>(pSender);
	//int idx = menuItem->getTag();
	//// create the test scene and run it
	//auto scene = g_aTestNames[idx].callback();

	//if (scene)
	//{
	//	scene->runThisTest();
	//	scene->release();
	//}

	// get the userdata, it's the index of the menu item clicked
	auto menuItem = static_cast<MenuItem *>(pSender);
	int idx = menuItem->getTag();

	switch (idx)
	{
	case 0:
		SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_PLAY_PATH);
		SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_MOVE_PATH);

		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, GameScene::createScene()));
		break;
	case 1:
		SimpleAudioEngine::getInstance()->playBackgroundMusic("OpeningAnimation/The Last Goodbye.mp3", true);
		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, OpeningAnimation::scene()));
		break;
	case 2:
		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, BtnTurnTest::create()));
		break;
	case 3:
		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, captureScreen::scene()));
		break;
	case 4:
		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, WelcomeScene_CandyCrush::createScene()));
		break;
	case 5:
		//Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, MenuScene::scene()));
		MessageBox("Too Much BUG, STOP!!", "LinkLiner");
		break;
	case 6:
		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, ClippingNodeDemo1::createScene()));
		break;
	case 7:
		Csv::Test();
		break;
	case 8:
		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5f, SceneMapWalk::create()));
		break;

	}
}