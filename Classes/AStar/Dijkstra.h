#pragma once
#include "GraphPathfinding.h"

class Dijkstra:public GraphPathfinding
{
public:
	Dijkstra();
	~Dijkstra();
public:
	void Execute(const Graph &graph, const string &vertexId) override;
	Result& GetResult() { return m_Ret; }

private:
	// 抽出最小路径估值的顶点 
	inline Vertex* ExtractMin(vector< Vertex* >& Q);
	// 松弛
	inline bool Relax(Vertex* v1, Vertex* v2, int Weight);
private:
	Result m_Ret;

};

