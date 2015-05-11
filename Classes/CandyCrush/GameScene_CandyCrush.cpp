#include "GameScene_CandyCrush.h"
#include "WelcomeScene_CandyCrush.h"
#include "GameOver_CandyCrush.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

GameScene_CandyCrush::GameScene_CandyCrush()
	: spriteSheet(NULL)
	, isFillSprite(false)
	, isAction(true)
	, isTouchEna(true)
	, staSprite(NULL)
	, endSprite(NULL)
	, m_time(10)
	, m_score(0)
	
{
	mapLBX = (GAME_SCREEN_WIDTH - SPRITE_WIDTH * COLS - (COLS - 1) * BOADER_WIDTH) / 2;
	mapLBY = (GAME_SCREEN_HEIGHT - SPRITE_WIDTH * ROWS - (ROWS - 1) * BOADER_WIDTH) / 2;
}
GameScene_CandyCrush::~GameScene_CandyCrush()
{

}
Scene* GameScene_CandyCrush::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene_CandyCrush::create();
	scene->addChild(layer);
	return scene;
}

// 欢迎界面 初始化函数  
bool GameScene_CandyCrush::init()  {
	// 先初始化父类，不成功返回false  
	if (!Layer::init())    {
		return false;
	}
	// 加载plist和png
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CandyCrush/icon.plist");
	spriteSheet = SpriteBatchNode::create("CandyCrush/icon.png");
	this->addChild(spriteSheet);
	// 添加背景图片  
	auto sprite = Sprite::create("CandyCrush/scene_bg.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite, -1);

	// 添加返回按钮  
	auto backItem = MenuItemImage::create(
		"CandyCrush/btn_back01.png",
		"CandyCrush/btn_back02.png",
		CC_CALLBACK_1(GameScene_CandyCrush::menuBackCallback, this));
	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH - backItem->getContentSize().width / 2, backItem->getContentSize().height / 2));
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	// 加载ttf字体
	TTFConfig config("fonts/haibaoti.ttf", 30);
	// 分数显示 
	auto labelScore = Label::createWithTTF(config, StringUtils::format("Score: %d ", m_score));
	labelScore->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT - labelScore->getContentSize().height*2.6));
	labelScore->setTag(10);
	this->addChild(labelScore);
	// 最高分 
	if (!userDefault->getIntegerForKey("Int"))
	{
		userDefault->setIntegerForKey("Int", 0);
		userDefault->flush();
	}
	auto labelHScore = Label::createWithTTF(config, StringUtils::format("Highest: %d ", userDefault->getIntegerForKey("Int")));
	labelHScore->setPosition(Vec2(GAME_SCREEN_WIDTH - labelHScore->getContentSize().width, GAME_SCREEN_HEIGHT - labelHScore->getContentSize().height));
	this->addChild(labelHScore);

	// 游戏时间的显示 
	auto labelTime = Label::createWithTTF(config, StringUtils::format("Time:%d",m_time));
	labelTime->setPosition(Vec2(labelTime->getContentSize().width, GAME_SCREEN_HEIGHT - labelTime->getContentSize().height));
	labelTime->setTag(11);
	this->addChild(labelTime);

	//按键处理
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene_CandyCrush::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene_CandyCrush::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene_CandyCrush::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//生成精灵
	initMap();
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene_CandyCrush::myClock), 1.0f);

	return true;
}

void GameScene_CandyCrush::myClock(float ft)
{
	--m_time;
	if (m_time == 0)
	{
		Label *labelTime = (Label*)this->getChildByTag(11);
		labelTime->setScale(0);
		// 游戏结束 动画  
		auto gmov = Sprite::create("CandyCrush/pic_gameover.png");
		gmov->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT*1.5));
		gmov->runAction(MoveTo::create(3.0f, Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2)));
		this->addChild(gmov);
		scheduleOnce(schedule_selector(GameScene_CandyCrush::gameOver), 3.5f);
		return;
	}
	else
	{
		Label *labelTime = (Label*)this->getChildByTag(11);
		labelTime->setString(StringUtils::format("Time:%d", m_time));
	}
}

bool GameScene_CandyCrush::onTouchBegan(Touch *touch, Event *event)
{
	staSprite = NULL;
	endSprite = NULL;
	if (m_time <= 0)
	{
		return false;
	}
	if (isTouchEna)
	{
		auto location = touch->getLocation();
		staSprite = spriteOfPoint(&location);
	}
	return isTouchEna;
}
// 触摸后移动的方向 
void GameScene_CandyCrush::onTouchMoved(Touch *touch, Event *event)
{
	// 如果没有初始精灵 或者 触摸事件不可行，直接返回  
	if (!isTouchEna || !staSprite)
	{
		return;
	}
	int row = staSprite->getRow();
	int col = staSprite->getCol();
	// 获取移动到的 点 的位置  
	auto location = touch->getLocation();
	auto halfSpriteWidth = SPRITE_WIDTH / 2;
	auto halfSpriteHeight = SPRITE_WIDTH / 2;

	auto upRect = Rect(staSprite->getPositionX() - halfSpriteWidth, 
		staSprite->getPositionY() + halfSpriteHeight, 
		SPRITE_WIDTH, 
		SPRITE_WIDTH);
	if (upRect.containsPoint(location))
	{
		++row;
		if (row < ROWS)
		{
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}
	auto downRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
		staSprite->getPositionY() - (halfSpriteHeight * 3),
		SPRITE_WIDTH,
		SPRITE_WIDTH);
	if (downRect.containsPoint(location))
	{
		--row;
		if (row >= 0)
		{
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}

	auto leftRect = Rect(staSprite->getPositionX() - (halfSpriteWidth * 3),
		staSprite->getPositionY() - halfSpriteHeight,
		SPRITE_WIDTH,
		SPRITE_WIDTH);
	if (leftRect.containsPoint(location))
	{
		--col;
		if (row >= 0)
		{
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}


	auto  rightRect = Rect(staSprite->getPositionX() + halfSpriteWidth,
		staSprite->getPositionY() - halfSpriteHeight,
		SPRITE_WIDTH,
		SPRITE_WIDTH);
	if (rightRect.containsPoint(location)) {
		++col;
		if (col < COLS)
		{
			endSprite = map[row][col];
		}
		swapSprite();
		return;
	}


}
void GameScene_CandyCrush::onTouchEnded(Touch *touch, Event *event)
{

}
// 交换精灵  
void GameScene_CandyCrush::swapSprite()
{
	// 移动中，不允许再次触摸，执行动作设置为true  
	isAction = true;
	isTouchEna = false;

	if (!staSprite || !endSprite)
	{
		return;
	}

	Vec2 posOfSrc = staSprite->getPosition();
	Vec2 posOfDest = endSprite->getPosition();
	float time = 0.2f;
	// 在数组中交换位置 
	map[staSprite->getRow()][staSprite->getCol()] = endSprite;
	map[endSprite->getRow()][endSprite->getCol()] = staSprite;

	int tmpRow = staSprite->getRow();
	int tmpCol = staSprite->getCol();
	staSprite->setRow(endSprite->getRow());
	staSprite->setCol(endSprite->getCol());
	endSprite->setRow(tmpRow);
	endSprite->setCol(tmpCol);

	// 检查是否能消除  
	std::list<SpriteShape_CandyCrush *> colChainListOfFirst;
	getColChain(staSprite, colChainListOfFirst);

	std::list<SpriteShape_CandyCrush *> rowChainListOfFirst;
	getRowChain(staSprite, rowChainListOfFirst);

	std::list<SpriteShape_CandyCrush *> colChainListOfSecond;
	getColChain(endSprite, colChainListOfSecond);

	std::list<SpriteShape_CandyCrush *> rowChainListOfSecond;
	getRowChain(endSprite, rowChainListOfSecond);

	if (colChainListOfFirst.size() >= MIN_EQUAL
		|| rowChainListOfFirst.size() >= MIN_EQUAL
		|| colChainListOfSecond.size() >= MIN_EQUAL
		|| rowChainListOfSecond.size() >= MIN_EQUAL)
	{
		// 如果能够消除，仅仅进行移动（不会移动回来） 
		staSprite->runAction(MoveTo::create(time, posOfDest));
		endSprite->runAction(MoveTo::create(time, posOfSrc));
		return;
	}

	// 不能消除，则移动过去还要返回  
	map[staSprite->getRow()][staSprite->getCol()] = endSprite;
	map[endSprite->getRow()][endSprite->getCol()] = staSprite;
	tmpRow = staSprite->getRow();
	tmpCol = staSprite->getCol();
	staSprite->setRow(endSprite->getRow());
	staSprite->setCol(endSprite->getCol());
	endSprite->setRow(tmpRow);
	endSprite->setCol(tmpCol);
	staSprite->runAction(Sequence::create(
		MoveTo::create(time, posOfDest),
		MoveTo::create(time, posOfSrc),
		NULL));
	endSprite->runAction(Sequence::create(
		MoveTo::create(time, posOfSrc),
		MoveTo::create(time, posOfDest),
		NULL));
}

// 根据触摸的点位置，返回是地图中哪个精灵
SpriteShape_CandyCrush *GameScene_CandyCrush::spriteOfPoint(Vec2 *vec2)
{
	SpriteShape_CandyCrush *spr = NULL;
	Rect rect = Rect(0, 0, 0, 0);
	Size sz;
	sz.height = SPRITE_WIDTH;
	sz.width = SPRITE_WIDTH;

	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			spr = map[r][c];
			if (spr)
			{
				rect.origin.x = spr->getPositionX() - (SPRITE_WIDTH / 2);
				rect.origin.y = spr->getPositionY() - (SPRITE_WIDTH / 2);
				rect.size = sz;
				if (rect.containsPoint(*vec2))
				{
					return spr;
				}
			}
		}
	}
	return NULL;

}
void GameScene_CandyCrush::menuBackCallback(Ref *pSender)
{
	auto scene = WelcomeScene_CandyCrush::createScene();
	Director::getInstance()->replaceScene(scene);
}

// 初始化地图
void GameScene_CandyCrush::initMap()
{
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			createSprite(r,c);
		}
	}
}
// 创建精灵 
void GameScene_CandyCrush::createSprite(int row, int col)
{
	// 先创建一个寿司  
	SpriteShape_CandyCrush *spr = SpriteShape_CandyCrush::create(row, col);
	Vec2 endPos = positionOfItem(row, col);
	Vec2 startPos = Vec2(endPos.x, endPos.y + GAME_SCREEN_HEIGHT / 2);
	spr->setPosition(startPos);
	float speed = startPos.y / (1.5f * GAME_SCREEN_HEIGHT);
	spr->runAction(MoveTo::create(speed, endPos));
	// 加入到spriteSheet中,等待绘制
	spriteSheet->addChild(spr);
	// 数组相应位置，置上寿司对象  
	map[row][col] = spr;
}
// 根据行列，获取坐标值
Vec2 GameScene_CandyCrush::positionOfItem(int row, int col)
{
	float x = mapLBX + (SPRITE_WIDTH + BOADER_WIDTH) * col + SPRITE_WIDTH / 2;
	float y = mapLBY + (SPRITE_WIDTH + BOADER_WIDTH) * row + SPRITE_WIDTH / 2;
	return Vec2(x, y);
}

void GameScene_CandyCrush::update(float dt)
{
	if (isAction)
	{
		isAction = false;
		// 扫描一遍所有精灵，看有没有可以消除的  
		for (int r = 0; r < ROWS; ++r)
		{
			for (int c = 0; c < COLS; ++c)
			{
				SpriteShape_CandyCrush *spr = map[r][c];
				if (spr && spr->getNumberOfRunningActions() > 0)
				{
					isAction = true;
					break;
				}
			}
		}
	}

	// 如果精灵正在移动中，忽视触摸事件
	isTouchEna = !isAction;

	if (!isAction)
	{
		// 是否有精灵需要填补  
		if (isFillSprite)
		{
			//爆炸效果结束后才掉落新寿司，增强打击感  
			fillSprite();
			isFillSprite = false;
		}
		else
		{
			checkAndRemoveSprite();
		}
	}
	// 分数变化  
	Label *labelScore = (Label *)this->getChildByTag(10);
	labelScore->setString(StringUtils::format("Score: %d ", m_score));
}

// 检测是否有精灵可以移除
void GameScene_CandyCrush::checkAndRemoveSprite()
{
	SpriteShape_CandyCrush *spr;
	// 设定寿司的忽视检查，之前可能有精灵设置忽视检查，但这次检查要将之前所有的检查都不能忽视  
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			spr = map[r][c];
			if (spr)
			{
				spr->setIgnoreCheck(false);
			}
		}
	}
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			spr = map[r][c];
			if (!spr)
			{
				continue;
			}
			// 如果该精灵已经被扔到 要删除的List中，则不需要再检测它  
			if (spr->getIsNeedRemove())
			{
				continue;
			}
			// 如果该精灵是新生成的精灵 
			if (spr->getIgnoreCheck())
			{
				continue;
			}

			// 建立一个list 存储在本精灵周围（上下）与本精灵相同的精灵  
			std::list<SpriteShape_CandyCrush*> colChainList;
			getColChain(spr, colChainList);
			// 建立一个list 存储在本精灵周围（左右）与本精灵相同的精灵  
			std::list<SpriteShape_CandyCrush*> rowChainList;
			getRowChain(spr, rowChainList);

			//std::list<SpriteShape_CandyCrush*> longerList = colChainList.size() > rowChainList.size() ? colChainList : rowChainList;
			//// 如果相同精灵的个数小于3个 则跳过  
			//if (longerList.size() < MIN_EQUAL)
			//{
			//	continue;
			//}
			//3个以上
			std::list<SpriteShape_CandyCrush*> longerList;
			if (colChainList.size() >= rowChainList.size())
			{
				if (colChainList.size() < MIN_EQUAL)
				{
					continue;
				}
				longerList = colChainList;
				isRow = false;
			}
			else
			{
				if (rowChainList.size() < MIN_EQUAL)
				{
					continue;
				}
				longerList = rowChainList;
				isRow = true;
			}

			// 标志 是否需要设定忽视检查的精灵  
			bool isSetedIgnoreCheck = false;
			std::list<SpriteShape_CandyCrush*>::iterator itList;
			for (itList = longerList.begin(); itList != longerList.end(); ++itList)
			{
				spr = (SpriteShape_CandyCrush*)*itList;
				if (!spr)
				{
					continue;
				}
				//3个以上
				if (longerList.size() > MIN_EQUAL)
				{
					if (spr == staSprite || spr == endSprite)
					{
						isSetedIgnoreCheck = true;
						spr->setIgnoreCheck(true);
						spr->setIsNeedRemove(false);
						spr->setDisplayMode(isRow ? DISPLAY_MODE_HORIZONTAL : DISPLAY_MODE_VERTICAL);
						continue;
					}
				}
				// 标记要消除的精灵  
				markRemove(spr);
			}
			// 如何是自由掉落产生的4消, 取最后一个变化为特殊精灵 //3个以上
			if (!isSetedIgnoreCheck && longerList.size() > MIN_EQUAL)
			{
				spr->setIgnoreCheck(true);
				spr->setIsNeedRemove(false);
				spr->setDisplayMode(isRow ? DISPLAY_MODE_HORIZONTAL : DISPLAY_MODE_VERTICAL);
			}
		}

	}

	// 消除标记了的精灵  
	removeSprite();
}

void GameScene_CandyCrush::markRemove(SpriteShape_CandyCrush *spr)
{
	if (spr->getIsNeedRemove())
	{
		return;
	}
	spr->setIsNeedRemove(true);
}

void GameScene_CandyCrush::removeSprite()
{
	// 做一套移除的动作  
	isAction = true;
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			SpriteShape_CandyCrush *spr = map[r][c];
			if (spr && spr->getIsNeedRemove())
			{
				isFillSprite = true;

				if (spr->getDisplayMode() == DISPLAY_MODE_HORIZONTAL)
				{
					explodeSpecialH(spr->getPosition());
				}
				else if (spr->getDisplayMode() == DISPLAY_MODE_VERTICAL)
				{
					explodeSpecialV(spr->getPosition());
				}
				explodeSprite(spr);
			}
		}
	}
}

void GameScene_CandyCrush::explodeSprite(SpriteShape_CandyCrush *spr)
{

	SimpleAudioEngine::getInstance()->playEffect("CandyCrush/music_explode.wav");
	float time = 0.2f;
	spr->runAction(Sequence::create(ScaleTo::create(time, 0.0f), CallFuncN::create(CC_CALLBACK_1(GameScene_CandyCrush::actionEndCallback, this)), NULL));
	auto circleSprite = Sprite::create("CandyCrush/circle.png");
	circleSprite->setPosition(spr->getPosition());
	circleSprite->setScale(0);
	circleSprite->runAction(Sequence::create(ScaleTo::create(time, 1.0f), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, circleSprite)), NULL));
	this->addChild(circleSprite,10);
}
// 精灵的横向消除  
void GameScene_CandyCrush::explodeSpecialH(Vec2 point)
{
	SimpleAudioEngine::getInstance()->playEffect("CandyCrush/music_explodeOne.wav");
	// 先设置相应的变量  
	float scaleX = 4.0f;
	float scaleY = 0.7f;
	float time = 0.3f;
	Point startPosition = point;
	float speed = 0.6f;

	auto colorSpriteRight = Sprite::create("CandyCrush/colorHRight.png");
	addChild(colorSpriteRight, 10);
	Point endPosition1 = Point(point.x - GAME_SCREEN_WIDTH, point.y);
	colorSpriteRight->setPosition(startPosition);
	colorSpriteRight->runAction(Sequence::create(
		ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition1),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteRight)),
		NULL));

	auto colorSpriteLeft = Sprite::create("CandyCrush/colorHLeft.png");
	addChild(colorSpriteLeft, 10);
	Point endPosition2 = Point(point.x + GAME_SCREEN_WIDTH, point.y);
	colorSpriteLeft->setPosition(startPosition);
	colorSpriteLeft->runAction(Sequence::create(
		ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition2),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteLeft)),
		NULL));


}

// 精灵的纵向消除  
void GameScene_CandyCrush::explodeSpecialV(Point point)
{
	SimpleAudioEngine::getInstance()->playEffect("CandyCrush/music_explodeOne.wav");
	float scaleY = 4.0f;
	float scaleX = 0.7f;
	float time = 0.3f;
	Point startPosition = point;
	float speed = 0.6f;

	auto colorSpriteDown = Sprite::create("CandyCrush/colorVDown.png");
	addChild(colorSpriteDown, 10);
	Point endPosition1 = Point(point.x, point.y - GAME_SCREEN_HEIGHT);
	colorSpriteDown->setPosition(startPosition);
	colorSpriteDown->runAction(Sequence::create(
		ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition1),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteDown)),
		NULL));

	auto colorSpriteUp = Sprite::create("CandyCrush/colorVUp.png");
	addChild(colorSpriteUp, 10);
	Point endPosition2 = Point(point.x, point.y + GAME_SCREEN_HEIGHT);
	colorSpriteUp->setPosition(startPosition);
	colorSpriteUp->runAction(Sequence::create(
		ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition2),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteUp)),
		NULL));


}

void GameScene_CandyCrush::actionEndCallback(Node *node)
{
	SpriteShape_CandyCrush *spr = (SpriteShape_CandyCrush*)node;
	map[spr->getRow()][spr->getCol()] = NULL;
	spr->removeFromParent();
}

// 纵向检查  
void GameScene_CandyCrush::getColChain(SpriteShape_CandyCrush *spr, std::list<SpriteShape_CandyCrush *> &chainList)
{
	// 添加第一个精灵（自己）
	chainList.push_back(spr);
	// 向左查找 
	int neighborCol = spr->getCol() - 1;
	while (neighborCol >= 0)
	{
		SpriteShape_CandyCrush *neighborSpr = map[spr->getRow()][neighborCol];
		if (neighborSpr && !neighborSpr->getIsNeedRemove() && neighborSpr->getImgIndex() == spr->getImgIndex())
		{
			chainList.push_back(neighborSpr);
			--neighborCol;
		}
		else
		{
			break;
		}
	}

	// 向右查找  
	neighborCol = spr->getCol() + 1;
	while (neighborCol < COLS)
	{
		SpriteShape_CandyCrush *neighborSpr = map[spr->getRow()][neighborCol];
		if (neighborSpr && !neighborSpr->getIsNeedRemove() && neighborSpr->getImgIndex() == spr->getImgIndex())
		{
			chainList.push_back(neighborSpr);
			++neighborCol;
		}
		else
		{
			break;
		}
	}
}
// 横向检查  
void GameScene_CandyCrush::getRowChain(SpriteShape_CandyCrush *spr, std::list<SpriteShape_CandyCrush *> &chainList)
{
	chainList.push_back(spr);
	// 向上查找 
	int neighborRow = spr->getRow() - 1;
	while (neighborRow >= 0)
	{
		SpriteShape_CandyCrush *neighborSpr = map[neighborRow][spr->getCol()];
		if (neighborSpr && !neighborSpr->getIsNeedRemove() && neighborSpr->getImgIndex() == spr->getImgIndex())
		{
			chainList.push_back(neighborSpr);
			--neighborRow;
		}
		else
		{
			break;
		}
	}

	// 向下查找  
	neighborRow = spr->getRow() + 1;
	while (neighborRow < ROWS)
	{
		SpriteShape_CandyCrush *neighborSpr = map[neighborRow][spr->getCol()];
		if (neighborSpr && !neighborSpr->getIsNeedRemove() && neighborSpr->getImgIndex() == spr->getImgIndex())
		{
			chainList.push_back(neighborSpr);
			++neighborRow;
		}
		else
		{
			break;
		}
	}
}

// 填补空缺位置
void GameScene_CandyCrush::fillSprite()
{
	// 下落精灵总个数（方便后面分数的计算）  
	int sum = 0;
	isAction = true;
	int *colEmptyInfo = (int*)malloc(sizeof(int) * COLS);
	// 将存在的精灵降落下来  
	SpriteShape_CandyCrush *spr = NULL;
	for (int c = 0; c < COLS; ++c)
	{
		int removedSpriteOfCol = 0;
		// 自底向上  
		for (int r = 0; r < ROWS; ++r)
		{
			spr = map[r][c];
			if (spr == NULL)
			{
				++removedSpriteOfCol;
			}
			else
			{

				if (removedSpriteOfCol > 0)
				{
					int newRow = r - removedSpriteOfCol;
					map[newRow][c] = spr;
					map[r][c] = NULL;

					Vec2 startPos = spr->getPosition();
					Vec2 endPos = positionOfItem(newRow, c);
					float speed = (startPos.y - endPos.y) / GAME_SCREEN_HEIGHT * 3;
					spr->stopAllActions();
					spr->runAction(MoveTo::create(speed, endPos));
					spr->setRow(newRow);
				}
			}
			
		}
		// 记录相应列数移除的数量
		colEmptyInfo[c] = removedSpriteOfCol;
		sum += removedSpriteOfCol;
	}

	// 新建新的精灵，并降落  
	for (int c = 0; c < COLS; ++c)
	{
		for (int r = ROWS - colEmptyInfo[c]; r < ROWS; ++r)
		{
			createSprite(r, c);
		}
	}
	m_score += sum * 30;
	free(colEmptyInfo);
}

void GameScene_CandyCrush::gameOver(float f)
{
	auto scene = Scene::create();
	auto layer = GameOver_CandyCrush::create();
	layer->setScore(m_score);
	scene->addChild(layer);

	TransitionScene* reScene = TransitionFadeUp::create(1.0f, scene);
	Director::getInstance()->replaceScene(reScene);
}

void GameScene_CandyCrush::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE);
}
void GameScene_CandyCrush::onExit()
{
	Layer::onExit();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(MUSIC_FILE);
}