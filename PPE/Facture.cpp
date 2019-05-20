#include "Facture.h"
#include "PPE.h"
#include <QtWidgets>
#include "mustach.h"
#include <QtWidgets>
#include <string>
#include <cmath>
#include <QTimer>
#include <QFile>
#include <QWebEngineView>
#include <QMetaType> 
#include <QNetworkAccessManager> 
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

Facture::Facture(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ListeFacture();
	
	connect(ui.valBtn, &QAbstractButton::clicked, this, &Facture::HTMLFacture);
	
}

Facture::~Facture()
{
}

void Facture::ListeFacture()
{
	// create custom temporary event loop on stack
	QEventLoop eventLoop;

	// "quit()" the event-loop, when the network request "finished()"
	QNetworkAccessManager mgr;
	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	// the HTTP request
	QNetworkRequest req(QUrl(QString("https://fallonloic.fr/PPE2/API/AllCommande.php")));
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
			QString idCommande = json_obj["idCommande"].toString();
			QString dateCommande= json_obj["dateCommande"].toString();
			QString codeEvent = json_obj["codeEvent"].toString();
			ui.comboBox->addItem(idCommande+" - "+dateCommande+"|| Code : "+codeEvent);

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

void Facture::HTMLFacture()
{
	QString id = ui.comboBox->currentText();

	// create custom temporary event loop on stack
	QEventLoop eventLoop;

	// "quit()" the event-loop, when the network request "finished()"
	QNetworkAccessManager mgr;
	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

	// the HTTP request
	QNetworkRequest req(QUrl(QString("https://fallonloic.fr/PPE2/API/AllCommandeByID.php?idCommande="+id)));
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
			QString idCommande = json_obj["idCommande"].toString();
			QString dateCommande = json_obj["dateCommande"].toString();
			QString codeEvent = json_obj["codeEvent"].toString();
			QString idClient = json_obj["idClient"].toString();
			QString nom = json_obj["nom"].toString();
			QString prenom = json_obj["prenom"].toString();
			QString idBornes = json_obj["idBornes"].toString();
			QString prix = json_obj["prix"].toString();
			QString libelle = json_obj["libelle"].toString();
			QString dateDebut = json_obj["debutDate"].toString();
			QString dateFin = json_obj["finDate"].toString();
			QString adresse = json_obj["adresse"].toString();
			QString ville = json_obj["ville"].toString();
			QString cp = json_obj["cp"].toString();
			
			AfficherFacture(idCommande, dateCommande, codeEvent, idClient, nom, prenom, idBornes, prix, libelle, dateDebut, dateFin, adresse, ville, cp);

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

void Facture::AfficherFacture(QString idCommande, QString dateCommande, QString codeEvent, QString idClient, QString nom, QString prenom, QString idBornes, QString prix, QString libelle, QString dateDebut, QString dateFin, QString adresse, QString ville, QString cp)
{
	QDate DateDebut = QDate::fromString(dateDebut, "dd/MM/yyyy");
	QDate DateFin = QDate::fromString(dateFin, "dd/MM/yyyy");

	int dure = DateDebut.daysTo(DateFin)+1;
	QString duree = QString::number(dure);

	QVariantHash dataContext;

	dataContext["idCommande"] = idCommande;
	dataContext["dateCommande"] = dateCommande;
	dataContext["codeEvent"] = codeEvent;
	dataContext["idClient"] = idClient;
	dataContext["nom"] = nom;
	dataContext["prenom"] = prenom;
	dataContext["idBornes"] = idBornes;
	dataContext["prix"] = prix;
	dataContext["libelle"] = libelle;
	dataContext["dateDebut"] = dateDebut;
	dataContext["dateFin"] = dateFin;
	dataContext["adresse"] = adresse;
	dataContext["ville"] = ville;
	dataContext["cp"] = cp;
	dataContext["number"] = duree;
	

	qDebug() << dataContext;

	//Read file directly from resources with help of QFile
	QFile data("oui.html");
	if (data.open(QFile::ReadOnly))
	{
		QByteArray res = data.readAll();
		Mustache::Renderer renderer;
		Mustache::QtVariantContext context(dataContext);
		ui.webEngineView->setHtml(renderer.render(res, &context));
		qDebug() << "ça fonctionne !!!";

	}
	else
	{
		ui.webEngineView->setHtml("ERROR");
		qDebug() << "ça fonctionne pas!!!";

	}
}
