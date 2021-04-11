#include "postgres_connection.h"


postgres_connection::postgres_connection(QWidget *parent): QWidget(parent)
{
	
	ui.setupUi(this);
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	this->setFixedSize(400, 300);

	labelHostName = new QLabel("HostName:",this);
	labelPort = new QLabel("Port:", this);
	labelUser = new QLabel("User :", this);
	labelPassword = new QLabel("Password:", this);
	labelDataBaseName = new QLabel("DataBaseName:", this);

	labelTestMsg = new QLabel(this);

	editHostName = new QLineEdit("127.0.0.1", this);
	editPort = new QLineEdit("5432",this);
	editUser = new QLineEdit("test",this);
	editPassword = new QLineEdit("12345Ty",this);
	editDataBaseName = new QLineEdit("example_db_1",this);

	buttonTest = new QPushButton("Test", this);
	buttonSave = new QPushButton("Save", this);

	connect(
		buttonTest,
		&QAbstractButton::pressed,
		this,
		[&] {emit sendConnectionData(
			editHostName->text(),
			editPort->text(),
			editUser->text(),
			editPassword->text(),
			editDataBaseName->text());}
	);

	connect(buttonSave,&QAbstractButton::pressed,this, &postgres_connection::saveButtonPressed);

	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->addWidget(labelHostName, 0, 0, Qt::AlignTop);
	mainLayout->addWidget(editHostName, 0, 1, Qt::AlignTop);
	mainLayout->addWidget(labelPort, 1, 0, Qt::AlignTop);
	mainLayout->addWidget(editPort, 1, 1, Qt::AlignTop);
	mainLayout->addWidget(labelUser, 2, 0, Qt::AlignTop);
	mainLayout->addWidget(editUser, 2, 1, Qt::AlignTop);
	mainLayout->addWidget(labelPassword, 3, 0, Qt::AlignTop);
	mainLayout->addWidget(editPassword, 3, 1, Qt::AlignTop);
	mainLayout->addWidget(labelDataBaseName, 4, 0, Qt::AlignTop);
	mainLayout->addWidget(editDataBaseName, 4, 1, Qt::AlignTop);

	mainLayout->addWidget(labelTestMsg, 5, 0,2,2, Qt::AlignTop);
	mainLayout->addWidget(buttonTest, 7, 0, Qt::AlignTop);
	mainLayout->addWidget(buttonSave, 7, 1, Qt::AlignTop);

	setLayout(mainLayout);
}

postgres_connection::~postgres_connection()
{
}

void postgres_connection::testMsgChanged(QString str) {
	labelTestMsg->setText(str);

}

void postgres_connection::pressTestButton()
{
	emit sendConnectionData(
		editHostName->text(),
		editPort->text(),
		editUser->text(),
		editPassword->text(),
		editDataBaseName->text());
}
