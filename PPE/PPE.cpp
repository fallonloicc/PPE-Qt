#include "PPE.h"
#include "ClientWidget.h"
#include "Facture.h"
#include "Borne.h"
#include "Conso.h"
#include <QtWidgets>

	
PPE::PPE(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.AjoutFacture, &QAbstractButton::clicked, this, &PPE::ShowFacture);
	connect(ui.AjoutBorne, &QAbstractButton::clicked, this, &PPE::ShowBorne);
	connect(ui.Client, &QAbstractButton::clicked, this, &PPE::ShowClient);
	connect(ui.Conso, &QAbstractButton::clicked, this, &PPE::ShowConso);
	connect(ui.Quit, &QAbstractButton::clicked, this, &PPE::CloseWin);

}

void PPE::removeWidget()
{
	// Supprime la page dans StackedWidget
	QWidget *currentWidget = ui.stackedWidget->currentWidget();
	ui.stackedWidget->removeWidget(currentWidget);
}

void PPE::ShowFacture()
{
	removeWidget();
	// Affiche le contenu de la page Facture
	Facture *pageFacture = new Facture;
	ui.stackedWidget->addWidget(pageFacture);
	ui.stackedWidget->setCurrentIndex(1);

}

void PPE::ShowBorne()
{
	removeWidget();
	// Affiche le contenu de la page Borne
	Borne *pageBorne = new Borne;
	ui.stackedWidget->addWidget(pageBorne);
	ui.stackedWidget->setCurrentIndex(1);
}

void PPE::ShowConso()
{
	removeWidget();
	// Affiche le contenu de la page Borne
	Conso *pageConso = new Conso;
	ui.stackedWidget->addWidget(pageConso);
	ui.stackedWidget->setCurrentIndex(1);
}

void PPE::ShowClient()
{
	removeWidget();
	// Affiche le contenu de la page ClientWidget
	ClientWidget *pageClient = new ClientWidget;
	ui.stackedWidget->addWidget(pageClient);
	ui.stackedWidget->setCurrentIndex(1);
}

void PPE::CloseWin()
{
	close();
}