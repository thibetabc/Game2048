#include "SceneMapWalk.h"
#include "LayerMapWalk.h"
#include "LayerHudControl.h"

SceneMapWalk::SceneMapWalk()
{
}


SceneMapWalk::~SceneMapWalk()
{
}

bool SceneMapWalk::init()
{
	srand(time(0));
	m_pLayerMapWalk = LayerMapWalk::create();
	this->addChild(m_pLayerMapWalk);

	auto pLayerHudControl = LayerHudControl::create();
	this->addChild(pLayerHudControl);


	pLayerHudControl->m_pLayerMapWalk = m_pLayerMapWalk;
	m_pLayerMapWalk->m_pLayerHudControl = pLayerHudControl;

	return true;
}
