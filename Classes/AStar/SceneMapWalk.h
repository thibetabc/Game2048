#pragma once

#include "cocos2d.h"
USING_NS_CC;

class LayerMapWalk;

class SceneMapWalk :
	public Scene
{
public:
	SceneMapWalk();
	~SceneMapWalk();

public:

	CREATE_FUNC(SceneMapWalk);

	bool init();

private:

	LayerMapWalk * m_pLayerMapWalk;

};
