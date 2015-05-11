#include "GameOver.h"
#include "GameDefine.h"
#include "MainMenu.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibelSize = Director::getInstance()->getVisibleSize();

	Label *label = Label::createWithTTF(TTF_RES_PATH, "GAME OVER !");
	label->setPosition(visibelSize / 2);
	label->setSystemFontSize(TTF_FONT_SIZE);
	auto action = Sequence::createWithTwoActions(
		DelayTime::create(60.0f),
		CallFunc::create([](){
		Director::getInstance()->replaceScene(TransitionRotoZoom::create(0.5f, MainMenu::createScene()));
	}));
	label->runAction(action);
	this->addChild(label);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		return true;
	};
	listener->onTouchEnded = [&](Touch *touch, Event *event)
	{
		Director::getInstance()->replaceScene(TransitionRotoZoom::create(0.5f, MainMenu::createScene()));
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

Scene *GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return  scene;
}