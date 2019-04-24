#pragma once

#include <qstring.h>

class Sq1Action
{
public:
	Sq1Action();
	Sq1Action(int newUp,int intLow);
	~Sq1Action();

public:
	void SetUp(const int newUp);
	void SetLow(const int newLow);
	int getUp()const;
	int getLow()const;
	QString getDisplay()const;

private:
	int up;
	int low;

};

