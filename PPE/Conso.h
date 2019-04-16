#pragma once

#include <QWidget>
#include "ui_Conso.h"
#include "ui_PPE.h"

class Conso : public QWidget
{
	Q_OBJECT

public:
	Conso(QWidget *parent = Q_NULLPTR);
	void DeleteConso();
	void ajouterConso(QString nomBorne, QString prixBorne, QString numBorne, QString typeBorne, QString idBorne, QString url);
	void loadConso();
	void RecupInfo();
	QString getName() const;
	void setName(QString const& name);
	void removeTableau();

private:
	Ui::Conso ui;
	QString m_name;
};
