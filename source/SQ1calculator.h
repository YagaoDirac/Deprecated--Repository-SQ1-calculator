#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SQ1calculator.h"

class SQ1calculator : public QMainWindow
{
	Q_OBJECT

public:
	SQ1calculator(QWidget *parent = Q_NULLPTR);

private:
	Ui::SQ1calculatorClass ui;
};
