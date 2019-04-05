#pragma once

#include <QWidget>
#include "ui_Facture.h"

class Facture : public QWidget
{
	Q_OBJECT

public:
	Facture(QWidget *parent = Q_NULLPTR);
	~Facture();

private:
	Ui::Facture ui;
};
