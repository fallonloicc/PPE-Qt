#include "Conso.h"
#include <QtWidgets>
#include <QMessageBox>
#include <QNetworkAccessManager> 
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

Conso::Conso(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tableConso->setStyleSheet("QHeaderView::section { background-color:rgb(55, 55, 55); color: rgb(255, 255, 255); }");
	loadConso();
	connect(ui.AddButton_2, &QAbstractButton::clicked, this, &Conso::RecupInfo);
	connect(ui.DelButton_2, &QAbstractButton::clicked, this, &Conso::DeleteConso);
}


QString Conso::getName() const
{
	return m_name;
}

void Conso::setName(QString const& name)
{
	m_name = name;
}

void Conso::loadConso()
{
	// create custom temporary event loop on stack
	QEventLoop eventLoop;

	// "quit()" the event-loop, when the network request "finished()"
	QNetworkAccessManager mgr;
	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	// the HTTP request
	QNetworkRequest req(QUrl(QString("https://fallonloic.fr/PPE2/API/conso.php")));
	QNetworkReply *reply = mgr.get(req);
	eventLoop.exec(); // blocks stack until "finished()" has been called

	if (reply->error() == QNetworkReply::NoError) {

		QString strReply = (QString)reply->readAll();

		//parse json
		qDebug() << "Response:" << strReply;
		QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
		QJsonArray json_array = jsonResponse.array();

		int compt = 0;

		foreach(const QJsonValue &value, json_array) {

			QJsonObject json_obj = value.toObject();
			QString libelle = json_obj["libelle"].toString();
			QString prix = json_obj["prix"].toString();
			QString id = json_obj["idConsosommables"].toString();
			QString stock = json_obj["stock"].toString();

			ajouterConso(libelle, prix, id, stock);

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


void Conso::DeleteConso()
{

	int numLigne = ui.tableConso->currentRow();
	QTableWidgetItem* item = ui.tableConso->item(numLigne, 0);
	if (item != nullptr)
	{
		QString idBorne = item->data(Qt::DisplayRole).toString();
		ui.tableConso->removeRow(numLigne);

		QEventLoop eventLoop;

		QNetworkAccessManager *manager = new QNetworkAccessManager(this);
		connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

		manager->get(QNetworkRequest(QUrl("https://www.fallonloic.fr/PPE2/API/suppconso.php?idConso=" + idBorne)));
	}

}

void Conso::RecupInfo()
{
	QString nomConso = ui.editNom_2->text();
	QString prixConso = ui.editPrix_2->text();
	QString numConso = ui.editNum_2->text();
	QString stock = ui.editStock->text();
	

	if (nomConso != "" && prixConso != "" && numConso != "" && stock != "")
	{
		ajouterConso(nomConso, prixConso, numConso, stock);
	}

	ui.editNom_2->clear();
	ui.editPrix_2->clear();
	ui.editNum_2->clear();
	ui.editStock->clear();


	QEventLoop eventLoop;

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	manager->get(QNetworkRequest(QUrl("https://www.fallonloic.fr/PPE2/API/ajoutconso.php?prix="+prixConso+"&libelle="+nomConso+"&stock="+stock)));


	Conso oui = new Conso;
}


void Conso::ajouterConso(QString nomConso, QString prixConso, QString numConso, QString stock)
{

	int items = ui.tableConso->rowCount();
	const int colonn = 1;

	if (items < 1)
	{
		if (nomConso != "" && prixConso != "" && numConso != "" && stock != "")
		{
				int nbLines = ui.tableConso->rowCount();
				ui.tableConso->setRowCount(nbLines + 1);
				ui.tableConso->setItem(nbLines, 0, new QTableWidgetItem(numConso));
				ui.tableConso->setItem(nbLines, 1, new QTableWidgetItem(nomConso));
				ui.tableConso->setItem(nbLines, 2, new QTableWidgetItem(prixConso));
				ui.tableConso->setItem(nbLines, 3, new QTableWidgetItem(stock));
			
		}
		else
		{
			QMessageBox::critical(this, "ALERTE", "Veuillez remplir les champs ci dessus !");
		}
	}

	for (int i = 0; i < items; i++)
	{
		qDebug() << items;
		if (nomConso != ui.tableConso->item(i, colonn)->text())
		{
			if (nomConso != "" && prixConso != "" && numConso != "" && stock != "")
			{
				int nbLines = ui.tableConso->rowCount();
				ui.tableConso->setRowCount(nbLines + 1);
				ui.tableConso->setItem(nbLines, 0, new QTableWidgetItem(numConso));
				ui.tableConso->setItem(nbLines, 1, new QTableWidgetItem(nomConso));
				ui.tableConso->setItem(nbLines, 2, new QTableWidgetItem(prixConso));
				ui.tableConso->setItem(nbLines, 3, new QTableWidgetItem(stock));
			}
			else
			{
				QMessageBox::critical(this, "ALERTE", "Veuillez remplir les champs ci dessous !");
				qDebug() << "Ici !";
				i = items;
			}
		}
		else
		{
			QMessageBox::critical(this, "ALERTE", "Le nom est déjà prit !");
		}
	}
}

void Conso::removeTableau()
{
	while (ui.tableConso->rowCount() > 0)
	{
		ui.tableConso->removeRow(0);
	}
}
