#include "LayerHudControl.h"
#include "LayerMapWalk.h"
#include "MapWalkVertex.h"
#include "MapWalkConfigManager.h"
#include "tinyxml2/tinyxml2.h"
#include "AStar/AStarDefine.h"

LayerHudControl::LayerHudControl()
{
	m_pLayerMapWalk = 0;
}

LayerHudControl::~LayerHudControl()
{
}

bool LayerHudControl::init()
{

	Widget * pUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("AStar/ui/hud_control/hud_control.ExportJson");
	this->addChild(pUI);
	pUI->setAnchorPoint(Point(0, 1));

	auto rect = Director::getInstance()->getVisibleSize();
	//float y = rect.height - pUI->getSize( ).height ; 
	pUI->setPositionY(rect.height);

	m_pTxtInfo = (Text*)Helper::seekWidgetByName(pUI, "lblInfo");

	m_pTxtInfo2 = (Text*)Helper::seekWidgetByName(pUI, "txtInfo2");

	Button * pBtn = 0;
	function<void(Ref *ref, Widget::TouchEventType type)> fn;

	// �����ַ�����
	tinyxml2::XMLDocument doc;
	doc.LoadFile("AStar/config/strings.xml");
	auto pRoot = doc.RootElement();
	for (auto pElem = pRoot->FirstChildElement(); pElem != 0; pElem = pElem->NextSiblingElement())
	{
		m_StringList[pElem->Attribute("Key")] = pElem->Attribute("Value");
	}

	// Ĭ����ͼ�༭ģʽ
	m_pTxtInfo->setString(m_StringList["btnEditGraph"]);

	// ��̬����������������Ų��ᱻ���١�
	static auto fnSetInfo = [&](Widget *pWidget)
	{
		string name = pWidget->getName();
		auto it = m_StringList.find(name);
		if (it!= m_StringList.end())
		{
			m_pTxtInfo->setString(it->second);
		}
	};


	// ��ҷ��ť
	pBtn = (Button*)Helper::seekWidgetByName(pUI, "btnDrag");
	fn = [&](Ref* pSender, Widget::TouchEventType e)
	{
		if (e != Widget::TouchEventType::ENDED)	return;

		m_pLayerMapWalk->m_Mode = LayerMapWalk::OperationMode::DragContent;
		m_pTxtInfo->setString("��ǰģʽ:��ҷ����");
		fnSetInfo((Widget*)pSender);

	};
	pBtn->addTouchEventListener(fn);

	// ͼ�༭��ť
	pBtn = (Button*)Helper::seekWidgetByName(pUI, "btnEditGraph");
	fn = [&](Ref* pSender, Widget::TouchEventType e)
	{
		if (e != Widget::TouchEventType::ENDED)	return;

		m_pLayerMapWalk->m_Mode = LayerMapWalk::OperationMode::PutVertex;
		m_pTxtInfo->setString("��ǰģʽ:�༭ͼ");
		fnSetInfo((Widget*)pSender);
	};
	pBtn->addTouchEventListener(fn);

	// ��ʾ ����ͼ
	pBtn = (Button*)Helper::seekWidgetByName(pUI, "btnShowHideGraph");
	fn = [&](Ref*, Widget::TouchEventType e)
	{
		if (e != Widget::TouchEventType::ENDED)	return;

		for (auto& it : m_pLayerMapWalk->m_MapWalkVertexes)
		{
			it->setVisible(!it->isVisible());
		}

		for (auto& it : m_pLayerMapWalk->m_Lines)
		{
			it->setVisible(!it->isVisible());
		}
	};
	pBtn->addTouchEventListener(fn);

	// ��������
	pBtn = (Button*)Helper::seekWidgetByName(pUI, "btnPositionRole");
	fn = [&](Ref* pSender, Widget::TouchEventType e)
	{
		if (e != Widget::TouchEventType::ENDED)	return;

		m_pLayerMapWalk->m_Mode = LayerMapWalk::OperationMode::PositionRole;

		fnSetInfo((Widget*)pSender);
	};
	pBtn->addTouchEventListener(fn);

	// ����
	pBtn = (Button*)Helper::seekWidgetByName(pUI, "btnWalk");
	fn = [&](Ref* pSender, Widget::TouchEventType e)
	{
		if (e != Widget::TouchEventType::ENDED)	return;

		m_pLayerMapWalk->m_Mode = LayerMapWalk::OperationMode::RoleWalk;

		fnSetInfo((Widget*)pSender);
	};
	pBtn->addTouchEventListener(fn);

	pBtn = (Button*)Helper::seekWidgetByName(pUI, "btnSave");
	fn = [&](Ref*, Widget::TouchEventType e)
	{
		if (e != Widget::TouchEventType::ENDED)	return;

		MapWalkConfigManager::Save(RES_URL + "config/map_walk.xml", m_pLayerMapWalk);
	};
	pBtn->addTouchEventListener(fn);

	pBtn = (Button*)Helper::seekWidgetByName(pUI, "btnLoad");
	fn = [&](Ref*, Widget::TouchEventType e)
	{
		if (e != Widget::TouchEventType::ENDED)	return;

		MapWalkConfigManager::Load(RES_URL + "config/map_walk.xml", m_pLayerMapWalk);
	};
	pBtn->addTouchEventListener(fn);

	return true;
}