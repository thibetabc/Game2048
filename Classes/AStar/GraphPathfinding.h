#pragma once 
#include "Graph.h"
#include <unordered_map>

/*
路径搜索结果
*/
struct Result
{
	// 路径树
	unordered_map< Vertex*, Vertex* > PathTree;

};
class GraphPathfinding
{
public:
	GraphPathfinding();
	~GraphPathfinding();

public:
	virtual void Execute(const Graph &graph, const string& vertexId) = 0;

};
