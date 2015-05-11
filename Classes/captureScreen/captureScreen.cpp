#include "captureScreen.h"
#include "backMain.h"


bool captureScreen::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visSize.width / 2,
		origin.y + visSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visSize.width / 2 + origin.x, visSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	// add "HelloWorld" splash screen"
	auto QRcode = Sprite::create("QRcode.png");

	// position the sprite on the center of the screen
	QRcode->setPosition(Vec2(visSize.width / 2 + origin.x, visSize.height / 2 + origin.y-100));
	QRcode->setVisible(false);
	QRcode->setTag(1000);
	// add the sprite as a child to this layer
	this->addChild(QRcode, 0);



	auto label1 = Label::createWithTTF("capture all", "fonts/msyh.ttf", 30.0f);
	label1->enableOutline(Color4B(0, 0, 0, 255), 1);
	label1->setOpacity(0);
	auto fadeInAction = FadeIn::create(1.0f);
	auto fadeOutAction = FadeOut::create(1.0f);
	auto pSequenceScale = Sequence::createWithTwoActions(fadeInAction, fadeOutAction);
	label1->runAction(RepeatForever::create(pSequenceScale));
	auto mi1 = MenuItemLabel::create(label1, CC_CALLBACK_1(captureScreen::captureEvent, this));
	auto menu = Menu::create(mi1, nullptr);
	menu->setPosition(visSize.width / 2, visSize.height / 4);
	addChild(menu);

	auto exit = backMain::createMenu();
	addChild(exit);
	//auto caplb = Label::createWithTTF("caplb", "fonts/msyh.ttf", 50);
	//caplb->setPosition(Vec2(visSize.width/2, visSize.height/2));
	//this->addChild(caplb);

	//auto *ev = EventListenerTouchOneByOne::create();
	//ev->onTouchBegan = [](Touch* t, Event* e){
	//	cocos2d::log("touch begin!");
	//	return true;
	//};

	//ev->onTouchMoved = [](Touch* t, Event* e){};
	//ev->onTouchEnded = [&, caplb](Touch* t, Event* e){
	//	auto pos = t->getLocation();
	//	auto rect = caplb->getBoundingBox();
	//	auto cpos = caplb->convertToNodeSpace(pos);
	//	if (rect.containsPoint(cpos))
	//	{
	//		cocos2d::log("caplb is touched!!");
	//		std::string filename = "captureScreen.jpg"; //初始化filename，后缀很重要
	//		caplb->setVisible(false);//将Capture这个label隐藏
	//		capturesc(filename); //截屏
	//	}
	//};
	///Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ev, this);
	return true;
}

// there's no 'id' in cpp, so we recommend returning the class instance pointer
Scene* captureScreen::scene()
{
	auto scene = Scene::create();
	auto layer = captureScreen::create();
	scene->addChild(layer);
	return scene;
}

void captureScreen::captureEvent(Ref *pSender)
{
	std::string filename = "captureScreen.jpg"; //初始化filename，后缀很重要
	auto menuIten = (MenuItemLabel*)pSender;
	menuIten->setVisible(false);//将Capture这个label隐藏
	auto QRcode = this->getChildByTag(1000);
	QRcode->setVisible(true);
	capturesc(filename); //截屏

}
void captureScreen::afterCaptureScreen(bool issuccess, const std::string &filename) //这个函数参数是固定的，不能写错了
{
	auto size = Director::getInstance()->getWinSize();
	if (issuccess)
	{
		auto scene = Scene::create();
		auto sp = Sprite::create(filename);

		sp->setScale(0.8f);
		sp->setPosition(Vec2(size.width / 2, size.height / 2));
		scene->addChild(sp);

		auto lb = LabelTTF::create();
		lb->setString("capture success!");
		lb->setColor(ccc3(255, 0, 0));
		lb->setFontSize(40);
		lb->setAnchorPoint(Vec2(0.5f, 1.0f));
		lb->setPosition(Vec2(size.width / 2, size.height));
		scene->addChild(lb);
		auto exit = backMain::createMenu();
		scene->addChild(exit);

		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		auto scene = Scene::create();

		auto lb = Label::create();
		lb->setString("Capture Failed！");
		lb->setTextColor(ccc4(255, 0, 0, 255));
		lb->setPosition(Vec2(size.width / 2, size.height / 2));
		scene->addChild(lb);

		auto exit = backMain::createMenu();
		scene->addChild(exit);
		Director::getInstance()->replaceScene(scene);
	}
}

void captureScreen::capturesc(std::string &filename)
{
	Director::getInstance()->getTextureCache()->removeTextureForKey(filename); //这里最好加上这句，因为如果你需要重复点击这个按钮进行截屏操作的话，TextureCache里面不清除，会导致截屏失败
	utils::captureScreen(CC_CALLBACK_2(captureScreen::afterCaptureScreen, this), filename); //在这里调用cocos2d已经实现好的captureScreen函数，将我们写好的aftercapture函数和我们需要的图片名称穿进去，图片名称的初始化必须在这个函数调用之前完成
}