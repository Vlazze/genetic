#ifndef DBOPERATIONS_H
#define DBOPERATIONS_H

#include <QtSql/QtSql>
#include <QMessageBox>
#include <QVector>
#include <QFileDialog>
#include "algorithm/group.h"
#include "algorithm/room.h"
#include "algorithm/subject.h"
#include "algorithm/teacher.h"

class DbOperations
{
private:

    QSqlDatabase db;

public:

    QString databaseFileName;

    DbOperations();

    bool connect(QString databaseName);

    void backup();

    QSqlQuery executeQuery(QString q);

    QVector<group *> getGroupsInfo(unsigned int semesterParity);

    QVector<room *> getRoomsInfo();

    QVector<subject *> getSubjectsInfo();

    QVector<teacher *> getTeachersInfo();
};

#endif // DBOPERATIONS_H
