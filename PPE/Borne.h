#pragma once

#include "ui_Borne.h"
#include "ui_PPE.h"

class Borne : public QWidget
{
	Q_OBJECT

public:
	Borne(QWidget *parent = Q_NULLPTR);

	void DeleteBorne();
	void ajouterBorne(QString nomBorne, QString prixBorne, QString numBorne, QString typeBorne, QString idBorne, QString url);
	void loadBorne();
	void RecupInfo();
	QString getName() const;
	void setName(QString const& name);
	void removeTableau();
	void changeDesign();

private:
	Ui::Borne ui;
	QString m_name;
};
