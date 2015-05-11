#include "MapWalkConfigManager.h"
#include "LayerMapWalk.h"
#include "MapWalkVertex.h"
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

MapWalkConfigManager::MapWalkConfigManager()
{

}
MapWalkConfigManager::~MapWalkConfigManager()
{

}

void MapWalkConfigManager::Load(const string &ConfigFileName, LayerMapWalk *pLayerMapWalk)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(ConfigFileName.c_str());

	unordered_map<string, MapWalkVertex*> m_MwvList;
	auto pElemRoot = doc.RootElement();
	if (!pElemRoot)
	{
		return;
	}
	// 读取顶点的信息。创建出相应的顶点在界面上显示
	auto pElemVertexes = pElemRoot->FirstChildElement("Vertexes");
	if (!pElemVertexes)
	{
		return;
	}
	for (auto pElem = pElemVertexes->FirstChildElement(); pElem != 0; pElem = pElem->NextSiblingElement())
	{
		string strId = pElem->Attribute("Id");
		float x = atof(pElem->Attribute("x"));
		float y = atof(pElem->Attribute("y"));

		auto pMwv = MapWalkVertex::create();
		pMwv->setPosition(Vec2(x, y));
		pLayerMapWalk->AddVertex(pMwv, strId.c_str());

		m_MwvList[strId] = pMwv;
	}

	// 读取边的信息。创建出相应的边。
	auto pElemEdge = pElemRoot->FirstChildElement("Edges");
	for (auto pElem = pElemEdge->FirstChildElement(); pElem != 0; pElem = pElem->NextSiblingElement())
	{
		string v1Id = pElem->Attribute("StartVertexId");
		string v2Id = pElem->Attribute("EndVertexId");
		int  Weight = atof(pElem->Attribute("Weight"));
		pLayerMapWalk->AddEdge(m_MwvList[v1Id], m_MwvList[v2Id]);
	}
}

void MapWalkConfigManager::Save(const string& ConfigFileName, LayerMapWalk * pLayerMapWalk)
{
	tinyxml2::XMLDocument doc;

	auto pElemGraph = doc.NewElement("Graph");
	doc.InsertEndChild(pElemGraph);

	auto pElemGvRoot = doc.NewElement("Vertexes");
	pElemGraph->InsertEndChild(pElemGvRoot);

	// 保存顶点信息
	for (size_t i = 0; i < pLayerMapWalk->m_MapWalkVertexes.size(); ++i)
	{
		auto pMwv = pLayerMapWalk->m_MapWalkVertexes[i];
		auto pElemGv = doc.NewElement("Vertex");
		pElemGv->SetAttribute("Id", pMwv->GetGraphVertex()->GetId().c_str());
		pElemGv->SetAttribute("x", pMwv->getPositionX());
		pElemGv->SetAttribute("y", pMwv->getPositionY());
		pElemGvRoot->InsertEndChild(pElemGv);
	}

	auto pElemEdgeRoot = doc.NewElement("Edges");
	pElemGraph->InsertEndChild(pElemEdgeRoot);

	// 保存边的信息
	for (size_t i = 0; i < pLayerMapWalk->m_MapWalkVertexes.size(); ++i)
	{
		auto pMwvStart = pLayerMapWalk->m_MapWalkVertexes[i];

		auto pVS = pMwvStart->GetGraphVertex();
		// 遍历所有出边
		const auto& Eo = pVS->GetEdgesOut();
		for (auto& it : Eo)
		{
			auto pElemEdge = doc.NewElement("Edge");

			auto pEdge = it.second;
			auto pVE = pEdge->GetEndVertex();

			pElemEdge->SetAttribute("StartVertexId", pVS->GetId().c_str());
			pElemEdge->SetAttribute("EndVertexId", pVE->GetId().c_str());
			pElemEdge->SetAttribute("Weight", pEdge->GetWeight());

			pElemEdgeRoot->InsertEndChild(pElemEdge);
		}
	}


	doc.SaveFile(ConfigFileName.c_str());
}