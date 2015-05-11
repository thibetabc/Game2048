#pragma once
#include "AStar/GraphPathfinding.h"

class Spfa : public GraphPathfinding
{
public:
	Spfa();
	~Spfa();
public:
	virtual void Execute(const Graph &Graph, const string &vertexId);
private:
	inline bool Relax(Vertex *pStartVertex, Vertex *pEndVertex, int Weight);

};