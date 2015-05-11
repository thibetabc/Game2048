#pragma once
#include <string>
using namespace std;
class LayerMapWalk;

class MapWalkConfigManager
{
public:
	MapWalkConfigManager();
	~MapWalkConfigManager();

public:
	static void Load(const string& ConfigFileName, LayerMapWalk * pLayerMapWalk);

	static void Save(const string& ConfigFileName, LayerMapWalk * pLayerMapWalk);

};