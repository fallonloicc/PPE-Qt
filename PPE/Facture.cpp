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

Facture::Facture(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	int idFacture = 1;

	time_t temps;

	struct tm datetime;
	char  format[32];

	time(&temps);

	temps += 7 * 86400;

	datetime = *localtime(&temps);

	strftime(format, 32, "%Y-%m-%d", &datetime);

	QVariantHash dataContext;

	dataContext["borne_name"] = "Borne 1";
	dataContext["id_Facture"] = idFacture;
	dataContext["borne_id"] = "15";
	dataContext["TODO"] = format;

	//Read file directly from resources with help of QFile
	QFile data(":/PPE/oui.html");
	if (data.open(QFile::ReadOnly))
	{
		QByteArray res = data.readAll();
		Mustache::Renderer renderer;
		Mustache::QtVariantContext context(dataContext);
		ui.webEngineView->setHtml(renderer.render(res, &context));
	}
	else
	{
		ui.webEngineView->setHtml("ERROR");
	}
}

Facture::~Facture()
{
}
