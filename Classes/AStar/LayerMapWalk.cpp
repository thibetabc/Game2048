#include "LayerMapWalk.h"
#include "AStar/Graph.h"
#include "MapWalkVertex.h"
#include "json/writer.h"
#include "json/reader.h"
#include <iostream> 
#include <fstream>
#include "RoleKaito.h"
#include "AStar/Dijkstra.h"
#include "AStar/Spfa.h"
#include "AStar/AStar.h"
#include "LayerHudControl.h"
#include "AStarDefine.h"

#define ZOrderLine -1 
#define ZOrderVertex 2 
#define ZOrderRole  3 


LayerMapWalk::LayerMapWalk()
{
	m_pGraph = nullptr;
}


LayerMapWalk::~LayerMapWalk()
{
	if (m_pGraph)
	{
		delete m_pGraph;
	}
}

bool LayerMapWalk::init()
{
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setTouchEnabled(true);
	m_Mode = OperationMode::PutVertex;

	// 背景图
	//auto pSpr = Sprite::create( RES_URL + "map_bg.png" ) ; 
	//this->addChild( pSpr , -2 ) ; 

	// 初始化编辑数据
	auto pSprEdgeEditLine = Sprite::create(RES_URL + "line.png");
	//pSprEdgeEditLine->setColor( Color3B( 0 , 0 , 255 ) ) ; 
	m_EditData.pSprEdgeLine = pSprEdgeEditLine;
	this->addChild(pSprEdgeEditLine);
	pSprEdgeEditLine->setVisible(false);
	pSprEdgeEditLine->setAnchorPoint(Point(0, 0.5));


	// 初始化角色
	m_pRole = RoleKaito::create();
	m_pRole->setPosition(100, 100);
	m_pRole->setLocalZOrder(ZOrderRole);
	this->addChild(m_pRole);
	m_pRole->setVisible(false);


	// 初始化ID分配表
	for (int i = 0; i < 1000; ++i)
	{
		char sz[100];
		sprintf(sz, "%d", i);
		m_VertexIdTable[sz] = 0;
	}

	m_pGraph = new Graph();

	return true;
}


bool LayerMapWalk::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocation();

	switch (m_Mode)
	{

		case OperationMode::PutVertex:
		{
			// 坐标变换
			pos = this->convertToNodeSpaceAR(pos);
			auto pMwv = HitMapWalkVertex(pos);
			if (pMwv)
			{
				m_Mode = OperationMode::DragEdge;
				auto pSprLine = m_EditData.pSprEdgeLine;
				pSprLine->setPosition(pos);
				pSprLine->setVisible(true);
				MakeLine(pSprLine, pSprLine->getPosition(), pos);
				m_EditData.pMwv = pMwv;
			}
			else
			{
				// 创建地图行走的顶点
				auto pMwv = MapWalkVertex::create();
				pMwv->setPosition(pos);
				AddVertex(pMwv);

			}
		}
		break;


		case OperationMode::DragContent:
		{
			m_EditData.ptDrag = pos - this->getPosition();
		}
		break;


		case OperationMode::PositionRole:
		{
			// 坐标变换
			pos = this->convertToNodeSpaceAR(pos);

			auto pMwv = HitMapWalkVertex(pos);
			if (pMwv)
			{
				m_pRole->setPosition(pMwv->getPosition());
				m_pRole->setVisible(true);
				m_pRole->UserData["StartVertex"] = pMwv;
			}
		}
		break;


		case OperationMode::RoleWalk:
		{
			pos = this->convertToNodeSpaceAR(pos);
			auto pMwv = HitMapWalkVertex(pos);
			if (pMwv)
			{
				auto pVertexTarget = pMwv->GetGraphVertex();
				// 起点
				MapWalkVertex* pMwvStart = (MapWalkVertex*)m_pRole->UserData["StartVertex"];

				int nTimeStart;
				int Elapsed;
				char sz[256];
				string strElapseds;

				// 计算最短路径。用Dijkstra
				nTimeStart = ::clock();
				Dijkstra Dijkstra;
				Dijkstra.Execute(*m_pGraph, pMwvStart->GetGraphVertex()->GetId());
				Elapsed = ::clock() - nTimeStart;
				sprintf(sz, "Dijkstra : %d ms \n", Elapsed);
				strElapseds += sz;

				// 用 Spfa
				nTimeStart = ::clock();
				Spfa spfa;
				spfa.Execute(*m_pGraph, pMwvStart->GetGraphVertex()->GetId());
				Elapsed = ::clock() - nTimeStart;
				sprintf(sz, "Spfa : %d ms \n", Elapsed);
				strElapseds += sz;


				//用 AStar
				nTimeStart = ::clock();
				
				// A*的Ｈ估价函数
				auto Estimate = [](const Vertex *pVCurrent, const Vertex *pVTarget)->int
				{
					MapWalkVertex *pMwv1 = (MapWalkVertex *)pVCurrent->UserData.find("mwv")->second;
					MapWalkVertex *pMwv2 = (MapWalkVertex *)pVTarget->UserData.find("mwv")->second;
					Point v = pMwv1->getPosition() - pMwv2->getPosition();
					int H = v.getLength();
					return H;
				};

				AStar AStar;
				// 设置目的顶点
				AStar.SetTarget(pVertexTarget);
				// 设置Ｈ估价函数
				AStar.Estimate = Estimate;
				// 开始执行
				AStar.Execute(*m_pGraph, pMwvStart->GetGraphVertex()->GetId());
				Elapsed = ::clock() - nTimeStart;
				sprintf(sz, "AStar : %d ms \n", Elapsed);
				strElapseds += sz;


				m_pLayerHudControl->m_pTxtInfo2->setString(strElapseds);

				// 取得路径序列
				vector< MapWalkVertex* > MwvSeq;
				//const auto& PathTree = spfa.GetResult( ).PathTree ;
				MwvSeq.push_back(pMwv);

				//for ( auto it = PathTree.find( pVertex ) , end = PathTree.end( ); 
				//	it->second != 0 && it != end ;
				//	it = PathTree.find( it->second ) )
				//{
				//	MwvSeq.push_back( ( MapWalkVertex* ) it->second->UserData[ "mwv" ] ) ;
				//}

				for (Vertex* pParent = pVertexTarget->PathfindingData.pParent;
					pParent != 0;
					pParent = pParent->PathfindingData.pParent)
				{
					MwvSeq.push_back((MapWalkVertex*)pParent->UserData["mwv"]);
				}


				// 开始行走动画
				StartWalk(MwvSeq);

			}
		}
		break;
	}

	return true;
}


void LayerMapWalk::onTouchMoved(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocation();

	switch (m_Mode)
	{

	case OperationMode::DragEdge:
	{
		// 坐标变换
		pos = this->convertToNodeSpaceAR(pos);

		auto pSprLine = m_EditData.pSprEdgeLine;
		MakeLine(pSprLine, pSprLine->getPosition(), pos);

	}
		break;

	case OperationMode::DragContent:
	{
		Point pt = pos - m_EditData.ptDrag;
		this->setPosition(pt);
	}
		break;

	}
}


void LayerMapWalk::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 坐标变换
	auto pos = this->convertTouchToNodeSpaceAR(touch);

	switch (m_Mode)
	{
	case OperationMode::DragEdge:
	{
		auto pMwv = HitMapWalkVertex(pos);
		if (pMwv)
		{
			AddEdge(m_EditData.pMwv, pMwv);

			m_EditData.pSprEdgeLine->setVisible(false);

			m_Mode = OperationMode::PutVertex;
		}
		else
		{
			m_EditData.pSprEdgeLine->setVisible(false);

			m_Mode = OperationMode::PutVertex;
		}
	}
		break;

	}

}


MapWalkVertex* LayerMapWalk::HitMapWalkVertex(const Point& pos)
{
	MapWalkVertex * pRet = 0;

	// 是否命中节点
	for (auto& it : m_MapWalkVertexes)
	{
		auto v = pos - it->getPosition();
		if (v.getLengthSq() < 50 * 50)
		{
			pRet = it;
			break;
		}
	}

	return pRet;
}


void LayerMapWalk::MakeLine(Sprite* pSpr, const Point& pt1, const Point& pt2)
{
	// 设置锚点与位置
	pSpr->setAnchorPoint(Point(0, 0.5));
	pSpr->setPosition(pt1);

	// 缩放
	float width = pSpr->getTexture()->getContentSize().width;
	auto v = pt2 - pt1;
	float len = v.getLength();
	float ScaleX = len / width;
	pSpr->setScaleX(ScaleX);

	// 旋转
	float rad = v.getAngle();
	float Rotation = CC_RADIANS_TO_DEGREES(-rad);
	pSpr->setRotation(Rotation);

}


void LayerMapWalk::StartWalk(const vector< MapWalkVertex* >& MwvSeq)
{
	Action *pAct = m_pRole->getActionByTag(1);
	if (pAct != 0 && pAct->isDone() == false)
	{
		return;
	}

	Vector< FiniteTimeAction* > Actions;

	for (int i = MwvSeq.size() - 2; i >= 0; --i)
	{
		// 计算每一段的距离
		Point v = MwvSeq[i]->getPosition() - MwvSeq[i + 1]->getPosition();
		float len = v.getLength();
		float duration = len / 100 * 1.2;

		RoleKaito::State Direction;
		float rad = v.getAngle(Point(1, 1));
		float Degree = CC_RADIANS_TO_DEGREES(rad);
		if (Degree >= 0 && Degree < 90)
		{
			Direction = RoleKaito::State::WalkRight;
		}
		else if (Degree >= 90 && Degree <= 180)
		{
			Direction = RoleKaito::State::WalkBottom;
		}
		else if (Degree < 0 && Degree >= -90)
		{
			Direction = RoleKaito::State::WalkTop;
		}
		else if (Degree < -90 && Degree >= -180)
		{
			Direction = RoleKaito::State::WalkLeft;
		}

		auto fnSetDirection = [](RoleKaito *pRole, RoleKaito::State Dir)
		{
			pRole->SetState(Dir);
		};
		Actions.pushBack(CallFunc::create(bind(fnSetDirection, m_pRole, Direction)));

		FiniteTimeAction *pAct = MoveTo::create(duration, MwvSeq[i]->getPosition());
		auto fn = [](RoleKaito *pRole, MapWalkVertex * pGv)
		{
			pRole->UserData["StartVertex"] = pGv;
		};
		Actions.pushBack(pAct);
		Actions.pushBack(CallFunc::create(bind(fn, m_pRole, MwvSeq[i])));
	}

	auto fnStopActions = [](RoleKaito *pRole)
	{
		pRole->SetState(RoleKaito::State::None);
	};
	Actions.pushBack(CallFunc::create(bind(fnStopActions, m_pRole)));


	if (Actions.size() == 0)
	{
		return;
	}

	auto pSeq = Sequence::create(Actions);
	pSeq->setTag(1);
	m_pRole->runAction(pSeq);

}



void LayerMapWalk::AddVertex(MapWalkVertex* pMwv, const char * pszId)
{
	this->addChild(pMwv);
	m_MapWalkVertexes.push_back(pMwv);

	// 获取顶点ID
	string strId;
	if (pszId == 0)
	{
		auto it = m_VertexIdTable.begin();
		strId = it->first;
		m_VertexIdTable.erase(it);
	}
	else
	{
		auto it = m_VertexIdTable.find(pszId);
		if (it != m_VertexIdTable.end())
		{
			m_VertexIdTable.erase(it);
			strId = pszId;
		}

	}

	//  创建图顶点
	Vertex *pGv = new Vertex(strId);
	m_pGraph->AddVertex(pGv);

	//  地图行走的顶点绑定图顶点
	pMwv->SetGraphVertex(pGv);
	// 图顶点绑定地图行走的顶点
	pGv->UserData["mwv"] = pMwv;

	// 顶点的精灵表示
	auto pSpr = Sprite::create(RES_URL + "vertex_1.png");
	pMwv->addChild(pSpr);

}


void LayerMapWalk::AddEdge(MapWalkVertex* pMwv1, MapWalkVertex* pMwv2)
{
	// 不重复添加
	auto pGv1 = pMwv1->GetGraphVertex();
	auto pGv2 = pMwv2->GetGraphVertex();
	const auto& eo1 = pGv1->GetEdgesOut();
	const auto& eo2 = pGv2->GetEdgesOut();
	if (eo1.find(pGv2->GetId()) != eo1.end() ||
		eo2.find(pGv1->GetId()) != eo2.end())
	{
		return;
	}

	float Distance = (pMwv1->getPosition() - pMwv2->getPosition()).getLength();

	// 添加一条边
	m_pGraph->AddEdge(pMwv1->GetGraphVertex()->GetId(),
		pMwv2->GetGraphVertex()->GetId(),
		Distance
		);
	// 因为是有向边，所以，反向也添加一条边
	m_pGraph->AddEdge(pMwv2->GetGraphVertex()->GetId(),
		pMwv1->GetGraphVertex()->GetId(),
		Distance
		);

	// 添加边的表示。一条连接直线
	auto pSprLine = Sprite::create(RES_URL + "line.png");
	pSprLine->setOpacity(255 * 0.7);
	//pSprLine->setColor( Color3B( 0 , 0 , 255 ) ) ;
	MakeLine(pSprLine, pMwv1->getPosition(), pMwv2->getPosition());
	this->addChild(pSprLine, ZOrderLine);
	m_Lines.push_back(pSprLine);

}