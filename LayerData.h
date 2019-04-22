#pragma once

#include <qvector.h>

#include "Def for SQ1 calculator.h"//慢慢改 继续

class LayerData
{
public:
	LayerData();
	~LayerData();

public:
	bool setID(const int location,const char newID);
	char getID(const int location)const;
	bool getbMainPart(const int location)const;
	bool getDirty()const;
private:
	void setDirty(bool newDirty);

public:
	//this function doesnt check the data. Call check() or checkIndependently() before if you are not sure about the correctness.
	const QVector<char> getUsedNumbers()const;

	//without info from the other layer
	//bool checkIndependently();
	bool check(const QVector<char>& blocksInOtherLayer = QVector<char>()) ;

	//without info from the other layer
	//return value: count of removed(not very accurate) 
	int removeAllRepeatIndependently();

	//return value: count of removed(not very accurate) 
	int remove(const QVector<char>& IDsToRemove);

	//return value:1 true, 0 false,-1 error.
	inline int getBig(const int location)const;

public:
	//return value:1 true, 0 false,
	//-1 dirty.Break point in check() for more info.
	int isAbleToFlipAt(const int location);

	//Clockwisely rotate. Nothing to do with another layer.
	//when param = 1, then 1 goes to 0, 0 goes to 11. Right -> Front -> Left
	void rotate(int ThirtyDegrees);

	//return value:  1 ok
	//101 upper layer is not able to rotate at this position. Call isAbleToRotateAt()to check.
	//102 lower layer is not able.
	//-1 this layer is lower. Call this function through upper layer.
	int flip(LayerData& lowerLayer, int upper, int lower);
public:
	bool operator==(const LayerData& a);



private:
	// for small blocks in the upper layer, the front is 1, right is 3, back 5 left 7. for the lower layer, front 11, left 13,back 15,right 17.
	// for big blocks in the upper layer,fr 2,br 4,bl 6,fl 8,for the lower layer,fl 12,bl 14,br 16,fr 18
	// 0 for unknown when incompeletly searching.
	//上层小块是前1，右3，后5左7，下层是前11，左13，后15右17.
	//上层大块是 前右2，后右4，，，，下层是前左12，后左14，，，，
	//0是未知块
	QVector <char> IDs;

	//for all small blocks,this boolean is always true.
	//for big blocks,the left half is true but the right part is false. So, Gap is always found in left side of Main Parts.
	// this is for transforming availability check.
	// so, 12 blocks in a layer,4 are not main part, when a sq1 is solved.
	//automaticly managed. No set function available.
	QVector <bool> bMainPart;

	//a flag to track whether data has been written but hasnt been checked.
	bool dirty;

	//
	bool upper;
};

