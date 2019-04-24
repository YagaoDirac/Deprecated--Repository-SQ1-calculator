#include "CubeData.h"



CubeData::CubeData()
{
	UpperLayer = new LayerData();
	LowerLayer = new LayerData();
	useful = false;
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
	upperLocation %= 12;
	lowerLocation %= 12;

	LayerData_ReturnValue temp;
	temp = UpperLayer->flip(LowerLayer, upperLocation, lowerLocation);
	if (LayerData_ReturnValue::OK == temp)
	{
		track.push_back(Sq1Action(upperLocation, lowerLocation));
		return true;
	}
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

sq1rv CubeData::compare(CubeData* other, bool toSetUseful)
{
	if (!other) return sq1rv::bad_param;

	if (other->UpperLayer == UpperLayer && other->LowerLayer == LowerLayer)
	{
		if (toSetUseful)
		{
			useful = true;
		}
		return sq1rv::True;
	}
	else
	{
		if (toSetUseful)
		{
			setUselessAndRemoveTrack();
		}
		return sq1rv::False;
	}
}

QString CubeData::getFormula() const
{
	if (!useful)
		return QString();

	QString result;
	for (int i = 0; i < track.size(); ++i)
	{
		result.append(track[i].getDisplay());
	}
	
	return result;
}

bool CubeData::getUseful() const
{
	return useful;
}

void CubeData::setUselessAndRemoveTrack()
{
	useful = false;
	track.clear();
}

void CubeData::setUseful()
{
	useful = true;
}
