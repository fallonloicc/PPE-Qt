#include "ClientWidget.h"
#include <QtWidgets>
#include <QMessageBox>
#include <QNetworkAccessManager> 
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

ClientWidget::ClientWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	loadClient();
	connect(ui.ajoutClient, &QAbstractButton::clicked, this, &ClientWidget::addClient);
	connect(ui.suppClient, &QAbstractButton::clicked, this, &ClientWidget::delClient);
	//(bouton où on fait l'action, action, page dans laquelle on veut actionner la fonction, appel de la fonction)
}

ClientWidget::~ClientWidget()
{
}

void ClientWidget::loadClient()
{
	// create custom temporary event loop on stack
	QEventLoop eventLoop;

	// "quit()" the event-loop, when the network request "finished()"
	QNetworkAccessManager mgr;
	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	// the HTTP request
	QNetworkRequest req(QUrl(QString("https://fallonloic.fr/PPE2/API/clients.php")));
	QNetworkReply *reply = mgr.get(req);
	eventLoop.exec(); // blocks stack until "finished()" has been called

	if (reply->error() == QNetworkReply::NoError) {

		QString strReply = (QString)reply->readAll();

		//parse json
		qDebug() << "Response:" << strReply;
		QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
		QJsonArray json_array = jsonResponse.array();

		int compt = 0;

		foreach(const QJsonValue &value, json_array) 
		{

			QJsonObject json_obj = value.toObject();
			QString id = json_obj["idClient"].toString();
			QString nom = json_obj["nom"].toString();
			QString prenom = json_obj["prenom"].toString();
			QString email = json_obj["email"].toString();
			QString tel = json_obj["tel"].toString();
			QString cp = json_obj["cp"].toString();
			QString ville = json_obj["ville"].toString();
			QString adresse = json_obj["adresse"].toString();
			QString siret = json_obj["siret"].toString();

			addLine(id, nom, prenom, adresse, cp, ville, email, tel, siret);

			compt++;
		}
		qDebug() << compt;
		delete reply;
	}
	else {
		//failure
		qDebug() << "Failure" << reply->errorString();
		delete reply;
	}


}

void ClientWidget::addLine(QString id, QString nom, QString prenom, QString adresse, QString codePostal, QString ville, QString mail, QString tel, QString siret)
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
	ui.tabClient->setItem(nbLines, 8, new QTableWidgetItem(id));

	
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
	QString passwdClient = ui.editpasswd->text();

	addLine(0, nomClient, prenomClient, adresseClient, codePostalClient, villeClient, mailClient, numClient, siretClient);
	clearInput();

	QEventLoop eventLoop;

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	if (siretClient != "")
	{
		manager->get(QNetworkRequest(QUrl("https://fallonloic.fr/PPE2/API/ajoutClient.php?nom="+nomClient+"&prenom="+prenomClient+"&adresse="+ adresseClient +"&email="+mailClient+"&tel="+numClient+"&cp="+codePostalClient+"&ville="+villeClient+"&siret="+siretClient+"&passwd="+passwdClient)));
	}
	else
	{
		manager->get(QNetworkRequest(QUrl("https://fallonloic.fr/PPE2/API/ajoutClient.php?nom=" + nomClient + "&prenom=" + prenomClient + "&adresse=" + adresseClient + "&email=" + mailClient + "&tel=" + numClient + "&cp=" + codePostalClient + "&ville=" + villeClient +"&passwd=" + passwdClient)));
	}

	ClientWidget oui = new ClientWidget;
	
}

void ClientWidget::delClient()
{
	int numLigne = ui.tabClient->currentRow();
	QTableWidgetItem* item = ui.tabClient->item(numLigne, 8);
	QString idClient = item->data(Qt::DisplayRole).toString();
	ui.tabClient->removeRow(numLigne);

	QEventLoop eventLoop;

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	manager->get(QNetworkRequest(QUrl("https://fallonloic.fr/PPE2/API/suppclients.php?idClient=" + idClient)));
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