#pragma once
#include "GraphPathfinding.h"
#include <functional>

class AStar : public GraphPathfinding
{
public:
	AStar();
	~AStar();

public:
	// 估计顶点到目标顶点的代价 
	std::function<int(const Vertex *pVCurrent, const Vertex *pVTarget)> Estimate;

public:
	virtual void Execute(const Graph& Graph, const string& VetexId) override;

private:
	// 抽出最小路径估值的顶点
	Vertex* ExtractMin(vector< Vertex* >& Q);

	// 松弛
	bool Relax(Vertex* v1, Vertex* v2, int Weight);

public:
	inline void SetTarget(Vertex* pVTarget) { m_pVTarget = pVTarget; }

private:
	Vertex* m_pVTarget;

};