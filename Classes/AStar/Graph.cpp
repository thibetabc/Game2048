#include "Graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{
	//释放所有的顶点
	for (auto &kv : m_vertexes)
	{
		delete kv.second;
	}
	//释放所有的边
	for (auto &ke : m_edges)
	{
		delete ke.second;
	}
}

void Graph::AddVertex(Vertex *vertex)
{
	if (m_vertexes.find(vertex->GetId()) != m_vertexes.end())
	{
		//已经存在相同Key的顶点
	}
	m_vertexes[vertex->GetId()] = vertex;
	vertex->m_pGraph = this;
}

void Graph::delVertex(const string &vertexName)
{
	Vertex *pv = m_vertexes.find(vertexName)->second;
	//遍历要删除的节点的出边
	for (auto it = pv->m_EdgesOut.begin(), end = pv->m_EdgesOut.end(); it != end; ++it)
	{
		Edge *pEdgeOut = it->second;
		//删除入边记录
		pEdgeOut->m_pEndVertex->m_EdgesIn.erase(vertexName);
		//在边集合列表中删除
		string key = GetEdgeKey(pv, pEdgeOut->m_pEndVertex);
		m_edges.erase(key);

		//删除边对象
		delete pEdgeOut;
	}

	delete pv;
}

Edge *Graph::AddEdge(const string &vertex1Name, const string &vertex2Name, int weight/* = 0 */)
{
	Vertex *pv1 = m_vertexes.find(vertex1Name)->second;
	Vertex *pv2 = m_vertexes.find(vertex2Name)->second;

	//加入边的集合
	Edge *pEdge = new Edge(pv1, pv2, weight);
	string key = GetEdgeKey(pv1, pv2);
	m_edges[key] = pEdge;

	//加入v1的出边
	pv1->m_EdgesOut[vertex2Name] = pEdge;

	//加入v2的入边
	pv2->m_EdgesIn[vertex1Name] = pEdge;

	return pEdge;
}

void Graph::delEdge(const string &startVertexName, const string &endVertexName)
{
	Vertex *pv1 = m_vertexes.find(startVertexName)->second;
	Vertex *pv2 = m_vertexes.find(endVertexName)->second;

	string key = GetEdgeKey(pv1, pv2);

	Edge *pEdge = m_edges.find(key)->second;

	//在顶点1的出边列表中删除
	pv1->m_EdgesOut.erase(endVertexName);

	//在顶点2的入边列表中删除
	pv2->m_EdgesIn.erase(startVertexName);

	//在边集合列表中删除
	m_edges.erase(key);
	
	delete pEdge;

}