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

	// 初始化顶点  
	for (auto& it : Vertexes)
	{
		Vertex* pV = it.second;

		pV->PathfindingData.Cost = 0;
		pV->PathfindingData.pParent = nullptr;
		pV->PathfindingData.Heuristic = 0x0FFFFFFF;
		pV->PathfindingData.Flag = false;
	}

	// 初始化起始顶点  
	pVertexStart->PathfindingData.pParent = 0;
	pVertexStart->PathfindingData.Cost = 0;
	pVertexStart->PathfindingData.Heuristic = Estimate(pVertexStart, m_pVTarget);

	// 把起始顶点放入列表中  
	Q.push_back(pVertexStart);
	pVertexStart->PathfindingData.Flag = true;

	for (; Q.size() > 0;)
	{
		// 选出最小路径估计的顶点  
		auto v = ExtractMin(Q);
		v->PathfindingData.Flag = false;
		if (v == m_pVTarget)
		{
			return;
		}
		// 对所有的出边进行“松弛”  
		const auto& EO = v->GetEdgesOut();
		for (auto& it : EO)
		{
			Edge* pEdge = it.second;
			Vertex* pVEnd = pEdge->GetEndVertex();

			bool bRet = Relax(v, pVEnd, pEdge->GetWeight());
			// 如果松弛成功，加入列表中
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
	// 这里就是启发式函数
	int G = v1->PathfindingData.Cost + Weight;  // 取得从V1到V2的实际路径代价 
	int H = Estimate(v2, m_pVTarget);   // 估计V2到目标节点的路径代价
	int nHeuristic = G + H;    // 实际 + 估算 = 启发式函数的值  

	// 如果从此路径达到目标会被之前计算的更短，就更新  
	if (nHeuristic < v2->PathfindingData.Heuristic)
	{
		v2->PathfindingData.Cost = G;
		v2->PathfindingData.pParent = v1;

		v2->PathfindingData.Heuristic = nHeuristic;
		return true;
	}

	return false;
}