#include "Dijkstra.h"
#include <queue>


Dijkstra::Dijkstra()
{
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::Execute(const Graph& graph, const string& vetexId)
{
	m_Ret.PathTree.clear();
	const auto &Vertexes = graph.GetVertexes();
	Vertex* pVertexStart = Vertexes.find(vetexId)->second;
	vector< Vertex* > Q;
	//// ��ʼ��   
	//for (auto& it : Vertexes)
	//{
	//	it.second->PathfindingData.Cost = 0x0FFFFFFF;
	//	Q.push_back(it.second);
	//	pVertexStart->PathfindingData.pParent = nullptr;
	//}
	////m_Ret.PathTree[pVertexStart] = 0;    //  ��ʼ�����ǰ������Ϊ��  
	//pVertexStart->PathfindingData.Cost = 0;
	//for (; Q.size() > 0;)
	//{
	//	// ѡ����С·�����ƵĶ���   
	//	auto v = ExtractMin(Q);
	//	// �����еĳ��߽��С��ɳڡ�   
	//	const auto& EO = v->GetEdgesOut();
	//	for (auto& it : EO)
	//	{
	//		Edge* pEdge = it.second;
	//		Relax(v, pEdge->GetEndVertex(), pEdge->GetWeight());
	//	}
	//}

	// ��ʼ��   
	for (auto& it : Vertexes)
	{
		it.second->PathfindingData.Cost = 0x0FFFFFFF;
		pVertexStart->PathfindingData.pParent = nullptr;
	}

	// ��ʼ����ʼ����
	//m_Ret.PathTree[pVertexStart] = 0;    //  ��ʼ�����ǰ������Ϊ��  
	pVertexStart->PathfindingData.Cost = 0;
	pVertexStart->PathfindingData.pParent = nullptr;

	// ����ʼ��������б���  
	Q.push_back(pVertexStart);
	pVertexStart->PathfindingData.Flag = true;

	for (; Q.size() > 0;)
	{
		// ѡ����С·�����ƵĶ���   
		auto v = ExtractMin(Q);
		v->PathfindingData.Flag = false;

		// �����еĳ��߽��С��ɳڡ�   
		const auto& EO = v->GetEdgesOut();
		for (auto& it : EO)
		{
			Edge* pEdge = it.second;
			Vertex* pVEnd = pEdge->GetEndVertex();

			bool bRel = Relax(v, pVEnd, pEdge->GetWeight());
			if (bRel && pVEnd->PathfindingData.Flag == false)
			{
				Q.push_back(pVEnd);
				pVEnd->PathfindingData.Flag = true;
			}
		}
	}
}

Vertex *Dijkstra::ExtractMin(vector< Vertex*> &Q)
{
	Vertex *Ret = nullptr;
	Ret = Q[0];
	int pos = 0;
	for (int i = 1, size = Q.size(); i < size; ++i)
	{
		if (Ret->PathfindingData.Cost > Q[i]->PathfindingData.Cost)
		{
			Ret = Q[i];
			pos = i;
		}
	}

	Q.erase(Q.begin() + pos);
	return Ret;
}

bool Dijkstra::Relax(Vertex *v1, Vertex *v2, int Weight)
{
	int n = v1->PathfindingData.Cost + Weight;
	if (n < v2->PathfindingData.Cost)
	{
		v1->PathfindingData.Cost = n;
		v2->PathfindingData.pParent = v1;
		return true;
	}
	return false;
}
