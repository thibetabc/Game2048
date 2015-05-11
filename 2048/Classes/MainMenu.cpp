#include "MainMenu.h"
#include "GameScene.h"
#include "GameDefine.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto label = Label::createWithTTF(TTF_RES_PATH, "2048");
	auto visbleSize = Director::getInstance()->getVisibleSize();
	label->setSystemFontSize(TTF_FONT_SIZE);
	label->setPosition(visbleSize / 2);
	this->addChild(label);

	auto name = Label::createWithTTF(TTF_RES_PATH, "2015.02.12");
	name->setSystemFontSize(label->getSystemFontSize());
	name->setPosition(Vec2(label->getPositionX(), label->getPositionY() - label->getSystemFontSize() - 20));
	this->addChild(name);
	if (false)
	{
		this->scheduleOnce(schedule_selector(MainMenu::jumpToGame), 1);
	}
	else
	{
		auto event = EventListenerTouchOneByOne::create();
		event->onTouchBegan = [&](Touch *touch, Event *event)
		{
			return true;
		};
		event->onTouchEnded = [&](Touch *touch, Event *event)
		{
			jumpToGame(0);
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
	}
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