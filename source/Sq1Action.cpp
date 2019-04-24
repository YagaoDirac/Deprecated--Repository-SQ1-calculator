#include "Sq1Action.h"



Sq1Action::Sq1Action()
{
	up = 0;
	low = 0;
}

Sq1Action::Sq1Action(int newUp, int newLow)
{
	SetUp(newUp);
	SetLow(newLow);
}


Sq1Action::~Sq1Action()
{
}

void Sq1Action::SetUp(const int newUp)
{
	up = newUp % 12;
	if (up > 6)
		up -= 12;
}

void Sq1Action::SetLow(const int newLow)
{
	low = newLow % 12;
	if (low > 6)
		low -= 12;
}

int Sq1Action::getUp() const
{
	return up;
}

int Sq1Action::getLow() const
{
	return low;
}

QString Sq1Action::getDisplay() const
{
	if (0 == up && 0 == low)
		return QString("/");

	QString result;
	result.append("(").append(up).append(",").append(low).append(")/");
	return result;
}
