#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <unordered_map>

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

class LayerMapWalk;

class LayerHudControl :
	public Layer
{
public:
	LayerHudControl();
	~LayerHudControl();

	CREATE_FUNC(LayerHudControl);

	bool init();

public:
	LayerMapWalk * m_pLayerMapWalk;

	Text *m_pTxtInfo;

	Text *m_pTxtInfo2;

	// ×Ö·û´®±í
	unordered_map< string, string> m_StringList;

};