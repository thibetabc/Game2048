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

	// ����ģʽ
	enum class OperationMode
	{
		//  ���ö���
		PutVertex,

		// ��ҷ����
		DragContent,

		// ��ҷ��
		DragEdge,

		// ���ý�ɫ
		PositionRole,

		// ����
		RoleWalk,

	};
private:

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;

	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;

	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;

private:

	// �ж��Ƿ����ж���
	// �������еĶ����ָ�롣û���У�����0
	MapWalkVertex* HitMapWalkVertex(const Point& pos);

	// ����һ������ֱ��
	static void MakeLine(Sprite* pSpr, const Point& pt1, const Point& pt2);

	void StartWalk(const vector< MapWalkVertex* >& GvSeq);

	// ���һ������
	void AddVertex(MapWalkVertex* pMwv, const char * pszId = 0);

	// ���һ����
	void AddEdge(MapWalkVertex* pMwv1, MapWalkVertex* pMwv2);

public:

	LayerHudControl * m_pLayerHudControl;
private:

	OperationMode m_Mode;

	Graph * m_pGraph;

	// ��ͼ���ߵĽڵ��б�
	vector< MapWalkVertex* > m_MapWalkVertexes;

	// ��ͼ���ߵıߵľ���
	vector< Sprite* > m_Lines;
	Node * m_pNodeLines;

	// ��ͼ�༭���õ���ʱ����
	struct  EditData
	{
		MapWalkVertex * pMwv;

		// �༭�߶�
		Sprite * pSprEdgeLine;

		// �϶�ƫ������
		Point ptDrag;
	}m_EditData;


	RoleKaito * m_pRole;

	// ͼ�ڵ�ID�����
	unordered_map< string, int > m_VertexIdTable;
};