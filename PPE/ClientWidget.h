#pragma once

#include <QWidget>
#include "ui_ClientWidget.h"
#include "ui_PPE.h"

using namespace std;

class ClientWidget : public QWidget
{
	Q_OBJECT

public:
	ClientWidget(QWidget *parent = Q_NULLPTR);
	~ClientWidget();
	void addLine(QString id, QString nom, QString prenom, QString adresse, QString codePostal, QString ville, QString mail, QString tel, QString siret);
	void addClient();
	void delClient();
	void clearInput();
	void loadClient();

private:
	Ui::ClientWidget ui;
};
