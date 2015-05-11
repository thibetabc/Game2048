#include "SpriteShape_CandyCrush.h"
#include "GameDefine.h"

SpriteShape_CandyCrush::SpriteShape_CandyCrush()
{
	m_row = 0;
	m_col = 0;
	m_isNeedRemove = false;
	m_imgIndex = 0;
}
SpriteShape_CandyCrush::~SpriteShape_CandyCrush()
{

}
SpriteShape_CandyCrush *SpriteShape_CandyCrush::create(int row, int col)
{
	SpriteShape_CandyCrush *spr = new SpriteShape_CandyCrush;
	spr->m_row = row;
	spr->m_col = col;
	spr->m_imgIndex = rand() % TOTAL_SPRITE;
	spr->initWithSpriteFrameName(spriteNormal[spr->m_imgIndex]);
	spr->autorelease();
	return spr;
}

void SpriteShape_CandyCrush::setDisplayMode(DisplayMode mode)
{
	m_displayMode = mode;
	SpriteFrame *frame;
	switch (mode)
	{
	case DisplayMode::DISPLAY_MODE_HORIZONTAL:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprHorizontal[m_imgIndex]);
		break;
	case DisplayMode::DISPLAY_MODE_VERTICAL:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprVertical[m_imgIndex]);
		break;
	default:
		return;
	}
	setSpriteFrame(frame);
}

