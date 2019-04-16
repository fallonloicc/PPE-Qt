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
	loadConso();
	connect(ui.AddButton, &QAbstractButton::clicked, this, &Conso::RecupInfo);
	connect(ui.DelButton, &QAbstractButton::clicked, this, &Conso::DeleteConso);
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
	QNetworkRequest req(QUrl(QString("https://fallonloic.fr/PPE2/API/bornes.php")));
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
			QString id = json_obj["idBornes"].toString();
			QString adresse = json_obj["adresseMac"].toString();
			QString ip = json_obj["adresseIp"].toString();
			QString url = json_obj["image"].toString();

			ajouterConso(libelle, prix, id, adresse, ip, url);

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

	int numLigne = ui.TableConso->currentRow();
	QTableWidgetItem* item = ui.TableConso->item(numLigne, 0);
	QString idBorne = item->data(Qt::DisplayRole).toString();
	ui.TableConso->removeRow(numLigne);

	QEventLoop eventLoop;

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	manager->get(QNetworkRequest(QUrl("https://fallonloic.fr/PPE2/API/suppborne.php?idBorne=" + idBorne)));

}

void Conso::RecupInfo()
{
	QString nomBorne = ui.editNom_2->text();
	QString prixBorne = ui.editPrix_2->text();
	QString numBorne = ui.editNum_2->text();
	QString stock = ui.editStock->text();
	

	if (nomBorne != "" && prixBorne != "" && numBorne != "" && typeBorne != "" && idBorne != "")
	{
		ajouterConso(nomBorne, prixBorne, numBorne, typeBorne, idBorne, urlBorne);
	}

	ui.editNom->clear();
	ui.editPrix->clear();
	ui.editNum->clear();
	ui.editType->clear();
	ui.editIP->clear();
	ui.editURL->clear();


	QEventLoop eventLoop;

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	if (urlBorne != "")
	{
		manager->get(QNetworkRequest(QUrl("https://fallonloic.fr/PPE2/API/ajoutborne.php?prix=" + prixBorne + "&libelle=" + nomBorne + "&adresseMac=" + typeBorne + "&adresseIp=" + idBorne + "&urlImage=" + urlBorne)));
	}
	else
	{
		manager->get(QNetworkRequest(QUrl("https://fallonloic.fr/PPE2/API/ajoutborne.php?prix=" + prixBorne + "&libelle=" + nomBorne + "&adresseMac=" + typeBorne + "&adresseIp=" + idBorne)));
	}

	Conso oui = new Conso;
}


void Conso::ajouterConso(QString nomBorne, QString prixBorne, QString numBorne, QString typeBorne, QString idBorne, QString url)
{

	int items = ui.TableBorne->rowCount();
	const int colonn = 1;

	if (items < 1)
	{
		if (nomBorne != "" && prixBorne != "" && numBorne != "" && typeBorne != "" && idBorne != "")
		{
			if (url == "")
			{
				int nbLines = ui.TableBorne->rowCount();
				ui.TableBorne->setRowCount(nbLines + 1);
				ui.TableBorne->setItem(nbLines, 0, new QTableWidgetItem(numBorne));
				ui.TableBorne->setItem(nbLines, 1, new QTableWidgetItem(nomBorne));
				ui.TableBorne->setItem(nbLines, 2, new QTableWidgetItem(prixBorne));
				ui.TableBorne->setItem(nbLines, 3, new QTableWidgetItem(typeBorne));
				ui.TableBorne->setItem(nbLines, 4, new QTableWidgetItem(idBorne));
				ui.TableBorne->setItem(nbLines, 5, new QTableWidgetItem("image/Pas_d'image_disponible.png"));
			}
			else
			{
				int nbLines = ui.TableBorne->rowCount();
				ui.TableBorne->setRowCount(nbLines + 1);
				ui.TableBorne->setItem(nbLines, 0, new QTableWidgetItem(numBorne));
				ui.TableBorne->setItem(nbLines, 1, new QTableWidgetItem(nomBorne));
				ui.TableBorne->setItem(nbLines, 2, new QTableWidgetItem(prixBorne));
				ui.TableBorne->setItem(nbLines, 3, new QTableWidgetItem(typeBorne));
				ui.TableBorne->setItem(nbLines, 4, new QTableWidgetItem(idBorne));
				ui.TableBorne->setItem(nbLines, 5, new QTableWidgetItem(url));
			}
		}
		else
		{
			QMessageBox::critical(this, "ALERTE", "Veuillez remplir les champs ci dessus !");
		}
	}

	for (int i = 0; i < items; i++)
	{
		qDebug() << items;
		if (nomBorne != ui.TableBorne->item(i, colonn)->text())
		{
			if (nomBorne != "" && prixBorne != "" && numBorne != "" && typeBorne != "" && idBorne != "")
			{
				if (url == "")
				{
					int nbLines = ui.TableBorne->rowCount();
					ui.TableBorne->setRowCount(nbLines + 1);
					ui.TableBorne->setItem(nbLines, 0, new QTableWidgetItem(numBorne));
					ui.TableBorne->setItem(nbLines, 1, new QTableWidgetItem(nomBorne));
					ui.TableBorne->setItem(nbLines, 2, new QTableWidgetItem(prixBorne));
					ui.TableBorne->setItem(nbLines, 3, new QTableWidgetItem(typeBorne));
					ui.TableBorne->setItem(nbLines, 4, new QTableWidgetItem(idBorne));
					ui.TableBorne->setItem(nbLines, 5, new QTableWidgetItem("image/Pas_d'image_disponible.png"));
					i = items;

				}
				else
				{
					int nbLines = ui.TableBorne->rowCount();
					ui.TableBorne->setRowCount(nbLines + 1);
					ui.TableBorne->setItem(nbLines, 0, new QTableWidgetItem(numBorne));
					ui.TableBorne->setItem(nbLines, 1, new QTableWidgetItem(nomBorne));
					ui.TableBorne->setItem(nbLines, 2, new QTableWidgetItem(prixBorne));
					ui.TableBorne->setItem(nbLines, 3, new QTableWidgetItem(typeBorne));
					ui.TableBorne->setItem(nbLines, 4, new QTableWidgetItem(idBorne));
					ui.TableBorne->setItem(nbLines, 5, new QTableWidgetItem(url));
					i = items;

				}

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
	while (ui.TableBorne->rowCount() > 0)
	{
		ui.TableBorne->removeRow(0);
	}
}
