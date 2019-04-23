#pragma once

#include <QWidget>
#include "ui_Facture.h"

class Facture : public QWidget
{
	Q_OBJECT

public:
	Facture(QWidget *parent = Q_NULLPTR);
	~Facture();
	void ListeFacture();
	void HTMLFacture();
	void AfficherFacture(QString idCommande, QString dateCommande, QString codeEvent, QString idClient, QString nom, QString prenom, QString idBornes, QString prix, QString libelle, QString dateDebut, QString dateFin, QString adresse, QString ville, QString cp);


private:
	Ui::Facture ui;
};

