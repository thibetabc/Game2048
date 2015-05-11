#pragma once
#include <vector>
#include <unordered_map>

using namespace std;

class Vertex;
class Edge;
class Graph;
class GraphPathfinding;

/*
ͼ����
*/
class Vertex
{
	friend class Graph;
public:
	Vertex(const string &name)
	{
		m_strId = name;
		m_pGraph = nullptr;
	}
	~Vertex(){};
public:
	// �������� 
	unordered_map<string, void*> UserData;
public:
	const unordered_map<string, Edge*> &GetEdgesOut()const
	{
		return m_EdgesOut;
	}
	const unordered_map<string, Edge*> &GetEdgesIn()const
	{
		return m_EdgesIn;
	}
	const string &GetId() const
	{
		return m_strId;
	}
	const string &GetText() const
	{
		return m_Text;
	}
	void SetText(const string &Text)
	{
		m_Text = Text;
	}
	Graph *GetGraph()
	{
		return m_pGraph;
	}

protected:

	//���߼���
	unordered_map<string, Edge*> m_EdgesOut;

	//��߼���
	unordered_map<string, Edge*> m_EdgesIn;

	//�ڵ��ʾ���ַ���
	string m_Text;

	//�ڵ��ID
	string m_strId;

	//·�����۵Ĺ���
	//int m_Cost;

	//������ͼ
	Graph *m_pGraph;
public:

	//Ѱ·�㷨��Ҫ������
	struct Pathfinding
	{
		// ·�����۹���
		int Cost;

		// ��ʶ��
		int Flag;

		// �����ǰ�����㡣
		Vertex *pParent;

		// ����ʽ�����ļ��������ֵ  
		int Heuristic;

		Pathfinding()
		{
			Cost = 0;
			Flag = 0;
			pParent = nullptr;
			Heuristic = 0;
		}
	}PathfindingData;
};


/*
ͼ����ı�
�����
*/

class Edge
{
	friend class Graph;
public:
	Edge()
	{
		m_Weight = 0;
		m_pStartVertex = nullptr;
		m_pEndVertex = nullptr;
	}
	Edge(Vertex *startVertex, Vertex *endVertex, int weight = 0)
	{
		m_pStartVertex = startVertex;
		m_pEndVertex = endVertex;
		m_Weight = weight;
	}
	~Edge(){};
public:
	const int GetWeight(){ return m_Weight; }
	void SetWeight(int weight){ m_Weight = weight; }
	Vertex *GetStartVertex()const { return m_pStartVertex; }
	Vertex *GetEndVertex()const { return m_pEndVertex; }

protected:
	//�ߵ�Ȩ��
	int m_Weight;
	//���Ķ���
	Vertex *m_pStartVertex;
	//�յ�Ķ���
	Vertex *m_pEndVertex;
private:

};

/*
ͼ.
ͼ�Ḻ���ͷŶ���ͱߵ��ڴ�
*/
class Graph
{
public:
	Graph();
	~Graph();
public:
	//���һ������
	void AddVertex(Vertex *vertex);
	//ɾ��һ������
	void  delVertex(const string &vertexName);

	//���һ���ߣ����ر߶���
	Edge *AddEdge(const string &vertex1Name, const string &vertex2Name, int weight = 0);
	//ɾ��һ����;
	void delEdge(const string &startVertexName, const string &endVertexName);
	const unordered_map<string, Vertex*> &GetVertexes()const{ return m_vertexes; }
protected:
	//����ļ���
	unordered_map<string, Vertex*> m_vertexes;
	//�ߵļ��� 
	unordered_map<string, Edge*> m_edges;

protected:
	//key�ĸ�ʽ��"����1name->����2name"
#define GetEdgeKey(pV1, pV2)(pV1->m_strId + "->" + pV2->m_strId)

private:

};
