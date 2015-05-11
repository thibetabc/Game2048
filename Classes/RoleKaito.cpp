#include "RoleKaito.h"
#include "AStar/AStarDefine.h"

RoleKaito::RoleKaito()
{

}
RoleKaito::~RoleKaito()
{

}

bool RoleKaito::init()
{
	auto pTex = TextureCache::getInstance()->addImage(RES_URL + "kaito.png");
	m_size.width = pTex->getContentSize().width / 4;
	m_size.height = pTex->getContentSize().height / 4;
	m_pSprMain = Sprite::create(RES_URL + "kaito.png", Rect(0, m_size.height * 2, m_size.width, m_size.height));
	m_pSprMain->setAnchorPoint(Vec2(0.5, 0.05));
	this->addChild(m_pSprMain);
	CreateActions();

	SetState(State::WalkBottom);
	SetState(State::None);
	return true;
}

void RoleKaito::CreateActions()
{
	auto pTex = TextureCache::getInstance()->addImage(RES_URL + "kaito.png");
	float DelayPerUnit = 0.15;


	auto pAnim = Animation::create();
	pAnim->setDelayPerUnit(DelayPerUnit);
	for (int i = 0; i < 4; ++i)
	{
		Rect rect(m_size.width * i, m_size.height * 2, m_size.width, m_size.height);
		pAnim->addSpriteFrameWithTexture(pTex, rect);
	}
	m_pActWalkRight = RepeatForever::create(Animate::create(pAnim));
	m_Actions.pushBack(m_pActWalkRight);


	pAnim = Animation::create();
	pAnim->setDelayPerUnit(DelayPerUnit);
	for (int i = 0; i < 4; ++i)
	{
		Rect rect(m_size.width * i, m_size.height * 1, m_size.width, m_size.height);
		pAnim->addSpriteFrameWithTexture(pTex, rect);
	}
	m_pActWalkLeft = RepeatForever::create(Animate::create(pAnim));
	m_Actions.pushBack(m_pActWalkLeft);


	pAnim = Animation::create();
	pAnim->setDelayPerUnit(DelayPerUnit);
	for (int i = 0; i < 4; ++i)
	{
		Rect rect(m_size.width * i, m_size.height * 0, m_size.width, m_size.height);
		pAnim->addSpriteFrameWithTexture(pTex, rect);
	}
	m_pActWalkBottom = RepeatForever::create(Animate::create(pAnim));
	m_Actions.pushBack(m_pActWalkBottom);


	pAnim = Animation::create();
	pAnim->setDelayPerUnit(DelayPerUnit);
	for (int i = 0; i < 4; ++i)
	{
		Rect rect(m_size.width * i, m_size.height * 3, m_size.width, m_size.height);
		pAnim->addSpriteFrameWithTexture(pTex, rect);
	}
	m_pActWalkTop = RepeatForever::create(Animate::create(pAnim));
	m_Actions.pushBack(m_pActWalkTop);
}

void RoleKaito::SetState(State type)
{
	m_pSprMain->stopAllActions();
	switch (type)
	{
	case State::None:
	{
		m_pSprMain->stopAllActions();
		// 之前的状态决定空闲的精灵
		switch (m_State)
		{
		case State::None:
			break;

		case State::WalkTop:
			m_pSprMain->setTextureRect(Rect(m_size.width * 0, m_size.height * 3, m_size.width, m_size.height));
			break;

		case State::WalkBottom:
			m_pSprMain->setTextureRect(Rect(m_size.width * 0, m_size.height * 0, m_size.width, m_size.height));
			break;

		case State::WalkLeft:
			m_pSprMain->setTextureRect(Rect(m_size.width * 0, m_size.height * 1, m_size.width, m_size.height));
			break;

		case State::WalkRight:
			m_pSprMain->setTextureRect(Rect(m_size.width * 0, m_size.height * 2, m_size.width, m_size.height));
			break;

		default:
			break;
		}
	}
		break;

	case State::WalkTop:
		m_pSprMain->setTextureRect(Rect(m_size.width * 0, m_size.height * 0, m_size.width, m_size.height));
		m_pSprMain->runAction(m_pActWalkTop);
		break;

	case State::WalkBottom:
		m_pSprMain->runAction(m_pActWalkBottom);
		break;

	case State::WalkLeft:
		m_pSprMain->runAction(m_pActWalkLeft);
		break;

	case State::WalkRight:
		m_pSprMain->runAction(m_pActWalkRight);
		break;

	default:
		break;
	}
	m_State = type;
}