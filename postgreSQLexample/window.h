#pragma once
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <qlayout.h>
#include <QPushButton>
#include <QLineEdit>
#include <qtextedit.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtSql>
#include <QSqlQuery>
#include "postgres_connection.h"
#include <QCloseEvent>
//#include "S:\Code\Qt\6.0.2\Src\qtbase\src\plugins\sqldrivers\psql\qsql_psql.cpp"
//#include "S:\Code\Qt\6.0.2\Src\qtbase\src\plugins\sqldrivers\psql\qsql_psql.h"

class window :
    public QWidget
{
    Q_OBJECT
    QLabel* dbgMsg;
    QLabel* infoMsg;
    QLineEdit* input;
    QPushButton* ExecButton;
    QPushButton* connectionButton;
    QTextEdit* output;
    postgres_connection* connectionWidget;
    QSqlDatabase db;

    void window::closeEvent(QCloseEvent* event);

    bool isConnectionSuccessful = false;
   
public:
    explicit window(QWidget* parent = 0);

public slots:

void createPostgresConnection(
    QString host,
    QString port,
    QString user,
    QString pass,
    QString dbname);

void executeSQLQuery();
void changeExecButtonState(bool b);

signals:
    void statusMsgChanged(QString str);
    void connectionStateChanged(bool state);
};

