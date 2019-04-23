#include "CubeData.h"



CubeData::CubeData()
{
	UpperLayer = new LayerData();
	LowerLayer = new LayerData();
}


CubeData::~CubeData()
{
	delete UpperLayer;
	delete LowerLayer;
}

bool CubeData::check() const
{
	if (UpperLayer->check() && LowerLayer->check())
		return true;
	else
		return false;
}

bool CubeData::isAbleToFlipAt(int upperLocation, int lowerLocation) const
{
	if (UpperLayer->isAbleToFlipAt(upperLocation) && LowerLayer->isAbleToFlipAt(lowerLocation))
		return true;
	else
		return false;
}

bool CubeData::flip(int upperLocation, int lowerLocation)
{
	//as I checked the avalibility in side LayerData::flip(), this part is commented.
	/*if (!isAbleToFlipAt(upperLocation, lowerLocation))
		return false;*/

	//do the job
	LayerData_ReturnValue temp;
	temp = UpperLayer->flip(LowerLayer, upperLocation, lowerLocation);
	if (LayerData_ReturnValue::ok == temp)
		return true;
	else 
		return false;
}

bool CubeData::getDirty() const
{
	if (UpperLayer->getDirty() ||/*I wrote OR here. Might be wrong*/ LowerLayer->getDirty())
		return true;
	else
		return false;
}
