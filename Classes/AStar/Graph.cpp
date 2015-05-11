#include "Graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{
	//�ͷ����еĶ���
	for (auto &kv : m_vertexes)
	{
		delete kv.second;
	}
	//�ͷ����еı�
	for (auto &ke : m_edges)
	{
		delete ke.second;
	}
}

void Graph::AddVertex(Vertex *vertex)
{
	if (m_vertexes.find(vertex->GetId()) != m_vertexes.end())
	{
		//�Ѿ�������ͬKey�Ķ���
	}
	m_vertexes[vertex->GetId()] = vertex;
	vertex->m_pGraph = this;
}

void Graph::delVertex(const string &vertexName)
{
	Vertex *pv = m_vertexes.find(vertexName)->second;
	//����Ҫɾ���Ľڵ�ĳ���
	for (auto it = pv->m_EdgesOut.begin(), end = pv->m_EdgesOut.end(); it != end; ++it)
	{
		Edge *pEdgeOut = it->second;
		//ɾ����߼�¼
		pEdgeOut->m_pEndVertex->m_EdgesIn.erase(vertexName);
		//�ڱ߼����б���ɾ��
		string key = GetEdgeKey(pv, pEdgeOut->m_pEndVertex);
		m_edges.erase(key);

		//ɾ���߶���
		delete pEdgeOut;
	}

	delete pv;
}

Edge *Graph::AddEdge(const string &vertex1Name, const string &vertex2Name, int weight/* = 0 */)
{
	Vertex *pv1 = m_vertexes.find(vertex1Name)->second;
	Vertex *pv2 = m_vertexes.find(vertex2Name)->second;

	//����ߵļ���
	Edge *pEdge = new Edge(pv1, pv2, weight);
	string key = GetEdgeKey(pv1, pv2);
	m_edges[key] = pEdge;

	//����v1�ĳ���
	pv1->m_EdgesOut[vertex2Name] = pEdge;

	//����v2�����
	pv2->m_EdgesIn[vertex1Name] = pEdge;

	return pEdge;
}

void Graph::delEdge(const string &startVertexName, const string &endVertexName)
{
	Vertex *pv1 = m_vertexes.find(startVertexName)->second;
	Vertex *pv2 = m_vertexes.find(endVertexName)->second;

	string key = GetEdgeKey(pv1, pv2);

	Edge *pEdge = m_edges.find(key)->second;

	//�ڶ���1�ĳ����б���ɾ��
	pv1->m_EdgesOut.erase(endVertexName);

	//�ڶ���2������б���ɾ��
	pv2->m_EdgesIn.erase(startVertexName);

	//�ڱ߼����б���ɾ��
	m_edges.erase(key);
	
	delete pEdge;

}