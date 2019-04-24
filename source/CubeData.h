#pragma once

#include "source/LayerData.h"
#include "source/Sq1Action.h"

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

public:
	sq1rv compare(CubeData* other,bool toSetUseful);
	QString getFormula()const;
	bool getUseful()const;


private:
	//This function remove all track info for this data!!!!
	//Only invoke when you are sure this state is definitely useless.
	void setUselessAndRemoveTrack();

	void setUseful();

private:
	LayerData* UpperLayer;
	LayerData* LowerLayer;

	QVector<Sq1Action> track;
	bool useful;

};

