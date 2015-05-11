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
	// �����С·����ֵ�Ķ��� 
	inline Vertex* ExtractMin(vector< Vertex* >& Q);
	// �ɳ�
	inline bool Relax(Vertex* v1, Vertex* v2, int Weight);
private:
	Result m_Ret;

};

