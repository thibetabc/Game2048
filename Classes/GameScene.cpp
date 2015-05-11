#include "GameScene.h"
#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "MidMenu.h"
#include "ChineseString.h"
#include "MainMenu.h"


using namespace CocosDenshion;


GameScene::GameScene()
{
	m_score = 0;
	m_isNewMoveTiled = true;
}
GameScene::~GameScene()
{
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*
	初始化
	*/
	auto labelScore = Label::createWithTTF(TTF_RES_PATH, "SCORE:0");
	labelScore->setSystemFontSize(TTF_FONT_SIZE);
	labelScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - TTF_FONT_SIZE));
	labelScore->setTag(10);
	this->addChild(labelScore);

	//标题
	auto label = Label::createWithTTF(TTF_RES_PATH, ChineseString::a2u("菜单"));
	label->setSystemFontSize(TTF_FONT_SIZE);
	if (false)
	{
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 120));
		this->addChild(label);
	}
	else
	{
		auto mil = MenuItemLabel::create(label, [&](Ref *pSender){

			if (UserDefault::getInstance()->getIntegerForKey(AUDIO_DEFAULT) > 0)
			{
				SimpleAudioEngine::getInstance()->playEffect(AUDIO_PLAY_PATH);
			}
			Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, MidMenu::createScene()));

		});
		auto menu = Menu::create(mil, nullptr);
		menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 80));
		this->addChild(menu);
	}

	//退出
	auto exitLab = Label::createWithTTF(TTF_RES_PATH, ChineseString::a2u("退出"));
	exitLab->setSystemFontSize(TTF_FONT_SIZE);
	Size exitLabSize = exitLab->getContentSize();
	auto exitItem = MenuItemLabel::create(exitLab, [&](Ref *pSender){
		if (UserDefault::getInstance()->getIntegerForKey(AUDIO_DEFAULT) > 0)
		{
			SimpleAudioEngine::getInstance()->playEffect(AUDIO_PLAY_PATH);
		}
		Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, MainMenu::createScene()));

	});
	auto menu = Menu::create(exitItem, nullptr);
	menu->setPosition(Vec2(visibleSize.width - exitLabSize.width/2, exitLabSize.height/2));
	this->addChild(menu);

	//音乐是否开启
	int audioTag = UserDefault::getInstance()->getIntegerForKey(AUDIO_DEFAULT);
	if (audioTag == 0)
	{
		audioTag = 1;
		UserDefault::getInstance()->setIntegerForKey(AUDIO_DEFAULT, audioTag);
	}
	
	//背景
	m_bgColor = LayerColor::create(Color4B(170, 170, 170, 255),
		GAME_TILED_WIDTH*GAME_COLS + GAME_TILED_BOARD*(GAME_COLS + 1), 
		GAME_TILED_HEIGHT*GAME_ROWS + GAME_TILED_BOARD*(GAME_ROWS + 1));
	m_bgColor->setPosition((visibleSize - m_bgColor->getContentSize()) / 2);
	this->addChild(m_bgColor);

	//背景单元格子
	for (int col = 0; col < GAME_COLS; col++)
	{
		for (int row = 0; row < GAME_ROWS; row++)
		{
			auto layerColor = LayerColor::create(Color4B(70, 70, 70, 255), GAME_TILED_WIDTH, GAME_TILED_HEIGHT);
			layerColor->setPosition(Vec2(GAME_TILED_WIDTH * col + GAME_TILED_BOARD * (col + 1), GAME_TILED_HEIGHT * row + GAME_TILED_BOARD * (row + 1)));
			m_bgColor->addChild(layerColor);
		}
	}

	//格子数据
	for (int i = 0; i < GAME_ROWS; i++)
	{
		for (int j = 0; j < GAME_COLS; j++)
		{
			m_map[i][j] = 0;
		}
	}

	//产生可以移动的数字块
	newMoveTiled();
	newMoveTiled();


	//触摸处理
	auto event = EventListenerTouchOneByOne::create();
	event->onTouchBegan = [&](Touch *touch, Event *event)
	{
		m_isMove = true;
		m_moveX = touch->getLocation().x;
		m_moveY = touch->getLocation().y;
		return true;
	};
	event->onTouchMoved = [&](Touch *touch, Event *event)
	{
		int x = touch->getLocation().x;
		int y = touch->getLocation().y;
		if (m_isMove && (abs(m_moveX - x) > 10 || abs(m_moveY - y) > 10))
		{
			m_isMove = false;

			if (abs(m_moveX - x) > abs(m_moveY - y)) //左右
			{
				if (m_moveX > x)
				{
					m_dir = MOVE_DIR::LEFT;
				}
				else
				{
					m_dir = MOVE_DIR::RIGHT;
				}
			}
			else
			{
				if (m_moveY > y)
				{
					m_dir = MOVE_DIR::DOWN;
				}
				else
				{
					m_dir = MOVE_DIR::UP;
				}
			}

			moveAllTiled(m_dir); //移动所有块
		}
	};
	event->onTouchEnded = [&](Touch *touch, Event *event){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
	return true;
}

Scene *GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::moveAllTiled(MOVE_DIR dir)
{
	m_isNewMoveTiled = false;
	m_isSoundClear = false;
	switch (dir)
	{
	case MOVE_DIR::UP:
		moveUp();
		break;
	case MOVE_DIR::DOWN:
		moveDown();
		break;
	case MOVE_DIR::LEFT:
		moveLeft();
		break;
	case MOVE_DIR::RIGHT:
		moveRight();
		break;
	default:
		break;
	}
	if (UserDefault::getInstance()->getIntegerForKey(AUDIO_DEFAULT) > 0)
	{
		if (m_isSoundClear)
		{
			SimpleAudioEngine::getInstance()->playEffect(AUDIO_PLAY_PATH);
		}
		else
		{
			SimpleAudioEngine::getInstance()->playEffect(AUDIO_MOVE_PATH);
		}
	}
	newMoveTiled();
}

void GameScene::moveUp()
{
	//0.向上移动所有的块
	for (int col = 0; col < GAME_COLS; col++)
	{
		for (int row = GAME_ROWS - 1; row >= 0; row--)
		{
			if (m_map[row][col] > 0) //1.当前格子不为空
			{
				for (int upRow = row; upRow < GAME_ROWS - 1; upRow++)
				{					
					if (m_map[upRow + 1][col] == 0)//2.上一格子为空:往上移动
					{
						m_map[upRow + 1][col] = m_map[upRow][col];
						m_mtVector.at(m_map[upRow + 1][col] - 1)->moveTo(upRow + 1, col);
						m_map[upRow][col] = 0;
						m_isNewMoveTiled = true;
					}
					else
					{
						//3.上一格子不空，看是否相同;如果相同，前两个相加合并，并把
						auto upMoveTiled = m_mtVector.at(m_map[upRow + 1][col] - 1);
						auto curMoveTiled = m_mtVector.at(m_map[upRow][col] - 1);
						if (upMoveTiled->m_number == curMoveTiled->m_number)
						{
							m_score += upMoveTiled->m_number * 2;
							upMoveTiled->doubleNum();//前一个相加
							curMoveTiled->removeFromParent();//后一个消失
							//比m_map[upRow][col]大的都减一
							removeMoveTiled(upRow, col);							
						}
						break;
					}
				}
			}
		}
	}
}
void GameScene::moveDown()
{
	//0.向下移动所有的块
	for (int col = 0; col < GAME_COLS; col++)
	{
		for (int row = 0; row < GAME_ROWS; row++)
		{
			if (m_map[row][col] > 0) //1.当前格子不为空
			{
				for (int upRow = row; upRow > 0; upRow--)
				{
					if (m_map[upRow - 1][col] == 0)//2.上一格子为空:往上移动
					{
						m_map[upRow - 1][col] = m_map[upRow][col];
						m_mtVector.at(m_map[upRow - 1][col] - 1)->moveTo(upRow - 1, col);
						m_map[upRow][col] = 0;
						m_isNewMoveTiled = true;
					}
					else
					{
						//3.上一格子不空，看是否相同;如果相同，前两个相加合并，并把
						auto upMoveTiled = m_mtVector.at(m_map[upRow - 1][col] - 1);
						auto curMoveTiled = m_mtVector.at(m_map[upRow][col] - 1);
						if (upMoveTiled->m_number == curMoveTiled->m_number)
						{
							m_score += upMoveTiled->m_number * 2;
							upMoveTiled->doubleNum();//前一个相加
							curMoveTiled->removeFromParent();//后一个消失
							//比m_map[upRow][col]大的都减一
							removeMoveTiled(upRow, col);
						}
						break;
					}
				}
			}
		}
	}

}
void GameScene::moveLeft()
{
	//0.向左移动所有的块	
	for (int row = 0; row < GAME_ROWS; row++)
	{
		for (int col = 0; col < GAME_COLS; col++)
		{
			if (m_map[row][col] > 0) //1.当前格子不为空
			{
				for (int upCol = col; upCol > 0; upCol--)
				{
					if (m_map[row][upCol - 1] == 0)//2.上一格子为空:往上移动
					{
						m_map[row][upCol - 1] = m_map[row][upCol];
						m_mtVector.at(m_map[row][upCol - 1] - 1)->moveTo(row, upCol - 1);
						m_map[row][upCol] = 0;
						m_isNewMoveTiled = true;
					}
					else
					{
						//3.上一格子不空，看是否相同;如果相同，前两个相加合并，并把
						auto upMoveTiled = m_mtVector.at(m_map[row][upCol - 1] - 1);
						auto curMoveTiled = m_mtVector.at(m_map[row][upCol] - 1);
						if (upMoveTiled->m_number == curMoveTiled->m_number)
						{
							m_score += upMoveTiled->m_number * 2;
							upMoveTiled->doubleNum();//前一个相加
							curMoveTiled->removeFromParent();//后一个消失
							//比m_map[row][upCol]大的都减一
							removeMoveTiled(row, upCol);

						}
						break;
					}
				}
			}
		}
	}
}
void GameScene::moveRight()
{
	//0.向左移动所有的块	
	for (int row = 0; row < GAME_ROWS; row++)
	{
		for (int col = GAME_COLS - 1; col >= 0; col--)
		{
			if (m_map[row][col] > 0) //1.当前格子不为空
			{
				for (int upCol = col; upCol < GAME_COLS - 1; upCol++)
				{
					if (m_map[row][upCol + 1] == 0)//2.上一格子为空:往上移动
					{
						m_map[row][upCol + 1] = m_map[row][upCol];
						m_mtVector.at(m_map[row][upCol + 1] - 1)->moveTo(row, upCol + 1);
						m_map[row][upCol] = 0;
						m_isNewMoveTiled = true;
					}
					else
					{
						//3.上一格子不空，看是否相同;如果相同，前两个相加合并，并把
						auto upMoveTiled = m_mtVector.at(m_map[row][upCol + 1] - 1);
						auto curMoveTiled = m_mtVector.at(m_map[row][upCol] - 1);
						if (upMoveTiled->m_number == curMoveTiled->m_number)
						{
							m_score += upMoveTiled->m_number * 2;
							upMoveTiled->doubleNum();//前一个相加
							curMoveTiled->removeFromParent();//后一个消失
							//比m_map[row][upCol]大的都减一
							removeMoveTiled(row, upCol);
						}
						break;
					}
				}
			}
		}
	}

}

//产生可以移动的数字块
void GameScene::newMoveTiled()
{
	int freeCount = (GAME_ROWS*GAME_COLS - m_mtVector.size()); //剩余空格
	if (freeCount == 0)
	{
		gameOver();
		return;
	}

	//格子移动过或者合并过，才生产新的
	if (!m_isNewMoveTiled)
	{
		return;
	}
	int num = cocos2d::random() % freeCount;
	bool isFind = false;
	int count = -1;
	int row = 0;//记录空格子的行
	int col = 0;//记录空格子的列
	for (; row < GAME_ROWS; row++)
	{
		for (col = 0; col < GAME_COLS; col++)
		{
			if (m_map[row][col] == 0)
			{
				if (++count == num)
				{
					isFind = true;
					break;
				}
			}
		}
		if (isFind)
		{
			break;
		}
	}

	auto tiled = MoveTiled::create();
	tiled->moveTo(row, col);
	m_bgColor->addChild(tiled);
	m_mtVector.pushBack(tiled);
	m_map[row][col] = m_mtVector.getIndex(tiled) + 1;
}

void GameScene::removeMoveTiled(int row, int col)
{

	m_isSoundClear = true;
	m_mtVector.erase(m_map[row][col] - 1); //清除m_mtVector元素
	//比m_map[upRow][col]大的都减一
	for (int r = 0; r < GAME_ROWS; r++)
	{
		for (int c = 0; c < GAME_COLS; c++)
		{
			if (m_map[r][c] > m_map[row][col])
			{
				m_map[r][c]--;
			}
		}
	}
	m_map[row][col] = 0;//后一个数据清空

	//加分：
	auto labelScore = (Label *)this->getChildByTag(10);
	labelScore->setString(StringUtils::format("SCORE:%d", m_score));
	m_isNewMoveTiled = true;
}


void GameScene::gameOver()
{
	//判定游戏输赢
	//上 ，下 左 右 是否还能移动
	for (int row = 0; row < GAME_ROWS; row++)
	{
		for (int col = 0; col < GAME_COLS; col++)
		{
			////第r行 第c列的数值
			int curNum = m_mtVector.at(m_map[row][col] - 1)->m_number;
			//上
			if (row + 1 < GAME_ROWS)
			{
				if (curNum == m_mtVector.at(m_map[row + 1][col] - 1)->m_number)
				{
					return;
				}
			}
			//下
			if (row - 1 >= 0)
			{
				if (curNum == m_mtVector.at(m_map[row - 1][col] - 1)->m_number)
				{
					return;
				}
			}
			//左
			if (col + 1 < GAME_COLS)
			{
				if (curNum == m_mtVector.at(m_map[row][col + 1] - 1)->m_number)
				{
					return;
				}
			}
			//右
			if (col - 1 >= 0)
			{
				if (curNum == m_mtVector.at(m_map[row][col - 1] - 1)->m_number)
				{
					return;
				}
			}
		}
	}

	if (true)
	{
		//弹出GameOver图层，下层显示格子
		auto size = Director::getInstance()->getVisibleSize();
		auto layer = LayerColor::create(Color4B(0, 0, 0, 127), size.width, size.height);
		this->addChild(layer, 100);
		layer->ignoreAnchorPointForPosition(true);

		auto label = Label::createWithTTF(TTF_RES_PATH, "GameOver!");
		label->setColor(Color3B::WHITE);
		label->setSystemFontSize(TTF_FONT_SIZE);
		label->setPosition(Director::getInstance()->getVisibleSize() / 2);
		layer->addChild(label);

		auto eventTouch = EventListenerTouchOneByOne::create();
		eventTouch->setSwallowTouches(true);
		eventTouch->onTouchBegan = [&](Touch *touch, Event *event){
			return true;
		};
		eventTouch->onTouchMoved = [&](Touch *touch, Event *event){};
		eventTouch->onTouchEnded = [&](Touch *touch, Event *event){
			Director::getInstance()->replaceScene(TransitionZoomFlipX::create(0.5f, MainMenu::createScene()));
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(eventTouch, layer);
	}
	else
	{
		//直接跳转GameOverScene场景，不显示格子状态
		Director::getInstance()->replaceScene(TransitionZoomFlipX::create(0.5f, GameOver::createScene()));
	}


}
