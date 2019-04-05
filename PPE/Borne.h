#pragma once

#include "ui_Borne.h"
#include "ui_PPE.h"

class Borne : public QWidget
{
	Q_OBJECT

public:
	Borne(QWidget *parent = Q_NULLPTR);

	void DeleteBorne();
	void ajouterBorne(QString nomBorne, QString prixBorne, QString numBorne, QString typeBorne);
	void loadBorne();
	void RecupInfo();
	QString getName() const;
	void setName(QString const& name);

private:
	Ui::Borne ui;
	QString m_name;
};
