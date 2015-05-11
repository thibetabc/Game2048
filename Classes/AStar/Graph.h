#pragma once
#include <vector>
#include <unordered_map>

using namespace std;

class Vertex;
class Edge;
class Graph;
class GraphPathfinding;

/*
图顶点
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
	// 附加数据 
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

	//出边集合
	unordered_map<string, Edge*> m_EdgesOut;

	//入边集合
	unordered_map<string, Edge*> m_EdgesIn;

	//节点表示的字符串
	string m_Text;

	//节点的ID
	string m_strId;

	//路径代价的估计
	//int m_Cost;

	//所属的图
	Graph *m_pGraph;
public:

	//寻路算法需要的数据
	struct Pathfinding
	{
		// 路径代价估计
		int Cost;

		// 标识符
		int Flag;

		// 顶点的前驱顶点。
		Vertex *pParent;

		// 启发式函数的计算出来的值  
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
图顶点的边
有向边
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
	//边的权重
	int m_Weight;
	//起点的顶点
	Vertex *m_pStartVertex;
	//终点的顶点
	Vertex *m_pEndVertex;
private:

};

/*
图.
图会负责释放顶点和边的内存
*/
class Graph
{
public:
	Graph();
	~Graph();
public:
	//添加一个顶点
	void AddVertex(Vertex *vertex);
	//删除一个顶点
	void  delVertex(const string &vertexName);

	//添加一条边，返回边对象
	Edge *AddEdge(const string &vertex1Name, const string &vertex2Name, int weight = 0);
	//删除一条边;
	void delEdge(const string &startVertexName, const string &endVertexName);
	const unordered_map<string, Vertex*> &GetVertexes()const{ return m_vertexes; }
protected:
	//顶点的集合
	unordered_map<string, Vertex*> m_vertexes;
	//边的集合 
	unordered_map<string, Edge*> m_edges;

protected:
	//key的格式："顶点1name->顶点2name"
#define GetEdgeKey(pV1, pV2)(pV1->m_strId + "->" + pV2->m_strId)

private:

};
