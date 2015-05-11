#include "Spfa.h"
#include <queue>

using namespace std;

Spfa::Spfa()
{

}
Spfa::~Spfa()
{

}

void Spfa::Execute(const Graph &Graph, const string &vertexId)
{
	// ȡ��ͼ�Ķ��㼯��
	const auto &Vertexes = Graph.GetVertexes();
	//  ȡ����ʼ�������
	Vertex *pStartVertex = Vertexes.find(vertexId)->second;
	// Spfa�㷨��Ҫһ�����б��涥��
	queue<Vertex *>Q;
	// ��ʼ��
	for (auto it : Vertexes)
	{
		Vertex *pV = it.second;
		pV->PathfindingData.Cost = 0x0FFFFFFF;
		pV->PathfindingData.Flag = false;
		pV->PathfindingData.pParent = nullptr;
	}

	pStartVertex->PathfindingData.Cost = 0;// ��ʼ�����·������Ϊ0
	pStartVertex->PathfindingData.Flag = true;// ��ʼ�����ڶ�����
	Q.push(pStartVertex); // ��ʼ���������



	// spfa�㷨
	for (; Q.size();)
	{
		auto pStartVertex = Q.front();
		Q.pop();// ���е���һ������v
		pStartVertex->PathfindingData.Flag = false;

		// �ɳ�v�����г���
		const auto &Eo = pStartVertex->GetEdgesOut();
		for (auto &it : Eo)
		{
			auto pEdge = it.second;
			auto pEndVertex = pEdge->GetEndVertex();
			bool bRelaxRet = Relax(pStartVertex, pEndVertex, pEdge->GetWeight());
			if (bRelaxRet)
			{
				// ������ڳ����ɳڳɹ����ҳ��߶�Ӧ���յ㶥�㲻�ڶ����еĻ����Ͳ����β
				if (pEndVertex->PathfindingData.Flag == false)
				{
					Q.push(pEndVertex);
					pEndVertex->PathfindingData.Flag = false;
				}
			}
		}
	}

}


bool Spfa::Relax(Vertex *pStartVertex, Vertex *pEndVertex, int Weight)
{
	int n = pStartVertex->PathfindingData.Cost + Weight;
	if (n < pEndVertex->PathfindingData.Cost)
	{
		// ����·������
		pEndVertex->PathfindingData.Cost = n;
		// ����·��
		pEndVertex->PathfindingData.pParent = pStartVertex;
		return true;
	}
	return false;
}