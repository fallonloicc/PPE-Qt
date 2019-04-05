#include <QWidget>
#include "ui_PPE.h"

class PPE : public QMainWindow
{
	Q_OBJECT

public:
	PPE(QWidget *parent = Q_NULLPTR);

private:
	Ui::PPEClass ui;

	void removeWidget();
	void ShowFacture();
	void ShowClient();
	void ShowBorne();
	void CloseWin();
};