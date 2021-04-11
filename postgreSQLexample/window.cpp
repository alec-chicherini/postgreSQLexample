#include "window.h"

window::window(QWidget* w) :QWidget(w)
{

	dbgMsg = new QLabel(this);

	infoMsg = new QLabel(this);
	if (!isConnectionSuccessful)infoMsg->setText("Check connection properties --> ");
	else infoMsg->setText("Enter SQL query like: \"SELECT * FROM postgre\"");

	input = new QLineEdit(this);
	input->setText("SELECT * FROM person");
	output = new QTextEdit(this);
	QFont outFont;
	outFont.setFamily("Courier New");
	output->setFont(outFont);
	ExecButton = new QPushButton(this);
	ExecButton->setText("execute");
	ExecButton->setDisabled(1);

	connectionButton = new QPushButton(this);
	connectionButton->setText("Connect");
	
	connectionWidget = new postgres_connection();

	connect(connectionButton, &QAbstractButton::pressed, connectionWidget, [&] {connectionWidget->show(); this->setDisabled(1); });
	connect(this, &window::statusMsgChanged, connectionWidget, &postgres_connection::testMsgChanged);
	connect(connectionWidget, &postgres_connection::sendConnectionData, this, &window::createPostgresConnection);
	connect(connectionWidget, &postgres_connection::saveButtonPressed, this, [&] {this->setDisabled(0); connectionWidget->hide(); });
	connect(connectionWidget, &postgres_connection::saveButtonPressed, connectionWidget,&postgres_connection::pressTestButton);
	connect(ExecButton, &QAbstractButton::pressed, this, &window::executeSQLQuery);
	connect(this, &window::connectionStateChanged, this, &window::changeExecButtonState);

	//layout settings
	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->setColumnStretch(0, 6);
	mainLayout->setColumnStretch(1, 1);

	mainLayout->addWidget(infoMsg, 0, 0, Qt::AlignTop);
	mainLayout->addWidget(connectionButton, 0, 1, Qt::AlignTop);
	mainLayout->addWidget(input, 1, 0, Qt::AlignTop);
	mainLayout->addWidget(ExecButton, 1, 1, Qt::AlignTop);
	mainLayout->addWidget(output, 2, 0, 1, 2);
	mainLayout->addWidget(dbgMsg, 3, 0, 1, 2, Qt::AlignBottom);

	setLayout(mainLayout);

};

void window::createPostgresConnection(
	QString host,
	QString port,
	QString user,
	QString pass,
	QString dbname)
{
	if (isConnectionSuccessful) {
		db.close();
		db.removeDatabase("QPSQL");}
	db = QSqlDatabase::addDatabase("QPSQL");
	db.setHostName(host);
	db.setPort(port.toInt());
	db.setDatabaseName(dbname);
	db.setPassword(pass);
	db.setUserName(user);

	isConnectionSuccessful = db.open();
	emit connectionStateChanged(!isConnectionSuccessful);
	QString statusMsg;
	
	if(isConnectionSuccessful) statusMsg = "Database connection sucessful";
	else {
		statusMsg = "Database connection ERROR:\n";
		statusMsg += db.lastError().databaseText();
	};

	emit statusMsgChanged(statusMsg);
	dbgMsg->setText(statusMsg);

};

void window::closeEvent(QCloseEvent* event)
{
	connectionWidget->close();
	event->accept();
}

void window::executeSQLQuery() 
{
	output->clear();
	QSqlQuery query(input->text());
	dbgMsg->setText(query.lastError().text());
	int num_of_tables = query.record().count();
	
	while (query.next())
	{

		QString s;
		QTextStream str(&s);
		str.setFieldWidth(20);
		str.setFieldAlignment(QTextStream::AlignLeft);
		str.setPadChar(' ');
		for (int i = 0; i < num_of_tables; i++) 
		{

			str<<query.value(i).toString();
		
			
		}
		str.setFieldWidth(0);
		output->append(s);
		
	}

};

void window::changeExecButtonState(bool b) {
	ExecButton->setDisabled(b);
	if (!isConnectionSuccessful)infoMsg->setText("Check connection properties --> ");
	else infoMsg->setText("Enter SQL query like: \"SELECT * FROM (NAME OF RELATION)\"");
};

