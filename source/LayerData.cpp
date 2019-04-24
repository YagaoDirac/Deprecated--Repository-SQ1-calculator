#include "LayerData.h"



LayerData::LayerData()
{
	IDs.resize(12);
	bMainPart.resize(12);
}



LayerData::~LayerData()
{
}

bool LayerData::setID(const int location, const char newID)
{
	if (newID <= (char)0 || newID == (char)9 || newID == (char)10 || newID > (char)18)
		return false;

	//overwrites with the same info
	if (IDs[location] == newID  && true == bMainPart[location] )
		return true;

	//when new block is a big block
	if (newID % 2 == 0)
	{
		//and the block exists is also a big block
		if (getBig(location))
		{
			
			if (true == bMainPart[location])
			{
				IDs[location] = newID;
				bMainPart[location] = true;
				int rightHandSide = (location + 1) % 12;
				IDs[rightHandSide] = newID;
				bMainPart[rightHandSide] = false;
				//check one more step. Might be extra
				int temp_location = (rightHandSide + 1) % 12;
				if (bMainPart[temp_location] == false)
					IDs[temp_location] = 0;
				temp_location = (location - 1) % 12;
				if (bMainPart[temp_location] == true && IDs[temp_location] % 2 == 0)
					IDs[temp_location] = 0;
			}
			else//if (true == bMainPart[location])
			{
				IDs[location] = newID;
				bMainPart[location] = true;
				int rightHandSide = (location + 1) % 12;
				IDs[rightHandSide] = newID;
				bMainPart[rightHandSide] = false;
				int leftHandSide = (location - 1) % 12;
				IDs[leftHandSide] = 0;
				//check one more step. Might be extra
				int temp_location = (rightHandSide + 1) % 12;
				if (bMainPart[temp_location] == false)
					IDs[temp_location] = 0;
				temp_location = (location - 2) % 12;
				if (bMainPart[temp_location] == true && IDs[temp_location] % 2 == 0)
					IDs[temp_location] = 0;
			}
		}
		//but the block exists is a small block
		else//if (getBig(location))
		{
			IDs[location] = newID;
			bMainPart[location] = true;
			int rightHandSide = (location + 1) % 12;
			IDs[rightHandSide] = newID;
			bMainPart[rightHandSide] = false;
			//check one more step. Might be extra
			int temp_location = (rightHandSide + 1) % 12;
			if (bMainPart[temp_location] == false)
				IDs[temp_location] = 0;
			temp_location = (location - 1) % 12;
			if (bMainPart[temp_location] == true && IDs[temp_location] % 2 == 0)
				IDs[temp_location] = 0;
		}
	}
	//when new block is a small block
	else//if (newID % 2 == 0)
	{
		//and the block exists is a big block
		if (getBig(location))
		{
			if (true == bMainPart[location])
			{
				IDs[location] = newID;
				bMainPart[location] = true;
				int rightHandSide = (location + 1) % 12;
				IDs[rightHandSide] = 0;
			}
			else
			{
				IDs[location] = newID;
				bMainPart[location] = true;
				int leftHandSide = (location + 1) % 12;
				IDs[leftHandSide] = 0;
			}
		}
		//and the block exists is also a small block
		else//if (getBig(location))
		{
			IDs[location] = newID;
			bMainPart[location] = true;
		}
	}
	dirty = true;

	return true;
}

char LayerData::getID(int location) const
{
	if (location < 0 || location>7)
		return (char)-1;
	else
		return IDs[location];
}

bool LayerData::getbMainPart(int location) const
{
	return bMainPart[location%12];
}

bool LayerData::getDirty() const
{
	return dirty;
}

const QVector<char> LayerData::getUsedNumbers() const
{
	QVector<char> result;
	for (int i = 1; i <= 8; ++i)
	{
		if (IDs.contains(i))
			result.push_back(i);
	}
	for (int i = 11; i <= 18; ++i)
	{
		if (IDs.contains(i))
			result.push_back(i);
	}

	return QVector<char>();
}

bool LayerData::check(const QVector<char>& blocksInOtherLayer)
{
	//the only thing I need to write here is checking if any block number is used more than once.
	QVector<char> NumberUsed(blocksInOtherLayer);
	int currentLocation(0);

	//if (getbMainPart(0))
	//{//none
	//}
	//else
	//{	

	//	NumberUsed.append(IDs[0]);
	//	++currentLocation;
	//}
	while (currentLocation < 11)
	{
		int currentNumber = IDs[currentLocation];
		if (NumberUsed.contains(currentNumber))
		{
			return false;
		}
		else
		{
			NumberUsed.append(IDs[currentLocation]);
		}
		
		//update index
		if (getBig(currentLocation) && bMainPart[currentLocation])
			currentLocation += 2;
		else 
			currentLocation += 1;
	}

	//index == 11,and yes it's a main part, but it has to be small.
	if (11 == currentLocation)
	{
		if (getBig(11))
		{
			if (IDs[11] != IDs[0])
				return false;
		}
		else//small
		{
			if (NumberUsed.contains(IDs[currentLocation]))
				return false;
		}
	}

	//ok the checking functiong survived all the returning and got here. Let it return a true.
	setDirty(false);
	return true;
}

int LayerData::removeAllRepeatIndependently()
{
	int index(0);
	int removedCount(0);

	//for the first one
	while (index < 12)
	{
		int currentID = IDs[index];
		if (0 == currentID)
		{
			//do nothing to unknown blocks.
			++index;
			continue;
		}
	
		int count = IDs.count(IDs[index]);
		if(1 == count)
		{
			++index;
			continue;
		}
		else if (2 == count)
		{
			int rightHandSide = (index + 1) % 12;
			if (IDs[index] == IDs[rightHandSide] && 1 == bMainPart[index] && 0 == bMainPart[rightHandSide])
			{
				index += 2;
			}
			else
			{
				int leftHandSide = (index + 11) % 12;
				if (IDs[index] == IDs[leftHandSide] && 0 == bMainPart[0] && 1 == bMainPart[leftHandSide])
				{//I think this segment is fired only when the first part is the right half of a big block.
					index += 1;
				}
				else
				{
					for (int i = 1; i < 12; ++i)
					{
						if (IDs[0] == IDs[i])
						{
							IDs[i] = 0;//set to unknown
							++removedCount;
						}
					}
					IDs[0] = 0;
					++removedCount;
					index += 1;
				}
			}

		}
		else if (count>2)
		{
			for (int i = 1; i < 12; ++i)
			{
				if (IDs[0] == IDs[i])
				{
					IDs[i] = 0;//set to unknown
					++removedCount;
				}
			}
			IDs[0] = 0;
			++removedCount;
			index += 1;
		}
		
	}

	dirty = false;
	return removedCount;
}

int LayerData::remove(const QVector<char>& IDsToRemove)
{
	int removedCount(0);
	removedCount = removeAllRepeatIndependently();

	for (int i = 0; i < IDsToRemove.size(); ++i)
	{
		for (int i12 = 0; i12 < 12; ++i12)
		{
			if (IDsToRemove.contains(IDs[i12]))
			{
				if (getBig(i12))
				{
					IDs[i12] = 0;
					IDs[(i12 + 1) % 12] = 0;
					++removedCount;
				}
				else
				{
					IDs[i12] = 0;
					++removedCount;
				}
			}
		}
	}

	return removedCount;
}

inline int LayerData::getBig(int location)const
{
	if (location < 0 || location >= 12)
		return -1;
	if (IDs[location] % 2 == 0)
		return 1;
	else
		return 0;
}

int LayerData::isAbleToFlipAt(int location)
{
	if (dirty)
		return -1;//dirty

	location %= 6;
	
	if (bMainPart[location] && bMainPart[(location + 6) % 12])
		return 1;
	else
		return 0;
}

void LayerData::rotate(int ThirtyDegrees)
{
	ThirtyDegrees %= 12;
	if (0 == ThirtyDegrees)return;
	QVector<char> temp;
	
	for (int i = 0; i < ThirtyDegrees; ++i)
	{
		temp.push_back(IDs[i]);
	}
	IDs.remove(0, ThirtyDegrees);
	for (int i = 0; i < ThirtyDegrees; ++i)
	{
		IDs.push_back(temp[i]);
	}
	
	return;
}

LayerData_ReturnValue LayerData::flip(LayerData* lowerLayer, int upper, int lower)
{
	if (!LayerData::upper)//dont confuse with param for this func.
		return LayerData_ReturnValue::this_function_is_only_allowed_to_be_called_through_upper_layer;

	if (1 != isAbleToFlipAt(upper))
		return LayerData_ReturnValue::upper_layer_is_not_able_to_rotate_at_this_position;
	if (1 != lowerLayer->isAbleToFlipAt(lower))
		return LayerData_ReturnValue::lower_layer_is_not_able_to_rotate_at_this_position;

	//ok lets do something.
	upper %= 12;
	lower %= 12;

	rotate(upper);
	lowerLayer->rotate(lower);

	//The indices here are fixed. Upper 0 to 5 go exchange with lower 6 to 11. And 0-6 , 1-7
	char tempID;
	bool tempMainPart;
	for (int i = 0; i < 6; ++i)
	{
		tempID = IDs[i];
		tempMainPart = bMainPart[i];

		IDs[i] = lowerLayer->IDs[i];
		bMainPart[i] = lowerLayer->bMainPart[i];

		lowerLayer->IDs[i] = tempID;
		lowerLayer->bMainPart[i] = tempMainPart;
	}

	return LayerData_ReturnValue::OK;
}

bool LayerData::operator==(const LayerData& a)
{
	//One vote veto~
	for (int i = 0;i<12;++i)
	{ 
		if (IDs[i] != a.getID(i))
			return false;
		if (getBig(i) && bMainPart[i] != a.getbMainPart(i))
			return false;
	}

	return true;
}

void LayerData::setDirty(bool newDirty)
{
	dirty = newDirty;
}
		


