#pragma once

#include <vector>
#include "cocos2d.h"
#include "AStar\Graph.h"


using namespace std;
USING_NS_CC;

class MapWalkVertex;
class LayerHudControl;
class RoleKaito;
class LayerHudControl;

class LayerMapWalk :
	public Layer
{
	friend class LayerHudControl;
	friend class MapWalkConfigManager;

public:
	LayerMapWalk();
	~LayerMapWalk();
public:

	CREATE_FUNC(LayerMapWalk);

	bool init();
public:

	// 操作模式
	enum class OperationMode
	{
		//  放置顶点
		PutVertex,

		// 拖曳场景
		DragContent,

		// 拖曳边
		DragEdge,

		// 放置角色
		PositionRole,

		// 行走
		RoleWalk,

	};
private:

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;

	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;

	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;

private:

	// 判断是否命中顶点
	// 返回命中的顶点的指针。没命中，返回0
	MapWalkVertex* HitMapWalkVertex(const Point& pos);

	// 创建一条精灵直线
	static void MakeLine(Sprite* pSpr, const Point& pt1, const Point& pt2);

	void StartWalk(const vector< MapWalkVertex* >& GvSeq);

	// 添加一个顶点
	void AddVertex(MapWalkVertex* pMwv, const char * pszId = 0);

	// 添加一条边
	void AddEdge(MapWalkVertex* pMwv1, MapWalkVertex* pMwv2);

public:

	LayerHudControl * m_pLayerHudControl;
private:

	OperationMode m_Mode;

	Graph * m_pGraph;

	// 地图行走的节点列表
	vector< MapWalkVertex* > m_MapWalkVertexes;

	// 地图行走的边的精灵
	vector< Sprite* > m_Lines;
	Node * m_pNodeLines;

	// 地图编辑所用的临时数据
	struct  EditData
	{
		MapWalkVertex * pMwv;

		// 编辑线段
		Sprite * pSprEdgeLine;

		// 拖动偏移向量
		Point ptDrag;
	}m_EditData;


	RoleKaito * m_pRole;

	// 图节点ID分配表
	unordered_map< string, int > m_VertexIdTable;
};