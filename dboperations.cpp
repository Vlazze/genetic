#include "dboperations.h"

DbOperations::DbOperations()
{
}

//bool DbOperations::connect(QString hostName, int port, QString baseName, QString userName, QString password)
//{
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

//    db.setHostName(hostName);
//    db.setPort(port);
//    db.setDatabaseName(baseName);
//    db.setUserName(userName);
//    db.setPassword(password);

//    if (!db.open())
//    {
//        QMessageBox msgBox;

//        msgBox.setWindowTitle("Connection status");
//        msgBox.setText("Connecting...");
//        msgBox.setIcon(QMessageBox::Information);
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.setInformativeText(db.lastError().text());
//        msgBox.exec();

//        return false;
//    }
//    return true;
//}

bool DbOperations::connect(QString databaseName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(databaseName);

    if (!db.open())
    {
        QMessageBox msgBox;

        msgBox.setWindowTitle("Connection status");
        msgBox.setText("Connecting...");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setInformativeText(db.lastError().text());
        msgBox.exec();

        return false;
    }
    return true;
}

QSqlQuery DbOperations::executeQuery(QString q)
{
    QSqlQuery query;

    if (!query.exec(q))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Query status");
        msgBox.setText("Query failed!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setInformativeText(query.lastError().text());
        msgBox.exec();
    }

    return query;
}
