#ifndef DBOPERATIONS_H
#define DBOPERATIONS_H

#include <QtSql/QtSql>
#include <QMessageBox>

class DbOperations
{
public:
    DbOperations();

    //bool connect(QString hostName, int port, QString baseName, QString userName, QString password);
    bool connect(QString databaseName);

    QSqlQuery executeQuery(QString q);
};

#endif // DBOPERATIONS_H
