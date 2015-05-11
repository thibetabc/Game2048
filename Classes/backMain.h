#include "cocos2d.h"
#include "GameDefine.h"
#include "ChineseString.h"
#include "MainMenu.h"
USING_NS_CC;
class backMain
{
public:
	static Menu *createMenu()
	{
		//ÍË³ö
		auto exitLab = Label::createWithTTF(TTF_RES_PATH, ChineseString::a2u("ÍË³ö"));
		exitLab->setSystemFontSize(TTF_FONT_SIZE);
		Size exitLabSize = exitLab->getContentSize();
		auto exitItem = MenuItemLabel::create(exitLab, [&](Ref *pSender){
			Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, MainMenu::createScene()));

		});
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto menu = Menu::create(exitItem, nullptr);
		menu->setPosition(Vec2(visibleSize.width - exitLabSize.width / 2, exitLabSize.height / 2));
		return menu;
	}
};