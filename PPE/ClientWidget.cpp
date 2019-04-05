#include "ClientWidget.h"

ClientWidget::ClientWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.ajoutClient, &QAbstractButton::clicked, this, &ClientWidget::addClient);
	connect(ui.suppClient, &QAbstractButton::clicked, this, &ClientWidget::delClient);
	//(bouton où on fait l'action, action, page dans laquelle on veut actionner la fonction, appel de la fonction)
}

ClientWidget::~ClientWidget()
{
}

void ClientWidget::addLine(QString nom, QString prenom, QString adresse, QString codePostal, QString ville, QString mail, QString tel, QString siret)
{
	int nbLines = ui.tabClient->rowCount();
	ui.tabClient->setRowCount(nbLines + 1);
	ui.tabClient->setItem(nbLines, 0, new QTableWidgetItem(nom));
	ui.tabClient->setItem(nbLines, 1, new QTableWidgetItem(prenom));
	ui.tabClient->setItem(nbLines, 2, new QTableWidgetItem(adresse));
	ui.tabClient->setItem(nbLines, 3, new QTableWidgetItem(codePostal));
	ui.tabClient->setItem(nbLines, 4, new QTableWidgetItem(ville));
	ui.tabClient->setItem(nbLines, 5, new QTableWidgetItem(mail));
	ui.tabClient->setItem(nbLines, 6, new QTableWidgetItem(tel));
	ui.tabClient->setItem(nbLines, 7, new QTableWidgetItem(siret));
}

void ClientWidget::addClient()
{
	QString nomClient = ui.nomClient->text();
	QString prenomClient = ui.prenomClient->text();
	QString adresseClient = ui.adresseClient->text();
	QString codePostalClient = ui.codePostalClient->text();
	QString villeClient = ui.villeClient->text();
	QString mailClient = ui.mailClient->text();
	QString numClient = ui.numClient->text();
	QString siretClient = ui.siretClient->text();
	addLine(nomClient, prenomClient, adresseClient, codePostalClient, villeClient, numClient, numClient, siretClient);
	clearInput();
	
}

void ClientWidget::delClient()
{
	int numLigne = ui.tabClient->currentRow();
	ui.tabClient->removeRow(numLigne);
}

void ClientWidget::clearInput()
{
	ui.nomClient->clear();
	ui.prenomClient->clear();
	ui.adresseClient->clear();
	ui.codePostalClient->clear();
	ui.villeClient->clear();
	ui.mailClient->clear();
	ui.numClient->clear();
	ui.siretClient->clear();
}