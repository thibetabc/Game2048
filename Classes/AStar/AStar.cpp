#include "AStar.h"

AStar::AStar()
{

}

AStar::~AStar()
{

}

void AStar::Execute(const Graph &Graph, const string &VetexId)
{
	const auto& Vertexes = Graph.GetVertexes();
	Vertex* pVertexStart = Vertexes.find(VetexId)->second;
	vector< Vertex* > Q;

	// ��ʼ������  
	for (auto& it : Vertexes)
	{
		Vertex* pV = it.second;

		pV->PathfindingData.Cost = 0;
		pV->PathfindingData.pParent = nullptr;
		pV->PathfindingData.Heuristic = 0x0FFFFFFF;
		pV->PathfindingData.Flag = false;
	}

	// ��ʼ����ʼ����  
	pVertexStart->PathfindingData.pParent = 0;
	pVertexStart->PathfindingData.Cost = 0;
	pVertexStart->PathfindingData.Heuristic = Estimate(pVertexStart, m_pVTarget);

	// ����ʼ��������б���  
	Q.push_back(pVertexStart);
	pVertexStart->PathfindingData.Flag = true;

	for (; Q.size() > 0;)
	{
		// ѡ����С·�����ƵĶ���  
		auto v = ExtractMin(Q);
		v->PathfindingData.Flag = false;
		if (v == m_pVTarget)
		{
			return;
		}
		// �����еĳ��߽��С��ɳڡ�  
		const auto& EO = v->GetEdgesOut();
		for (auto& it : EO)
		{
			Edge* pEdge = it.second;
			Vertex* pVEnd = pEdge->GetEndVertex();

			bool bRet = Relax(v, pVEnd, pEdge->GetWeight());
			// ����ɳڳɹ��������б���
			if (bRet && pVEnd->PathfindingData.Flag == false)
			{
				Q.push_back(pVEnd);
				pVEnd->PathfindingData.Flag = true;
			}
		}
	}
}


Vertex* AStar::ExtractMin(vector< Vertex* >& Q)
{
	Vertex* Ret = 0;
	Ret = Q[0];
	int pos = 0;
	for (int i = 1, size = Q.size(); i < size; ++i)
	{
		if (Ret->PathfindingData.Heuristic > Q[i]->PathfindingData.Heuristic)
		{
			Ret = Q[i];
			pos = i;
		}
	}

	Q.erase(Q.begin() + pos);

	return Ret;
}

bool AStar::Relax(Vertex* v1, Vertex* v2, int Weight)
{
	// �����������ʽ����
	int G = v1->PathfindingData.Cost + Weight;  // ȡ�ô�V1��V2��ʵ��·������ 
	int H = Estimate(v2, m_pVTarget);   // ����V2��Ŀ��ڵ��·������
	int nHeuristic = G + H;    // ʵ�� + ���� = ����ʽ������ֵ  

	// ����Ӵ�·���ﵽĿ��ᱻ֮ǰ����ĸ��̣��͸���  
	if (nHeuristic < v2->PathfindingData.Heuristic)
	{
		v2->PathfindingData.Cost = G;
		v2->PathfindingData.pParent = v1;

		v2->PathfindingData.Heuristic = nHeuristic;
		return true;
	}

	return false;
}