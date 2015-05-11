#include "OpeningAnimation.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
#include "ChineseString.h"
#include "GameDefine.h"
#include "MainMenu.h"

using namespace CocosDenshion;

USING_NS_CC;

bool OpeningAnimation::sResReady = false;
std::vector<std::string> OpeningAnimation::sResVector;
unsigned int OpeningAnimation::sIndex = -1;

void OpeningAnimation::doTrans(float dt){
	log("do trans from %d", sIndex);
	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1, OpeningAnimation::scene())
		);
}

Scene* OpeningAnimation::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	OpeningAnimation *layer = OpeningAnimation::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// add the 'mask' layer
	{
		float width = designResolutionSize.width;
		float height = 100;//估计值
		auto layerBot = LayerColor::create(Color4B(0, 0, 0, 0xFF), width, height);
		layerBot->setAnchorPoint(Vec2(0, 0));
		layerBot->setPosition(0, 0);
		scene->addChild(layerBot);

		auto layerTop = LayerColor::create(Color4B(0, 0, 0, 0xFF), width, height);
		layerTop->setAnchorPoint(Vec2(0, 0));
		layerTop->setPosition(0, designResolutionSize.height - height);
		scene->addChild(layerTop);
		//退出
		auto exitLab = Label::createWithTTF(TTF_RES_PATH, ChineseString::a2u("退出"));
		exitLab->setSystemFontSize(TTF_FONT_SIZE);
		Size exitLabSize = exitLab->getContentSize();
		auto exitItem = MenuItemLabel::create(exitLab, [&](Ref *pSender){
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, MainMenu::createScene()));
		});
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto menu = Menu::create(exitItem, nullptr);
		menu->setPosition(Vec2(visibleSize.width - exitLabSize.width / 2, exitLabSize.height / 2));
		scene->addChild(menu);
	}
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool OpeningAnimation::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	
	// 静态变量初始化
	if (!sResReady) {
		sResReady = true;
		sResVector.push_back("OpeningAnimation/00.jpg");
		sResVector.push_back("OpeningAnimation/01.jpg");
		sResVector.push_back("OpeningAnimation/02.jpg");
		sResVector.push_back("OpeningAnimation/03.jpg");
		sResVector.push_back("OpeningAnimation/04.jpg");

		sResVector.push_back("OpeningAnimation/05.jpg");
		sResVector.push_back("OpeningAnimation/06.jpg");
		sResVector.push_back("OpeningAnimation/07.jpg");
		sResVector.push_back("OpeningAnimation/08.jpg");
		sResVector.push_back("OpeningAnimation/09.jpg");

		sResVector.push_back("OpeningAnimation/10.jpg");
		sResVector.push_back("OpeningAnimation/11.jpg");
		sResVector.push_back("OpeningAnimation/12.jpg");
	}

	sIndex++;// index start from 0

	// make it repeat for ever
	if (sIndex == sResVector.size()){
		sIndex = 0;
	}

	if (sIndex<sResVector.size()){
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();
		// add "OpeningAnimation" splash screen"
		auto sprite = Sprite::create(sResVector.at(sIndex));

		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize / 2) + origin);

		// run the scale action
		// 细节，用delay配合TransitionCrossFade的时间，这样过度不会卡顿
		//	    sprite->runAction(ScaleTo::create(4, 1.08f));
		auto actionSeq = Sequence::create(
			DelayTime::create(1),
			ScaleTo::create(4, 1.08f),
			nullptr);
		sprite->runAction(actionSeq);

		// add the sprite as a child to this layer
		this->addChild(sprite);

		// prepare to do trans
		scheduleOnce(schedule_selector(OpeningAnimation::doTrans), 4);
	}


	return true;
}

void OpeningAnimation::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
