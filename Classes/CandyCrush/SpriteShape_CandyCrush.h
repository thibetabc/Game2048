#ifndef __H_SPRITESHAPE_CANDYCRUSH_H__
#define __H_SPRITESHAPE_CANDYCRUSH_H__
#include "cocos2d.h"
#include "GameDefine.h"
USING_NS_CC;

class SpriteShape_CandyCrush : public Sprite
{
public:
	SpriteShape_CandyCrush();
	~SpriteShape_CandyCrush();
	static SpriteShape_CandyCrush *create(int row, int col);
	void setDisplayMode(DisplayMode mode);

	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int, m_col, Col);
	CC_SYNTHESIZE(int, m_imgIndex, ImgIndex);
	CC_SYNTHESIZE(bool, m_isNeedRemove, IsNeedRemove);
	CC_SYNTHESIZE(bool, m_ignoreCheck, IgnoreCheck)
	CC_SYNTHESIZE_READONLY(DisplayMode, m_displayMode, DisplayMode);

};
#endif