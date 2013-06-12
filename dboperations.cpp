#include "dboperations.h"

DbOperations::DbOperations()
{
}

bool DbOperations::connect(QString databaseName)
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");

    this->db.setDatabaseName(databaseName);

    if (!this->db.open())
    {
        QMessageBox msgBox;

        msgBox.setWindowTitle("Connection status");
        msgBox.setText("Connecting...");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setInformativeText(this->db.lastError().text());
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

QVector<group *> DbOperations::getGroupsInfo(unsigned int semesterParity) // even || odd
{
    QSqlQuery query;
    QVector<group *> groups;
    int i = 0;
    int semester = 0;

    query = this->executeQuery("SELECT groupId, specialtyId "
                               "FROM groups "
                               "WHERE specialtyId = 1 "
                               "AND deleted <> 1");

    if (semesterParity == 2)
        i = 1;
    else
        i = 0;

    while (query.next())
    {
        switch (query.value(0).toInt())
        {
        case 1: case 2: case 3:
            semester = 1 + i;
            break;

        case 4: case 5: case 6:
            semester = 3 + i;
            break;

        case 7: case 8: case 9:
            semester = 5 + i;
            break;

        case 10: case 11: case 12:
            semester = 7 + i;
            break;
        }
        //group * g = new group();
        groups.push_back(group::create(query.value(0).toInt(),0,semester,query.value(1).toInt()));
    }

    return groups;
}

QVector<room *> DbOperations::getRoomsInfo()
{
    QSqlQuery query;
    QVector<room *> rooms;

    query = this->executeQuery("SELECT roomId, roomType, own "
                               "FROM room "
                               "WHERE deleted <> 1");

    while (query.next())
    {
        if (QString::compare(query.value(1).toString(), "Лекционная", Qt::CaseInsensitive) == 0)
        {
            rooms.push_back(room::create(query.value(0).toInt(), 0, lectureRoom));
        }
        else if (QString::compare(query.value(2).toString(), "ИС", Qt::CaseInsensitive))
        {
            rooms.push_back(room::create(query.value(0).toInt(), 0, ourDepartmentRoom));
        }
        else
        {
            rooms.push_back(room::create(query.value(0).toInt(), 0, otherDepartmentRoom));
        }
    }

    return rooms;
}

QVector<subject *> DbOperations::getSubjectsInfo()
{
    QSqlQuery query;
    QSqlQuery query_2;
    QVector<subject *> subjects;
    unsigned int ToS = 2;
    QSet<int> semesters;

    query = this->executeQuery("SELECT DISTINCT curriculum.subjectId, subject.subjectName "
                               "FROM curriculum "
                               "JOIN subject ON curriculum.subjectId = subject.subjectId "
                               "WHERE curriculum.specialtyId = 1 "
                               "AND curriculum.deleted <> 1 "
                               "AND curriculum.classTypeId > 1 "
                               "AND curriculum.specialtyId = 1");

    while (query.next())
    {
        semesters.clear();

        query_2 = this->executeQuery("SELECT semesterId "
                                     "FROM curriculum "
                                     "WHERE subjectId="+query.value(0).toString());

        while (query_2.next())
        {
            semesters.insert(query_2.value(0).toInt());
        }

        subjects.push_back(subject::create(query.value(0).toInt(),
                                            query.value(1).toString(),
                                            1,
                                            4,
                                            TypeOfSubject(ToS),
                                            semesters));
    }
    return subjects;
}

QVector<teacher *> DbOperations::getTeachersInfo()
{
    QSqlQuery query_1;
    QSqlQuery query_2;
    QSqlQuery query_3;
    QVector<teacher *> teachers;
    QSet<int> subjectsCanTeach;
    int lectureLoad = 0;
    int practiceLoad = 0;

    query_1 = this->executeQuery("SELECT load.teacherId, teacher.teacherName, subjectId, classTypeId "
                                 "FROM load "
                                 "JOIN teacher ON load.teacherId = teacher.teacherId "
                                 "WHERE load.deleted <> 1");

    while (query_1.next())
    {
        subjectsCanTeach.clear();
        query_2 = this->executeQuery("SELECT DISTINCT subjectId "
                                     "FROM load "
                                     "WHERE teacherId=" + query_1.value(0).toString() +
                                     " AND deleted <> 1");

        while (query_2.next())
        {
            subjectsCanTeach.insert(query_2.value(0).toInt());
        }

        query_3 = this->executeQuery("SELECT hours "
                                     "FROM curriculum "
                                     "WHERE subjectId=" + query_1.value(2).toString() +
                                     " AND classTypeId=" + query_1.value(3).toString() +
                                     " AND deleted <> 1");

        while (query_3.next())
            if (query_1.value(3).toInt() == 1)
            {
                lectureLoad = int(query_3.value(0).toInt() / 18);
            }
            else
            {
                practiceLoad = int(query_3.value(0).toInt() / 18);
            }

        teachers.push_back(teacher::create(query_1.value(0).toInt(),
                                            query_1.value(1).toString(),
                                            0,
                                            practiceLoad,
                                            subjectsCanTeach));
    }
    return teachers;
}

void DbOperations::backup()
{
    QMessageBox mb;

    if (this->db.isOpen())
    {
        QFile dbFile;
        QFile bckFile;
        QDir bckDir;
             bckDir.mkdir(".\\backup");
        QString saveFileName = QFileDialog::getSaveFileName(0, QObject::trUtf8("Сохранить резервную копию"), QObject::tr(".\\backup"), QObject::tr("*.db_bckup"));

        if (!saveFileName.endsWith(".db_bckup", Qt::CaseInsensitive))
        {
            saveFileName += ".db_bckup";
        }

        dbFile.setFileName(this->databaseFileName);

        if (saveFileName.isEmpty())
        {
            mb.setIcon(QMessageBox::Critical);
            mb.setText("ERROR!");
            mb.setInformativeText("Cannot save to this file: " + saveFileName);
            mb.exec();
            return;
        }

        if (!dbFile.open(QIODevice::ReadOnly))
        {
            mb.setIcon(QMessageBox::Critical);
            mb.setText(QObject::trUtf8("ОШИБКА!"));
            mb.setInformativeText(QObject::trUtf8("Невозможно открыть файл для чтения: ") + this->databaseFileName);
            mb.exec();
            return;
        }

        bckFile.setFileName(saveFileName);

        if (!bckFile.open(QIODevice::WriteOnly))
        {
            mb.setIcon(QMessageBox::Critical);
            mb.setText(QObject::trUtf8("ОШИБКА!"));
            mb.setInformativeText(QObject::trUtf8("Невозможно открыть файл для записи: ") + saveFileName);
            mb.exec();
            return;
        }

        if (bckFile.write(dbFile.readAll()) == -1)
        {
            mb.setIcon(QMessageBox::Critical);
            mb.setText(QObject::trUtf8("ОШИБКА!"));
            mb.setInformativeText(QObject::trUtf8("Невозможно записать в файл"));
            mb.exec();
            return;
        }
        else
        {

            mb.setIcon(QMessageBox::Information);
            mb.setText(QObject::trUtf8("Копия успешно создана."));
            mb.setInformativeText(QObject::trUtf8("Файл копии: ") + saveFileName);
            mb.exec();
        }

        dbFile.close();
        bckFile.close();
    }
    else
    {
        mb.setIcon(QMessageBox::Critical);
        mb.setText(QObject::trUtf8("ОШИБКА!"));
        mb.setInformativeText(QObject::trUtf8("Откройте БД для копирования"));
        mb.exec();
        return;
    }
}
