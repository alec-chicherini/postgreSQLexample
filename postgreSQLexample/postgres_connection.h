#pragma once

#include <QWidget>
#include "ui_postgres_connection.h"

#include <QLabel>
#include <qlayout.h>
#include <QPushButton>
#include <QLineEdit>
#include <qtextedit.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtSql>
#include <QSqlQuery>
//#include "window.h"

class postgres_connection : public QWidget
{
	Q_OBJECT

	QLabel* labelHostName;
	QLabel* labelPort;
	QLabel* labelUser;
	QLabel* labelPassword;
	QLabel* labelDataBaseName;
	QLabel* labelTestMsg;

	QLineEdit* editHostName;
	QLineEdit* editPort;
	QLineEdit* editUser;
	QLineEdit* editPassword;
	QLineEdit* editDataBaseName;

	QPushButton* buttonTest;
	QPushButton* buttonSave;

public:
	postgres_connection(QWidget *parent = Q_NULLPTR);
	~postgres_connection();

private:
	Ui::postgres_connection ui;

public slots:
	void testMsgChanged(QString str);
	void pressTestButton();

signals:
	
	void sendConnectionData(
		QString host,
		QString port,
		QString user,
		QString pass,
		QString dbname);

	void saveButtonPressed() ;

};
