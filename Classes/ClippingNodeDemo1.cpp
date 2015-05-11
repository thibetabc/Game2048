#include "ClippingNodeDemo1.h"
//#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "backMain.h"


ClippingNodeDemo1::ClippingNodeDemo1()
	:m_font("fonts/msyh.ttf")
	,m_fontSize(30)
	,m_state(State::idle)
	, m_count(0)
{

	auto size = Director::getInstance()->getVisibleSize();
	m_showRect = Rect(0, 0, size.width, 30);
}
ClippingNodeDemo1::~ClippingNodeDemo1()
{

}

bool ClippingNodeDemo1::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto stencil = Sprite::create();
	stencil->setTextureRect(m_showRect);
	stencil->setColor(Color3B::BLUE);
	auto clippingNode = ClippingNode::create();
	clippingNode->setInverted(false);
	clippingNode->setAlphaThreshold(0.5f);
	clippingNode->setStencil(stencil);
	auto size = Director::getInstance()->getVisibleSize();
	clippingNode->setPosition(size / 2);
	this->addChild(clippingNode);

	m_label = Label::createWithTTF(TTFConfig(m_font.c_str(), m_fontSize), "");
	m_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	clippingNode->addChild(m_label);
	this->addChild(stencil, -1);


	//testBtn
	auto button = ui::Button::create("CloseNormal.png","CloseSelected.png");
	button->addTouchEventListener([&](Ref*sender, ui::Widget::TouchEventType eventType)
	{
		if (eventType == ui::Widget::TouchEventType::ENDED)
		{
			addMessage(StringUtils::format("test %d", ++m_count));
		}
	});
	button->setPosition(Vec2(100, 100));
	this->addChild(button);
	auto menu = backMain::createMenu();
	this->addChild(menu);

	return true;
}

void ClippingNodeDemo1::show(std::string str)
{
	m_state = State::playing;
	m_label->setPosition(Vec2::ZERO);
	m_label->setString(str);
	auto seq = Sequence::create(
		Show::create(),
		MoveBy::create(5.0f, Vec2(-(m_label->getContentSize().width + m_showRect.size.width / 2), 0)),
		Hide::create(),
		DelayTime::create(1.0f),
		CallFunc::create([&]()
		{
		if (_texts.size() == 0)
		{
			m_state = State::idle;
		}
		else
		{
			show(_texts.front());
			_texts.pop();
		}
		})
		,NULL
	);
	m_label->runAction(seq);
}

void ClippingNodeDemo1::addMessage(const std::string text)
{
	if (text.empty())
	{
		return;
	}

	if (m_state == State::idle)
	{
		show(text);
	}
	else
	{
		_texts.push(text);
	}
}


Scene *ClippingNodeDemo1::createScene()
{
	auto scene = Scene::create();
	auto layer = ClippingNodeDemo1::create();
	scene->addChild(layer);
	return scene;
}