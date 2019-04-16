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
	void ajouterConso(QString nomConso, QString prixConso, QString numConso, QString stock);
	void loadConso();
	void RecupInfo();
	QString getName() const;
	void setName(QString const& name);
	void removeTableau();

private:
	Ui::Conso ui;
	QString m_name;
};
