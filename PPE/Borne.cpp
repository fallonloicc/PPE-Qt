#include "Borne.h"
#include <QtWidgets>
#include <QMessageBox>
#include <QNetworkAccessManager> 
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

Borne::Borne(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	loadBorne();
	connect(ui.AddButton, &QAbstractButton::clicked, this, &Borne::RecupInfo);
	connect(ui.DelButton, &QAbstractButton::clicked, this, &Borne::DeleteBorne);
}


QString Borne::getName() const
{
	return m_name;
}

void Borne::setName(QString const& name)
{
	m_name = name;
}

void Borne::loadBorne()
{
	// create custom temporary event loop on stack
	QEventLoop eventLoop;

	// "quit()" the event-loop, when the network request "finished()"
	QNetworkAccessManager mgr;
	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	// the HTTP request
	QNetworkRequest req(QUrl(QString("https://ibm-patisserie-mysql-php-20190301075256009-spontaneous-toucan.eu-gb.mybluemix.net/API/bornes.php")));
	QNetworkReply *reply = mgr.get(req);
	eventLoop.exec(); // blocks stack until "finished()" has been called

	if (reply->error() == QNetworkReply::NoError) {

		QString strReply = (QString)reply->readAll();

		//parse json
		qDebug() << "Response:" << strReply;
		QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
		QJsonArray json_array = jsonResponse.array();

		foreach(const QJsonValue &value, json_array) {

			QJsonObject json_obj = value.toObject();
			qDebug() << json_obj["id"].toString();
			qDebug() << json_obj["nom"].toString();
		}

		delete reply;
	}
	else {
		//failure
		qDebug() << "Failure" << reply->errorString();
		delete reply;
	}


}


void Borne::DeleteBorne()
{
	int numLigne = ui.TableBorne->currentRow();
	ui.TableBorne->removeRow(numLigne);
}

void Borne::RecupInfo()
{
	QString nomBorne = ui.editNom->text();
	QString prixBorne = ui.editPrix->text();
	QString numBorne = ui.editNum->text();
	QString typeBorne = ui.editType->text();

	ajouterBorne(nomBorne, prixBorne, numBorne, typeBorne);
}


void Borne::ajouterBorne(QString nomBorne, QString prixBorne, QString numBorne, QString typeBorne)
{

	int items = ui.TableBorne->rowCount();
	const int colonn = 1;

	if (items < 1)
	{
		if (nomBorne != "" && prixBorne != "" && numBorne != "" && typeBorne != "")
		{
			
			int nbLines = ui.TableBorne->rowCount();
			ui.TableBorne->setRowCount(nbLines + 1);
			ui.TableBorne->setItem(nbLines, 0, new QTableWidgetItem(nomBorne));
			ui.TableBorne->setItem(nbLines, 1, new QTableWidgetItem(prixBorne));
			ui.TableBorne->setItem(nbLines, 2, new QTableWidgetItem(numBorne));
			ui.TableBorne->setItem(nbLines, 3, new QTableWidgetItem(typeBorne));

			ui.editNom->clear();
			ui.editPrix->clear();
			ui.editNum->clear();
			ui.editType->clear();
		}
		else
		{
			QMessageBox::critical(this, "ALERTE", "Veuillez remplir les champs ci dessus !");
		}
	}

	for (int i = 0; i < items; i++)
	{
		if (ui.editNom->text() != ui.TableBorne->item(i,colonn)->text())
		{
			if (ui.editNom->text() != "" && ui.editNum->text() != "" && ui.editPrix->text() != "" && ui.editType->text() != "")
			{
				QString nomBorne = ui.editNom->text();
				QString prixBorne = ui.editPrix->text();
				QString numBorne = ui.editNum->text();
				QString typeBorne = ui.editType->text();

				int nbLines = ui.TableBorne->rowCount();
				ui.TableBorne->setRowCount(nbLines + 1);
				ui.TableBorne->setItem(nbLines, 0, new QTableWidgetItem(nomBorne));
				ui.TableBorne->setItem(nbLines, 1, new QTableWidgetItem(prixBorne));
				ui.TableBorne->setItem(nbLines, 2, new QTableWidgetItem(numBorne));
				ui.TableBorne->setItem(nbLines, 3, new QTableWidgetItem(typeBorne));

				ui.editNom->clear();
				ui.editPrix->clear();
				ui.editNum->clear();
				ui.editType->clear();
			}
			else
			{
				QMessageBox::critical(this, "ALERTE", "Veuillez remplir les champs ci dessous !");
			}
		}
		else
		{
			QMessageBox::critical(this, "ALERTE", "Le nom est déjà prit !");
		}
	}
}

	
