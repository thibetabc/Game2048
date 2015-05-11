#include "MoveTiled.h"
#include "GameDefine.h"

bool MoveTiled::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto numBg = LayerColor::create(Color4B(200, 200, 200, 255), GAME_TILED_WIDTH, GAME_TILED_HEIGHT);
	numBg->setTag(110);
	this->addChild(numBg);
	if (rand() % 10 > 2)
	{
		this->m_number = 2;
	}
	else
	{
		this->m_number = 4;
	}
	auto numLabel = Label::createWithTTF(TTF_RES_PATH, StringUtils::format("%d", this->m_number));
	numLabel->setPosition(numBg->getContentSize() / 2);
	numLabel->setColor(Color3B::BLACK);
	numLabel->setSystemFontSize(TTF_FONT_SIZE);
	numLabel->setTag(120);
	numBg->addChild(numLabel);
	numBg->setScale(0);
	numBg->runAction(Sequence::create(
		ScaleTo::create(0.25, 1),
		NULL
		));
	switch (this->m_number) {
	case 2:
		numBg->setColor(Color3B(238, 228, 218));
	case 4:
		numBg->setColor(Color3B(238, 223, 202));
		break;
	}
	return true;
}

void MoveTiled::showAt(int row, int col)
{
}

void MoveTiled::moveTo(int row, int col)
{
	this->m_row = row;
	this->m_col = col;
	this->setPosition(Vec2(col * GAME_TILED_WIDTH + GAME_TILED_BOARD * (col + 1), row * GAME_TILED_HEIGHT + GAME_TILED_BOARD * (row + 1)));
}

void MoveTiled::doubleNum()
{
	this->m_number *= 2;
	auto numBg = this->getChildByTag(110);
	auto numLabel = (Label *)numBg->getChildByTag(120);
	numLabel->setString(StringUtils::format("%d", this->m_number));
	numBg->runAction(Sequence::create(
		ScaleTo::create(0.1, 0.9),
		ScaleTo::create(0.1, 1.1),
		ScaleTo::create(0.1, 1),
		NULL
		));
	switch (this->m_number) {
	case 2:
		numBg->setColor(Color3B(238, 228, 218));
	case 4:
		numBg->setColor(Color3B(238, 223, 202));
		break;
	case 8:
		numBg->setColor(Color3B(242, 177, 122));
		numLabel->setColor(Color3B(255, 255, 255));
		break;
	case 16:
		numBg->setColor(Color3B(236, 141, 85));
		numLabel->setColor(Color3B(255, 255, 255));
		break;
	case 32:
		numBg->setColor(Color3B(230, 100, 90));
		numLabel->setColor(Color3B(255, 255, 255));
		break;
	case 64:
		numBg->setColor(Color3B(230, 70, 60));
		numLabel->setColor(Color3B(255, 255, 255));
		break;
	case 128:
		numBg->setColor(Color3B(230, 190, 60));
		numLabel->setColor(Color3B(255, 255, 255));
		break;
	case 256:
		numBg->setColor(Color3B(236, 220, 60));
		numLabel->setColor(Color3B(255, 255, 255));
		break;
	case 512:
		numBg->setColor(Color3B(242, 190, 75));
		numLabel->setColor(Color3B(255, 255, 255));
		break;
		//case 1024:
		//case 2048:
	default:
		numBg->setColor(Color3B(210, 180, 30));
		numLabel->setColor(Color3B(255, 255, 255));
		numLabel->setScale(0.5);
		break;
	}

}