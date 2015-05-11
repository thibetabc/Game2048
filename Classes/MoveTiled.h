#ifndef __H_MOVETILED_H__
#define __H_MOVETILED_H__

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class MoveTiled : public Node
{
public:
	CREATE_FUNC(MoveTiled);
	bool init();
	void showAt(int ros, int col);
	void moveTo(int row, int col);
	void doubleNum();

public:
	int m_row, m_col;
	int m_number;

};

#endif