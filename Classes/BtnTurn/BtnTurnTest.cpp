#include "BtnTurnTest.h"
#include "BtnTurn.h"
#include "backMain.h"

BtnTurnTest::BtnTurnTest()
{
}

BtnTurnTest::~BtnTurnTest()
{

}

Scene * BtnTurnTest::create()
{
	auto scene = Scene::create();
	auto pLayer = new BtnTurnTest();
	if (pLayer && pLayer->init())
	{
		pLayer->autorelease();
		scene->addChild(pLayer);
		return scene;
	}
	else
	{
		CC_SAFE_DELETE(pLayer);
		return NULL;
	}
}

bool BtnTurnTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto bgSize = Director::getInstance()->getVisibleSize();

	auto pBg = Sprite::create("BtnTurn/bg.png");
	pBg->setPosition(Vec2(bgSize.width / 2,bgSize.height / 2));
	this->addChild(pBg);

	//添加标题
	auto plabel = Label::createWithTTF("BtnTurnTest","fonts/Marker Felt.ttf",30);
	plabel->setPosition(Vec2(bgSize.width / 2,bgSize.height*0.9));
	pBg->addChild(plabel);

	//添加BtnTurn
	auto btnTurn = BtnTurn::create();
	//btnTurn->setPosition(Vec2(bgSize.width * 0.525, bgSize.height * 0.5));
	btnTurn->setPosition(Vec2(bgSize.width / 4, bgSize.height / 2));
	pBg->addChild(btnTurn);
	auto menu = backMain::createMenu();
	this->addChild(menu);
	return true;
}


