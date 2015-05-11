#include "MidMenu.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "ChineseString.h"

using namespace CocosDenshion;

MidMenu::MidMenu()
{

}
MidMenu::~MidMenu()
{

}

bool MidMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibelSize = Director::getInstance()->getVisibleSize();
	MenuItemFont *backGame = MenuItemFont::create(ChineseString::a2u("返回游戏"), CC_CALLBACK_1(MidMenu::menu, this));
	int audioTag = UserDefault::getInstance()->getIntegerForKey(AUDIO_DEFAULT);
	MenuItemFont *setMusic = MenuItemFont::create(ChineseString::a2u(audioTag > 0 ? "音乐:开" : "音乐:关"), CC_CALLBACK_1(MidMenu::menu, this));
	MenuItemFont *restart = MenuItemFont::create(ChineseString::a2u("重新游戏"), CC_CALLBACK_1(MidMenu::menu, this));
	backGame->setTag(0);
	setMusic->setTag(1);
	restart->setTag(2);
	Menu *menu = Menu::create(backGame, setMusic, restart, nullptr);
	menu->setPosition(Vec2(visibelSize.width / 2, visibelSize.height / 2));
	menu->alignItemsVertically();
	this->addChild(menu);

	return true;
}

Scene *MidMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MidMenu::create();
	scene->addChild(layer);
	return scene;
}

void MidMenu::menu(Ref *pSender)
{
	if (UserDefault::getInstance()->getIntegerForKey(AUDIO_DEFAULT) > 0)
	{
		SimpleAudioEngine::getInstance()->playEffect(AUDIO_PLAY_PATH);
	}
	int tag = static_cast<MenuItemFont*>(pSender)->getTag();
	CCLOG("tag = %d", tag);
	switch (tag)
	{
	case 0:
		Director::getInstance()->popScene();
		break;
	case 1:
		{
			int audioTag = UserDefault::getInstance()->getIntegerForKey(AUDIO_DEFAULT);
			if (audioTag > 0)
			{
				static_cast<MenuItemFont*>(pSender)->setString(ChineseString::a2u("音乐:关"));
				UserDefault::getInstance()->setIntegerForKey(AUDIO_DEFAULT, -1);
			}
			else
			{
				static_cast<MenuItemFont*>(pSender)->setString(ChineseString::a2u("音乐:开"));
				UserDefault::getInstance()->setIntegerForKey(AUDIO_DEFAULT, 1);
			}
			UserDefault::getInstance()->flush();
		}
		break;
	case 2:
		Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f, GameScene::createScene(), true));
		break;
	default:
		break;
	}
}

