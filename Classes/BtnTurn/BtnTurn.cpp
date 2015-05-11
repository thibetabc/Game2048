#include "BtnTurn.h"

const float RUNTIME = 0.3; //动画运行时间
float A;//椭圆长半径
float Bd;//下椭圆短半径
float Bu;//上椭圆短半径
float Cx;//椭圆中心X坐标
float Cy;//椭圆中心Y坐标

BtnTurn::BtnTurn()
: m_btn1(nullptr)
, m_btn2(nullptr)
, m_btn3(nullptr)
, m_btn4(nullptr)
, m_firstPos(Point::ZERO)
, m_valid(false)
, m_invalid(false)

{

}

BtnTurn::~BtnTurn()
{

}

bool BtnTurn::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_winSize = Director::getInstance()->getWinSize();
	m_posBottom = Vec2(0,0);
	m_posLeft = Vec2(-m_winSize.width * 0.24,m_winSize.height * 0.15);
	m_posTop = Vec2(0,m_winSize.height * 0.24);
	m_posRight = Vec2(m_winSize.width * 0.24,m_winSize.height * 0.15);
	A = m_posBottom.x - m_posLeft.x;
	Bu = m_posTop.y - m_posLeft.y;
	Bd = m_posLeft.y - m_posBottom.y;
	Cx = m_posBottom.x;
	Cy = m_posLeft.y;

	Texture2D * pTt2d = Director::getInstance()->getTextureCache()->addImage("BtnTurn/btn.png");
	m_btn1 = Sprite::createWithTexture(pTt2d);
	m_btn1->setPosition(m_posBottom);
	m_btn1->setTag(Pos_Bottom);
	this->addChild(m_btn1,4);

	m_btn2 = Sprite::createWithTexture(pTt2d);
	m_btn2->setPosition(m_posLeft);
	m_btn2->setScale(0.75);
	m_btn2->setOpacity(100);
	m_btn2->setTag(Pos_Left);
	this->addChild(m_btn2,3);

	m_btn3 = Sprite::createWithTexture(pTt2d);
	m_btn3->setPosition(m_posTop);
	m_btn3->setScale(0.5);
	m_btn3->setOpacity(50);
	m_btn3->setTag(Pos_Top);
	this->addChild(m_btn3,2);

	m_btn4 = Sprite::createWithTexture(pTt2d);
	m_btn4->setPosition(m_posRight);
	m_btn4->setScale(0.75);
	m_btn4->setOpacity(100);
	m_btn4->setTag(Pos_Right);
	this->addChild(m_btn4,3);

	auto listenerT = EventListenerTouchOneByOne::create();
	listenerT->onTouchBegan = CC_CALLBACK_2(BtnTurn::onTouchBegan,this);
	listenerT->onTouchMoved = CC_CALLBACK_2(BtnTurn::onTouchMoved,this);
	listenerT->onTouchEnded = CC_CALLBACK_2(BtnTurn::onTouchEnded,this);
	listenerT->setSwallowTouches(false);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerT,this);

	return true;
}

bool BtnTurn::onTouchBegan(Touch* touch, Event* pEvent)
{
	m_firstPos = touch->getLocation();

	return true;
}

void BtnTurn::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	auto movePos = pTouch->getLocation();
	auto judgePos = this->convertToNodeSpace(movePos);
	auto box = Rect(-m_winSize.width * 0.5,-m_winSize.height * 0.1,m_winSize.width,m_winSize.height * 0.4);
	//优化，不能全屏都可以滑,并判断是先点击有效还是无效区域
	if (!box.containsPoint(judgePos))
	{
		if (!m_valid)
		{
			m_invalid = true;
		}
		return ;
	}
	if (!m_invalid)
	{
		m_valid = true;
	}
	else
	{
		return ;
	}
	//根据滑动方向来运动
	auto ratio = fabsf(movePos.x - m_firstPos.x) * 2 / m_winSize.width;
	if (ratio >= 1)
	{
		return ;
	}
	this->runSlidedAmt(movePos.x - m_firstPos.x < 0,ratio,fabsf(m_firstPos.x - movePos.x));
}

void BtnTurn::runSlidedAmt(bool isLeft,float ratio,float judgePosX)
{
	auto btnTop = this->getChildByTag(Pos_Top);
	auto btnLeft = this->getChildByTag(Pos_Left);
	auto btnRight = this->getChildByTag(Pos_Right);
	auto btnBottom = this->getChildByTag(Pos_Bottom);

	auto deltPosDown = m_posRight - m_posBottom;
	auto deltPosUp = m_posTop - m_posLeft;

	//判断是否需要调换Z顺序
	if (judgePosX > m_winSize.width / 4)
	{
		btnTop->setZOrder(3);
		btnLeft->setZOrder(isLeft ? 2 : 4);
		btnRight->setZOrder(isLeft ? 4 : 2);
		btnBottom->setZOrder(3);
	}
	
	auto B1 = isLeft ? Bu : Bd;//判断左边的button沿哪个椭圆运动
	auto B2 = isLeft ? Bd : Bu;//判断右边的button沿哪个椭圆运动
	
	int temp = isLeft ? (m_posBottom.x - deltPosDown.x * ratio) : (m_posBottom.x + deltPosDown.x * ratio);
	btnBottom->setPosition(Vec2(temp,sin(-acos((temp - Cx)/A)) * Bd + Cy));
	btnBottom->setScale(1 - 0.25 * ratio);
	btnBottom->setOpacity(255 - 155 * ratio);

	temp = isLeft ? (m_posLeft.y + deltPosUp.y * ratio) : (m_posLeft.y - deltPosDown.y * ratio);
	btnLeft->setPosition(Vec2(-cos(asin((temp - Cy)/B1)) * A + Cx,temp));
	btnLeft->setScale(0.75 - (isLeft ? 0.25 * ratio : -0.25 * ratio));
	btnLeft->setOpacity(100 - (isLeft ? 50 * ratio : -155 * ratio));

	temp = m_posTop.x + (isLeft ? (deltPosUp.x * ratio) : (-1 * deltPosUp.x * ratio));
	btnTop->setPosition(Vec2(temp,sin(acos((temp - Cx)/A)) * Bu + Cy));
	btnTop->setScale(0.5 + 0.25 * ratio);
	btnTop->setOpacity(50 + 50 * ratio);

	temp = m_posRight.y + (isLeft ? (-1 * deltPosDown.y * ratio) : (deltPosUp.y * ratio));
	btnRight->setPosition(Vec2(cos(asin((temp - Cy)/B2)) * A + Cx,temp));
	btnRight->setScale(0.75 + 0.25 * (isLeft ? ratio : -ratio));
	btnRight->setOpacity(100 + (isLeft ? 155 * ratio : -50 * ratio));
	
}

void BtnTurn::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	if (m_invalid)
	{
		m_invalid = false;
		return;
	}
	auto endPos = pTouch->getLocation();
	auto delX = endPos.x - m_firstPos.x;
	auto delY = endPos.y - m_firstPos.y;
	//如果是点击操作
	if (fabsf(delX) < 0.0001 && fabsf(delY) < 0.0001)
	{
		endPos = this->convertToNodeSpace(endPos);
		auto box1 = m_btn1->getBoundingBox();
		auto box2 = m_btn2->getBoundingBox();
		auto box3 = m_btn3->getBoundingBox();
		auto box4 = m_btn4->getBoundingBox();
		if (box1.containsPoint(endPos))
		{
			if (m_btn1->getZOrder() == 4)
			{
				log("******************Btn1 CallBack***************");
			}
			else
			{
				
				this->runTouchedAmt(m_btn1);
			}
		}
		else if (box2.containsPoint(endPos))
		{
			if (m_btn2->getZOrder() == 4)
			{
				log("******************Btn2 CallBack***************");
			}
			else
			{
				this->runTouchedAmt(m_btn2);
			}
		}
		else if (box3.containsPoint(endPos))
		{
			if (m_btn3->getZOrder() == 4)
			{
				log("******************Btn3 CallBack***************");
			}
			else
			{
				this->runTouchedAmt(m_btn3);
			}
		}
		else if (box4.containsPoint(endPos))
		{
			if (m_btn4->getZOrder() == 4)
			{
				log("******************Btn4 CallBack***************");
			}
			else
			{
				this->runTouchedAmt(m_btn4);
			}
		}
	}
	else//滑动操作
	{
		auto adjustPos = pTouch->getLocation();
		//判断滑动方向
		if (adjustPos.x - m_firstPos.x < 0)//向左滑动
		{
			auto tmpBtn = (Sprite *)this->getChildByTag(Pos_Right);
			this->runTouchedAmt(tmpBtn);
		}
		else if (adjustPos.x - m_firstPos.x > 0)
		{
			auto tmpBtn = (Sprite *)this->getChildByTag(Pos_Left);
			this->runTouchedAmt(tmpBtn);
		}
	}
	m_valid = false;
}

void BtnTurn::runTouchedAmt(Sprite * btn)
{
	auto tag = btn->getTag();
	switch (tag)
	{
	case Pos_Left :
		{
			btn->runAction(Spawn::create(ScaleTo::create(RUNTIME,1),
										Sequence::createWithTwoActions(MoveTo::create(RUNTIME / 2,m_posBottom),
												MoveTo::create(RUNTIME / 2,m_posBottom)),
										FadeIn::create(RUNTIME),NULL));
			btn->setZOrder(4);
			
			auto topBtn = (Sprite *)(this->getChildByTag(Pos_Top));
			topBtn->runAction(Spawn::create(ScaleTo::create(RUNTIME,0.75),
											MoveTo::create(RUNTIME,m_posLeft),
											FadeTo::create(RUNTIME,100),NULL));
			topBtn->setZOrder(3);

			auto rightBtn = (Sprite *)this->getChildByTag(Pos_Right);
			rightBtn->runAction(Spawn::create(ScaleTo::create(RUNTIME,0.5),
								MoveTo::create(RUNTIME,m_posTop),
								FadeTo::create(RUNTIME,50),NULL));
			rightBtn->setZOrder(2);

			auto bottomBtn = (Sprite *)this->getChildByTag(Pos_Bottom);
			bottomBtn->runAction(Spawn::create(ScaleTo::create(RUNTIME,0.75),
												MoveTo::create(RUNTIME,m_posRight),
												FadeTo::create(RUNTIME,100),NULL));
			bottomBtn->setZOrder(3);

			btn->setTag(Pos_Bottom);
			topBtn->setTag(Pos_Left);
			rightBtn->setTag(Pos_Top);
			bottomBtn->setTag(Pos_Right);
		}
		break;
	case Pos_Top :
		{
			btn->runAction(Spawn::create(ScaleTo::create(RUNTIME,1),
				Sequence::createWithTwoActions(MoveTo::create(RUNTIME/2,m_posLeft),MoveTo::create(RUNTIME/2,m_posBottom)),
				FadeIn::create(0.2),NULL));
			btn->setZOrder(4);

			auto rightBtn = (Sprite *)this->getChildByTag(Pos_Right);
			rightBtn->runAction(Spawn::create(Sequence::createWithTwoActions(ScaleTo::create(RUNTIME/2,0.5),ScaleTo::create(RUNTIME/2,0.75)),
				Sequence::createWithTwoActions(MoveTo::create(RUNTIME/2,m_posTop),MoveTo::create(RUNTIME/2,m_posLeft)),
				Sequence::createWithTwoActions(FadeTo::create(RUNTIME/2,50),FadeTo::create(RUNTIME/2,100)),NULL));
			rightBtn->setZOrder(3);

			auto bottomBtn = (Sprite *)this->getChildByTag(Pos_Bottom);
			bottomBtn->runAction(Spawn::create(ScaleTo::create(RUNTIME,0.5),
				Sequence::createWithTwoActions(MoveTo::create(RUNTIME/2,m_posRight),MoveTo::create(RUNTIME/2,m_posTop)),
				FadeTo::create(RUNTIME,50),NULL));
			bottomBtn->setZOrder(2);

			auto leftBtn = (Sprite *)this->getChildByTag(Pos_Left);
			leftBtn->runAction(Spawn::create(Sequence::createWithTwoActions(ScaleTo::create(RUNTIME/2,1),ScaleTo::create(RUNTIME/2,0.75)),
				Sequence::createWithTwoActions(MoveTo::create(RUNTIME/2,m_posBottom),MoveTo::create(RUNTIME/2,m_posRight)),
				Sequence::createWithTwoActions(FadeIn::create(RUNTIME/2),FadeTo::create(RUNTIME/2,100)),NULL));
			leftBtn->setZOrder(3);

			btn->setTag(Pos_Bottom);
			leftBtn->setTag(Pos_Right);
			rightBtn->setTag(Pos_Left);
			bottomBtn->setTag(Pos_Top);

		}
		break;
	case Pos_Right :
		{
			btn->runAction(Spawn::create(ScaleTo::create(RUNTIME,1),
				MoveTo::create(RUNTIME,m_posBottom),
				FadeIn::create(RUNTIME),NULL));
			btn->setZOrder(4);

			auto topBtn = (Sprite *)this->getChildByTag(Pos_Top);
			topBtn->runAction(Spawn::create(ScaleTo::create(RUNTIME,0.75),
				MoveTo::create(RUNTIME,m_posRight),
				FadeTo::create(RUNTIME,100),NULL));
			topBtn->setZOrder(3);

			auto leftBtn = (Sprite *)this->getChildByTag(Pos_Left);
			leftBtn->runAction(Spawn::create(ScaleTo::create(RUNTIME,0.5),
				MoveTo::create(RUNTIME,m_posTop),
				FadeTo::create(RUNTIME,50),NULL));
			leftBtn->setZOrder(2);

			auto bottomBtn = (Sprite *)this->getChildByTag(Pos_Bottom);
			bottomBtn->runAction(Spawn::create(ScaleTo::create(RUNTIME,0.75),
				MoveTo::create(RUNTIME,m_posLeft),
				FadeTo::create(RUNTIME,100),NULL));
			bottomBtn->setZOrder(3);

			btn->setTag(Pos_Bottom);
			topBtn->setTag(Pos_Right);
			leftBtn->setTag(Pos_Top);
			bottomBtn->setTag(Pos_Left);

		}
		break;
	}

}