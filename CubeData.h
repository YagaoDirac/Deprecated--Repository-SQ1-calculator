#pragma once

#include "source/LayerData.h"


class CubeData
{
public:
	CubeData();
	~CubeData();

public:
	bool check()const;
	bool isAbleToFlipAt(int upperLocation, int lowerLocation)const;
	bool flip(int upperLocation, int lowerLocation);
	bool getDirty()const;

private:

	LayerData* UpperLayer;
	LayerData* LowerLayer;


};

