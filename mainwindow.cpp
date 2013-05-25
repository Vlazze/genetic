#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "schedule_constructor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->showButton->setVisible(false);

    // set table SPECIALTY appearance
    ui->specialtyTable->setColumnCount(3);
    ui->specialtyTable->setColumnWidth(1, 150);
    ui->specialtyTable->setColumnWidth(2, 650);

    QStringList specialtyHorHeaders;
    specialtyHorHeaders.push_back("ID");
    specialtyHorHeaders.push_back("Code");
    specialtyHorHeaders.push_back("Name");

    ui->specialtyTable->setHorizontalHeaderLabels(specialtyHorHeaders);
    ui->specialtyTable->setColumnHidden(0, true);

    // set table SUBJECT appearance
    ui->subjectTable->setColumnCount(4);
    ui->subjectTable->setColumnWidth(1, 450);
    ui->subjectTable->setColumnWidth(2, 150);
    ui->subjectTable->setColumnWidth(3, 200);

    QStringList subjectHorHeaders;
    subjectHorHeaders.push_back("ID");
    subjectHorHeaders.push_back("Name");
    subjectHorHeaders.push_back("Short");
    subjectHorHeaders.push_back("Type");

    ui->subjectTable->setHorizontalHeaderLabels(subjectHorHeaders);
    ui->subjectTable->setColumnHidden(0, true);

    // set table ROOM appearance
    ui->roomTable->setColumnCount(5);
    ui->roomTable->setColumnWidth(1, 200);
    ui->roomTable->setColumnWidth(2, 200);
    ui->roomTable->setColumnWidth(3, 200);
    ui->roomTable->setColumnWidth(4, 200);

    QStringList roomHorHeaders;
    roomHorHeaders.push_back("ID");
    roomHorHeaders.push_back("#");
    roomHorHeaders.push_back("Capacity");
    roomHorHeaders.push_back("Type");
    roomHorHeaders.push_back("Own");

    ui->roomTable->setHorizontalHeaderLabels(roomHorHeaders);
    ui->roomTable->setColumnHidden(0, true);

    // set table TEACHER appearance
    ui->teacherTable->setColumnCount(3);
    ui->teacherTable->setColumnWidth(1, 600);
    ui->teacherTable->setColumnWidth(2, 200);

    QStringList teacherHorHeaders;
    teacherHorHeaders.push_back("ID");
    teacherHorHeaders.push_back("Name");
    teacherHorHeaders.push_back("Department");

    ui->teacherTable->setHorizontalHeaderLabels(teacherHorHeaders);
    ui->teacherTable->setColumnHidden(0, true);

    // set table GROUPS appearance
    ui->groupsTable->setColumnCount(3);
    ui->groupsTable->setColumnWidth(1, 300);
    ui->groupsTable->setColumnWidth(2, 500);

    QStringList groupsHorHeaders;
    groupsHorHeaders.push_back("ID");
    groupsHorHeaders.push_back("#");
    groupsHorHeaders.push_back("Specialty");

    ui->groupsTable->setHorizontalHeaderLabels(groupsHorHeaders);
    ui->groupsTable->setColumnHidden(0, true);

    // set table CLASS_TYPE appearance
    ui->classTypeTable->setColumnCount(2);
    ui->classTypeTable->setColumnWidth(1, 800);

    QStringList classTypeHorHeaders;
    classTypeHorHeaders.push_back("ID");
    classTypeHorHeaders.push_back("Type");

    ui->classTypeTable->setHorizontalHeaderLabels(classTypeHorHeaders);
    ui->classTypeTable->setColumnHidden(0, true);

    // set table SEMESTER appearance
    ui->semesterTable->setColumnCount(3);
    ui->semesterTable->setColumnWidth(1, 400);
    ui->semesterTable->setColumnWidth(2, 400);

    QStringList semesterHorHeaders;
    semesterHorHeaders.push_back("ID");
    semesterHorHeaders.push_back("#");
    semesterHorHeaders.push_back("Weeks");

    ui->semesterTable->setHorizontalHeaderLabels(semesterHorHeaders);
    ui->semesterTable->setColumnHidden(0, true);

    //set table CURRICULUM appearance
    ui->curriculumTable->setColumnCount(6);
    ui->curriculumTable->setColumnWidth(1, 300);
    ui->curriculumTable->setColumnWidth(2, 125);
    ui->curriculumTable->setColumnWidth(3, 125);
    ui->curriculumTable->setColumnWidth(4, 125);
    ui->curriculumTable->setColumnWidth(5, 125);

    QStringList curriculumHorHeaders;
    curriculumHorHeaders.push_back("ID");
    curriculumHorHeaders.push_back("Subject");
    curriculumHorHeaders.push_back("Specialty");
    curriculumHorHeaders.push_back("Semester");
    curriculumHorHeaders.push_back("Class type");
    curriculumHorHeaders.push_back("Hours");

    ui->curriculumTable->setHorizontalHeaderLabels(curriculumHorHeaders);
    ui->curriculumTable->setColumnHidden(0, true);

    // set table LOAD appearance
    ui->loadTable->setColumnCount(4);
    ui->loadTable->setColumnWidth(1, 300);
    ui->loadTable->setColumnWidth(2, 250);
    ui->loadTable->setColumnWidth(3, 250);

    QStringList loadHorHeaders;
    loadHorHeaders.push_back("ID");
    loadHorHeaders.push_back("Teacher");
    loadHorHeaders.push_back("Subject");
    loadHorHeaders.push_back("Type");

    ui->loadTable->setHorizontalHeaderLabels(loadHorHeaders);
    ui->loadTable->setColumnHidden(0, true);

    // set table TEACHER_LIMITS appearance
    ui->limitsTable->setColumnCount(3);
    ui->limitsTable->setColumnWidth(1, 400);
    ui->limitsTable->setColumnWidth(2, 400);

    QStringList limitsHorHeaders;
    limitsHorHeaders.push_back("ID");
    limitsHorHeaders.push_back("Teacher");
    limitsHorHeaders.push_back("Limit");

    ui->limitsTable->setHorizontalHeaderLabels(limitsHorHeaders);
    ui->limitsTable->setColumnHidden(0, true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//
//  Function selects info from database
//
void MainWindow::on_showButton_clicked(){}

//
//  Function deletes row from table but not from database
//
void MainWindow::on_deleteButton_clicked()
{
    int row     = 0;    // row of selected item
    QString id;         // ID of selected item
    QMessageBox msgBox;

    msgBox.setWindowTitle("Removing status");
    msgBox.setText("Removing...");
    msgBox.setInformativeText("Are you really want to remove this item?");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    switch (ui->tabWidget->currentIndex())  // which tab is open?
    {
    // SPECIALTY table
    case 0:
        if (ui->specialtyTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->specialtyTable->selectedItems().first()->row();
            id      = ui->specialtyTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE specialty "
                             "SET deleted = 1 "
                             "WHERE specialtyId=" + id);
        }
        break;

    // SUBJECT table
    case 1:
        if (ui->subjectTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->subjectTable->selectedItems().first()->row();
            id      = ui->subjectTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE subject "
                             "SET deleted = 1 "
                             "WHERE subjectId=" + id);
        }
        break;

    // ROOM table
    case 2:
        if (ui->roomTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->roomTable->selectedItems().first()->row();
            id      = ui->roomTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE room "
                             "SET deleted = 1 "
                             "WHERE roomId=" + id);
        }
        break;

    // TEACHER table
    case 3:
        if (ui->teacherTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->teacherTable->selectedItems().first()->row();
            id      = ui->teacherTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE teacher "
                             "SET deleted = 1 "
                             "WHERE teacherId=" + id);
        }
        break;

    // GROUPS table
    case 4:
        if (ui->groupsTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->groupsTable->selectedItems().first()->row();
            id      = ui->groupsTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE groups "
                             "SET deleted = 1 "
                             "WHERE groupId=" + id);
        }
        break;

    // CLASS_TYPE table
    case 5:
        if (ui->classTypeTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->classTypeTable->selectedItems().first()->row();
            id      = ui->classTypeTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE class_type "
                             "SET deleted = 1 "
                             "WHERE classTypeId=" + id);
        }
        break;

    // SEMESTER table
    case 6:
        if (ui->semesterTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->semesterTable->selectedItems().first()->row();
            id      = ui->semesterTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE semester "
                             "SET deleted = 1 "
                             "WHERE semesterId=" + id);
        }
        break;

    // CURRICULUM table
    case 7:
        if (ui->curriculumTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->curriculumTable->selectedItems().first()->row();
            id      = ui->curriculumTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE curriculum "
                             "SET deleted = 1 "
                             "WHERE curriculumId=" + id);
        }
        break;

    // LOAD table
    case 8:
        if (ui->loadTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->loadTable->selectedItems().first()->row();
            id      = ui->loadTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE load "
                             "SET deleted = 1 "
                             "WHERE loadId=" + id);
        }
        break;

    // TEACHER_LIMITS table
    case 9:
        if (ui->limitsTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row     = ui->limitsTable->selectedItems().first()->row();
            id      = ui->limitsTable->item(row, 0)->text();
            dbo.executeQuery("UPDATE teacher_limits "
                             "SET deleted = 1 "
                             "WHERE teacherLimitId=" + id);
        }
        break;
    }
    //MainWindow::on_showButton_clicked();
    MainWindow::on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

//
//  Function adds new row to the selected table
//
void MainWindow::on_addButton_clicked()
{
    switch (ui->tabWidget->currentIndex())  // which tab is open?
    {
    // SPECIALTY table
    case 0:
        ui->specialtyTable->insertRow(ui->specialtyTable->rowCount());
        ui->specialtyTable->setItem(ui->specialtyTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->specialtyTable->setItem(ui->specialtyTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->specialtyTable->setItem(ui->specialtyTable->rowCount()-1, 2, new QTableWidgetItem(""));
        break;

    // SUBJECT table
    case 1:
        ui->subjectTable->insertRow(ui->subjectTable->rowCount());
        ui->subjectTable->setItem(ui->subjectTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->subjectTable->setItem(ui->subjectTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->subjectTable->setItem(ui->subjectTable->rowCount()-1, 2, new QTableWidgetItem(""));
        ui->subjectTable->setItem(ui->subjectTable->rowCount()-1, 3, new QTableWidgetItem(""));
        break;

    // ROOM table
    case 2:
        ui->roomTable->insertRow(ui->roomTable->rowCount());
        ui->roomTable->setItem(ui->roomTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->roomTable->setItem(ui->roomTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->roomTable->setItem(ui->roomTable->rowCount()-1, 2, new QTableWidgetItem(""));
        ui->roomTable->setItem(ui->roomTable->rowCount()-1, 3, new QTableWidgetItem(""));
        ui->roomTable->setItem(ui->roomTable->rowCount()-1, 4, new QTableWidgetItem(""));
        break;

    // TEACHER table
    case 3:
        ui->teacherTable->insertRow(ui->teacherTable->rowCount());
        ui->teacherTable->setItem(ui->teacherTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->teacherTable->setItem(ui->teacherTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->teacherTable->setItem(ui->teacherTable->rowCount()-1, 2, new QTableWidgetItem(""));
        break;

    // GROUPS table
    case 4:
        ui->groupsTable->insertRow(ui->groupsTable->rowCount());
        ui->groupsTable->setItem(ui->groupsTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->groupsTable->setItem(ui->groupsTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->groupsTable->setItem(ui->groupsTable->rowCount()-1, 2, new QTableWidgetItem(""));
        break;

    // CLASS_TYPE table
    case 5:
        ui->classTypeTable->insertRow(ui->classTypeTable->rowCount());
        ui->classTypeTable->setItem(ui->classTypeTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->classTypeTable->setItem(ui->classTypeTable->rowCount()-1, 1, new QTableWidgetItem(""));
        break;

    // SEMESTER table
    case 6:
        ui->semesterTable->insertRow(ui->semesterTable->rowCount());
        ui->semesterTable->setItem(ui->semesterTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->semesterTable->setItem(ui->semesterTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->semesterTable->setItem(ui->semesterTable->rowCount()-1, 2, new QTableWidgetItem(""));
        break;

    // CURRICULUM table
    case 7:
        ui->curriculumTable->insertRow(ui->curriculumTable->rowCount());
        ui->curriculumTable->setItem(ui->curriculumTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->curriculumTable->setItem(ui->curriculumTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->curriculumTable->setItem(ui->curriculumTable->rowCount()-1, 2, new QTableWidgetItem(""));
        ui->curriculumTable->setItem(ui->curriculumTable->rowCount()-1, 3, new QTableWidgetItem(""));
        ui->curriculumTable->setItem(ui->curriculumTable->rowCount()-1, 4, new QTableWidgetItem(""));
        ui->curriculumTable->setItem(ui->curriculumTable->rowCount()-1, 5, new QTableWidgetItem(""));
        break;

    // LOAD table
    case 8:
        ui->loadTable->insertRow(ui->loadTable->rowCount());
        ui->loadTable->setItem(ui->loadTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->loadTable->setItem(ui->loadTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->loadTable->setItem(ui->loadTable->rowCount()-1, 2, new QTableWidgetItem(""));
        ui->loadTable->setItem(ui->loadTable->rowCount()-1, 3, new QTableWidgetItem(""));
        break;

    // TEACHER_LIMITS table
    case 9:
        ui->limitsTable->insertRow(ui->limitsTable->rowCount());
        ui->limitsTable->setItem(ui->limitsTable->rowCount()-1, 0, new QTableWidgetItem(""));
        ui->limitsTable->setItem(ui->limitsTable->rowCount()-1, 1, new QTableWidgetItem(""));
        ui->limitsTable->setItem(ui->limitsTable->rowCount()-1, 2, new QTableWidgetItem(""));
        break;
    }
}

//
//  SPECIALTY table item selected
//
void MainWindow::on_specialtyTable_cellClicked(int row)
{
    ui->lineEdit->setText(ui->specialtyTable->item(row, 1)->text());
    ui->lineEdit_2->setText(ui->specialtyTable->item(row, 2)->text());
}

//
//  SUBJECT table item selected
//
void MainWindow::on_subjectTable_cellClicked(int row)
{
    ui->lineEdit_3->setText(ui->subjectTable->item(row, 1)->text());
    ui->lineEdit_4->setText(ui->subjectTable->item(row, 2)->text());
    ui->lineEdit_12->setText(ui->subjectTable->item(row, 3)->text());
}

//
//  ROOM table item selected
//
void MainWindow::on_roomTable_cellClicked(int row)
{
    ui->lineEdit_5->setText(ui->roomTable->item(row, 1)->text());
    ui->lineEdit_6->setText(ui->roomTable->item(row, 2)->text());
    ui->lineEdit_7->setText(ui->roomTable->item(row, 3)->text());
    ui->lineEdit_16->setText(ui->roomTable->item(row, 4)->text());
}

//
//  TEACHER table item selected
//
void MainWindow::on_teacherTable_cellClicked(int row)
{
    ui->lineEdit_8->setText(ui->teacherTable->item(row, 1)->text());
    ui->lineEdit_10->setText(ui->teacherTable->item(row, 2)->text());
}

//
//  GROUPS table item selected
//
void MainWindow::on_groupsTable_cellClicked(int row)
{
    ui->lineEdit_9->setText(ui->groupsTable->item(row, 1)->text());
}

//
//  CLASS_TYPE table item selected
//
void MainWindow::on_classTypeTable_cellClicked(int row)
{
    ui->lineEdit_11->setText(ui->classTypeTable->item(row, 1)->text());
}

//
//  SEMESTER table item selected
//
void MainWindow::on_semesterTable_cellClicked(int row)
{
    ui->lineEdit_13->setText(ui->semesterTable->item(row, 1)->text());
    ui->lineEdit_14->setText(ui->semesterTable->item(row, 2)->text());
}

//
//  CURRICULUM table item selected
//
void MainWindow::on_curriculumTable_cellClicked(int row)
{
    ui->lineEdit_15->setText(ui->curriculumTable->item(row, 5)->text());
}


//
//  Function sets info into a database (INSERT or UPDATE)
//
void MainWindow::on_saveButton_clicked()
{
    int row;
    QString id;
    QMessageBox msgBox;
    QSqlQuery query;

    msgBox.setWindowTitle("Updating status");
    msgBox.setText("Updating...");
    msgBox.setInformativeText("Are you really want to update this item?");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    switch (ui->tabWidget->currentIndex())  // which tab is open?
    {
    // SPECIALTY table
    case 0:
        if (ui->specialtyTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec()
                && (!ui->lineEdit->text().isEmpty() || !ui->lineEdit_2->text().isEmpty()))
        {
            row = ui->specialtyTable->selectedItems().first()->row();
            id  = ui->specialtyTable->item(row, 0)->text();

            if (id == "")
            {
                query = dbo.executeQuery("SELECT MAX(specialtyId) FROM specialty");
                query.first();
                dbo.executeQuery("INSERT INTO specialty "
                                 "VALUES "
                                 "(" + QString::number(query.value(0).toInt()+1) +
                                 ",'"+ui->lineEdit->text() +
                                 "','" + ui->lineEdit_2->text() + "',0)");
            }
            else
            {
                dbo.executeQuery("UPDATE specialty "
                                 "SET specialtyCode=" + ui->lineEdit->text() +
                                 ", specialtyName='" + ui->lineEdit_2->text() +
                                 "' WHERE specialtyId=" + id);
            }
        }
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        break;

    // SUBJECT table
    case 1:
        if (ui->subjectTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec()
                && (!ui->lineEdit_3->text().isEmpty() || !ui->lineEdit_4->text().isEmpty()))
        {
            row = ui->subjectTable->selectedItems().first()->row();
            id  = ui->subjectTable->item(row, 0)->text();

            if (id == "")
            {
                query = dbo.executeQuery("SELECT MAX(subjectId) FROM subject");
                query.first();
                dbo.executeQuery("INSERT INTO subject "
                                 "VALUES "
                                 "(" + QString::number(query.value(0).toInt()+1) +
                                 ",'" + ui->lineEdit_3->text() +
                                 "','" + ui->lineEdit_4->text() +
                                 "','" + ui->lineEdit_12->text() + "',0)");
            }
            else
            {
                dbo.executeQuery("UPDATE subject "
                                 "SET subjectName='" + ui->lineEdit_3->text() +
                                 "', shortSubjectName='" + ui->lineEdit_4->text() +
                                 "', subjectType='" + ui->lineEdit_12->text() +
                                 "' WHERE subjectId=" + id);
            }
        }
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_12->clear();
        break;

    // ROOM table
    case 2:
        if (ui->roomTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec()
                && (!ui->lineEdit_5->text().isEmpty() || !ui->lineEdit_6->text().isEmpty()
                || !ui->lineEdit_7->text().isEmpty() || !ui->lineEdit_16->text().isEmpty()))
        {
            row = ui->roomTable->selectedItems().first()->row();
            id  = ui->roomTable->item(row, 0)->text();

            if (id == "")
            {
                query = dbo.executeQuery("SELECT MAX(roomId) FROM room");
                query.first();
                dbo.executeQuery("INSERT INTO room "
                                 "VALUES "
                                 "(" + QString::number(query.value(0).toInt()+1) +
                                 ",'" + ui->lineEdit_5->text() +
                                 "'," + ui->lineEdit_6->text() +
                                 ",'" + ui->lineEdit_7->text() +
                                 "','" + ui->lineEdit_16->text() + "',0");
            }
            else
            {
                dbo.executeQuery("UPDATE room "
                                 "SET roomNumber='" + ui->lineEdit_5->text() +
                                 "', capacity=" + ui->lineEdit_6->text() +
                                 ", roomType='" + ui->lineEdit_7->text() +
                                 "',own='"      + ui->lineEdit_16->text() +
                                 "' WHERE roomId=" + id);
            }
        }
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_16->clear();
        break;

    // TEACHER table
    case 3:
        if (ui->teacherTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec()
                && !ui->lineEdit_8->text().isEmpty())
        {
            row = ui->teacherTable->selectedItems().first()->row();
            id  = ui->teacherTable->item(row, 0)->text();

            if (id == "")
            {
                query = dbo.executeQuery("SELECT MAX(teacherId) FROM teacher");
                query.first();
                dbo.executeQuery("INSERT INTO teacher "
                                 "VALUES "
                                 "(" + QString::number(query.value(0).toInt()+1) +
                                 ",'" + ui->lineEdit_8->text() +
                                 "','" + ui->lineEdit_10->text() + "',0)");
            }
            else
            {
                dbo.executeQuery("UPDATE teacher "
                                 "SET teacherName='" + ui->lineEdit_8->text() +
                                 "', department='" + ui->lineEdit_10->text() +
                                 "' WHERE teacherId=" + id);
            }
        }
        ui->lineEdit_8->clear();
        ui->lineEdit_10->clear();
        break;

    // GROUPS table
    case 4:
        if (ui->groupsTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec()
                && !ui->lineEdit_9->text().isEmpty())
        {
            QString specialtyId = "";

            specialtyId = ui->comboBox->itemData(ui->comboBox->currentIndex()).toString();
            row = ui->groupsTable->selectedItems().first()->row();
            id  = ui->groupsTable->item(row, 0)->text();

            if (id == "")
            {
                query = dbo.executeQuery("SELECT MAX(groupId) FROM groups");
                query.first();
                dbo.executeQuery("INSERT INTO groups "
                                 "VALUES "
                                 "(" + QString::number(query.value(0).toInt()+1) +
                                 ",'" + ui->lineEdit_9->text() +
                                 "','" + specialtyId + "',0)");
            }
            else
            {
                dbo.executeQuery("UPDATE groups "
                                 "SET groupNumber='" + ui->lineEdit_9->text() +
                                 "', specialtyId='" + specialtyId +
                                 "' WHERE groupId=" + id);
            }
        }
        ui->lineEdit_9->clear();
        break;

    // CLASS_TYPE table
    case 5:
        if (ui->classTypeTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec()
                && !ui->lineEdit_11->text().isEmpty())
        {
            row = ui->classTypeTable->selectedItems().first()->row();
            id  = ui->classTypeTable->item(row, 0)->text();

            if (id == "")
            {
                query = dbo.executeQuery("SELECT MAX(classTypeId) FROM class_type");
                query.first();
                dbo.executeQuery("INSERT INTO class_type "
                                 "VALUES "
                                 "(" + QString::number(query.value(0).toInt()+1) + ",'" + ui->lineEdit_11->text() + "',0)");
            }
            else
            {
                dbo.executeQuery("UPDATE class_type "
                                 "SET classTypeName='" + ui->lineEdit_11->text() +
                                 "' WHERE classTypeId=" + id);
            }
        }
        ui->lineEdit_11->clear();
        break;

    // SEMESTER table
    case 6:
        if (ui->semesterTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec()
                && (!ui->lineEdit_13->text().isEmpty() || !ui->lineEdit_14->text().isEmpty()))
        {
            row = ui->semesterTable->selectedItems().first()->row();
            id  = ui->semesterTable->item(row, 0)->text();

            if (id == "")
            {
                query = dbo.executeQuery("SELECT MAX(semesterId) FROM semester");
                query.first();
                dbo.executeQuery("INSERT INTO semester "
                                 "VALUES "
                                 "(" + QString::number(query.value(0).toInt()+1) +
                                 ",'" + ui->lineEdit_13->text() +
                                 "','" + ui->lineEdit_14->text() + "',0)");
            }
            else
            {
                dbo.executeQuery("UPDATE semester "
                                 "SET semesterNumber='" + ui->lineEdit_13->text() +
                                 "',weeks='" + ui->lineEdit_14->text() +
                                 "' WHERE semesterId=" + id);
            }
        }
        ui->lineEdit_11->clear();
        break;

    // CURRICULUM table
    case 7:
        if (ui->curriculumTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec()
                && !ui->lineEdit_15->text().isEmpty())
        {
            row = ui->curriculumTable->selectedItems().first()->row();
            id  = ui->curriculumTable->item(row, 0)->text();

            QString subjectId   = ui->comboSubject->itemData(ui->comboSubject->currentIndex()).toString();
            QString specialtyId = ui->comboSpecialty->itemData(ui->comboSpecialty->currentIndex()).toString();
            QString semesterId  = ui->comboSemester->itemData(ui->comboSemester->currentIndex()).toString();
            QString classTypeId = ui->comboClassType->itemData(ui->comboClassType->currentIndex()).toString();
            QString hours       = ui->lineEdit_15->text();

            if (id.isEmpty())
            {
                dbo.executeQuery("INSERT INTO curriculum (subjectId, specialtyId, semesterId, classTypeId, hours, deleted) "
                                 "VALUES (" +
                                 subjectId      + "," +
                                 specialtyId    + "," +
                                 semesterId     + "," +
                                 classTypeId    + "," +
                                 hours + ",0)"
                                 );
            }
            else
            {
                dbo.executeQuery("UPDATE curriculum "
                                 "SET subjectId="   + subjectId +
                                 ",specialtyId="    + specialtyId +
                                 ",semesterId="     + semesterId +
                                 ",classTypeId="    + classTypeId +
                                 ",hours="          + hours +
                                 " WHERE curriculumId=" + id
                                 );
            }
            ui->lineEdit_15->clear();
        }
        break;

    // LOAD table
    case 8:
        if (ui->loadTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row = ui->loadTable->selectedItems().first()->row();
            id  = ui->loadTable->item(row, 0)->text();

            QString teacherId   = ui->comboTeacherLoad->itemData(ui->comboTeacherLoad->currentIndex()).toString();
            QString subjectId   = ui->comboSubjectLoad->itemData(ui->comboSubjectLoad->currentIndex()).toString();
            QString classTypeId = ui->comboClassTypeLoad->itemData(ui->comboClassTypeLoad->currentIndex()).toString();

            if (id.isEmpty())
            {
                dbo.executeQuery("INSERT INTO load (teacherId, subjectId, classTypeId, deleted) "
                                 "VALUES (" +
                                 teacherId      + "," +
                                 subjectId      + "," +
                                 classTypeId    + ",0)"
                                 );
            }
            else
            {
                dbo.executeQuery("UPDATE load "
                                 "SET teacherId="   + teacherId +
                                 ",subjectId="      + subjectId +
                                 ",classTypeId="    + classTypeId +
                                 " WHERE loadId="   + id
                                 );
            }
        }
        break;

    // TEACHER_LIMITS table
    case 9:
        if (ui->limitsTable->selectedItems().count() && QMessageBox::Yes == msgBox.exec())
        {
            row = ui->limitsTable->selectedItems().first()->row();
            id  = ui->limitsTable->item(row, 0)->text();

            QString teacherId   = ui->comboTeacherLimit->itemData(ui->comboTeacherLimit->currentIndex()).toString();
            QString limitId     = ui->comboLimit->itemData(ui->comboLimit->currentIndex()).toString();
            QString isLimitSet  = "0";

            if (ui->isLimitSet->isChecked())
            {
                isLimitSet = "1";
            }

            if (id.isEmpty())
            {
                dbo.executeQuery("INSERT INTO teacher_limits (teacherId, limitId, value) "
                                 "VALUES (" +
                                 teacherId      + "," +
                                 limitId        + "," +
                                 isLimitSet     + ")"
                                 );
            }
            else
            {
                dbo.executeQuery("UPDATE teacher_limits "
                                 "SET teacherId="           + teacherId +
                                 ",limitId="                + limitId +
                                 " WHERE teacherLimitId="   + id
                                 );
            }
        }
        break;
    }
    //MainWindow::on_showButton_clicked();
    MainWindow::on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}


//
//  Function fills current visible table
//
void MainWindow::on_tabWidget_currentChanged(int index)
{
    QSqlQuery query;
    int i = 0;

    switch (index)  // which tab is open?
    {
    // SPECIALTY table
    case 0:
        ui->specialtyTable->clearContents();
        ui->specialtyTable->setRowCount(0);

        query = dbo.executeQuery("SELECT specialtyId, specialtyCode, specialtyName "
                                 "FROM specialty "
                                 "WHERE deleted <> 1");

        while (query.next())
        {
            ui->specialtyTable->insertRow(i);
            ui->specialtyTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->specialtyTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // specialty code
            ui->specialtyTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // specialty name
            i++;
        }
        break;

    // SUBJECT table
    case 1:
        ui->subjectTable->clearContents();
        ui->subjectTable->setRowCount(0);

        query = dbo.executeQuery("SELECT subjectId, subjectName, shortSubjectName, subjectType "
                                 "FROM subject "
                                 "WHERE deleted <> 1");
        ui->subjectTable->setRowCount(query.size());

        while (query.next())
        {
            ui->subjectTable->insertRow(i);
            ui->subjectTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->subjectTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // subject name
            ui->subjectTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // short subject name
            ui->subjectTable->setItem(i, 3, new QTableWidgetItem(query.value(3).toString())); // subject type
            i++;
        }
        break;

    // ROOM table
    case 2:
        ui->roomTable->clearContents();
        ui->roomTable->setRowCount(0);

        query = dbo.executeQuery("SELECT roomId, roomNumber, capacity, roomType, own "
                                 "FROM room "
                                 "WHERE deleted <> 1");
        ui->roomTable->setRowCount(query.size());

        while (query.next())
        {
            ui->roomTable->insertRow(i);
            ui->roomTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->roomTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // room number
            ui->roomTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // room capacity
            ui->roomTable->setItem(i, 3, new QTableWidgetItem(query.value(3).toString())); // room type
            ui->roomTable->setItem(i, 4, new QTableWidgetItem(query.value(4).toString())); // own
            i++;
        }
        break;

    // TEACHER table
    case 3:
        ui->teacherTable->clearContents();
        ui->teacherTable->setRowCount(0);

        query = dbo.executeQuery("SELECT teacherId, teacherName, department "
                                 "FROM teacher "
                                 "WHERE deleted <> 1");
        ui->teacherTable->setRowCount(query.size());

        while (query.next())
        {
            ui->teacherTable->insertRow(i);
            ui->teacherTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->teacherTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // teacher name
            ui->teacherTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // department
            i++;
        }
        break;

    // GROUPS table
    case 4:
        ui->groupsTable->clearContents();
        ui->groupsTable->setRowCount(0);
        ui->comboBox->clear();

        query = dbo.executeQuery("SELECT groupId, groupNumber, specialtyName "
                                 "FROM groups "
                                 "JOIN specialty ON "
                                 "groups.specialtyId = specialty.specialtyId "
                                 "WHERE groups.deleted <> 1");
        ui->groupsTable->setRowCount(query.size());

        while (query.next())
        {
            ui->groupsTable->insertRow(i);
            ui->groupsTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->groupsTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // group number
            ui->groupsTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // specialty name
            i++;
        }

        query = dbo.executeQuery("SELECT specialtyId, specialtyName "
                                 "FROM specialty "
                                 "WHERE deleted <> 1");

        i = 0;
        while (query.next())
        {
            ui->comboBox->addItem(query.value(1).toString());
            ui->comboBox->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }
        break;

    // CLASS_TYPE table
    case 5:
        ui->classTypeTable->clearContents();
        ui->classTypeTable->setRowCount(0);

        query = dbo.executeQuery("SELECT classTypeId, classTypeName "
                                 "FROM class_type "
                                 "WHERE deleted <> 1");
        ui->classTypeTable->setRowCount(query.size());

        while (query.next())
        {
            ui->classTypeTable->insertRow(i);
            ui->classTypeTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->classTypeTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // class type name
            i++;
        }
        break;

    // SEMESTER table
    case 6:
        ui->semesterTable->clearContents();
        ui->semesterTable->setRowCount(0);

        query = dbo.executeQuery("SELECT semesterId, semesterNumber, weeks "
                                 "FROM semester "
                                 "WHERE deleted <> 1");
        ui->semesterTable->setRowCount(query.size());

        while (query.next())
        {
            ui->semesterTable->insertRow(i);
            ui->semesterTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->semesterTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // semester number
            ui->semesterTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // weeks
            i++;
        }
        break;

    // CURRICULUM table
    case 7:
        ui->curriculumTable->clearContents();
        ui->curriculumTable->setRowCount(0);
        ui->comboClassType->clear();
        ui->comboSemester->clear();
        ui->comboSpecialty->clear();
        ui->comboSubject->clear();

        query = dbo.executeQuery("SELECT curriculumId, subjectName, specialtyName, semesterNumber, classTypeName, hours "
                                 "FROM curriculum "
                                 "JOIN subject ON curriculum.subjectId = subject.subjectId "
                                 "JOIN specialty ON curriculum.specialtyId = specialty.specialtyId "
                                 "JOIN semester ON curriculum.semesterId = semester.semesterId "
                                 "JOIN class_type ON curriculum.classTypeId = class_type.classTypeId "
                                 "WHERE subject.deleted <> 1 "
                                    "AND specialty.deleted <> 1 "
                                    "AND semester.deleted <> 1 "
                                    "AND class_type.deleted <> 1 "
                                    "AND curriculum.deleted <> 1");
        ui->curriculumTable->setRowCount(query.size());

        while (query.next())
        {
            ui->curriculumTable->insertRow(i);
            ui->curriculumTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // curriculum id
            ui->curriculumTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // subject name
            ui->curriculumTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // specialty name
            ui->curriculumTable->setItem(i, 3, new QTableWidgetItem(query.value(3).toString())); // semester number
            ui->curriculumTable->setItem(i, 4, new QTableWidgetItem(query.value(4).toString())); // class type name
            ui->curriculumTable->setItem(i, 5, new QTableWidgetItem(query.value(5).toString())); // hours
            i++;
        }

        query = dbo.executeQuery("SELECT subjectId, subjectName "
                                 "FROM subject "
                                 "WHERE deleted <> 1 "
                                 "ORDER BY subjectName");

        i = 0;
        while (query.next())
        {
            ui->comboSubject->addItem(query.value(1).toString());
            ui->comboSubject->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        query = dbo.executeQuery("SELECT specialtyId, specialtyName "
                                 "FROM specialty "
                                 "WHERE deleted <> 1");

        i = 0;
        while (query.next())
        {
            ui->comboSpecialty->addItem(query.value(1).toString());
            ui->comboSpecialty->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        query = dbo.executeQuery("SELECT semesterId, semesterNumber "
                                 "FROM semester "
                                 "WHERE deleted <> 1");

        i = 0;
        while (query.next())
        {
            ui->comboSemester->addItem(query.value(1).toString());
            ui->comboSemester->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        query = dbo.executeQuery("SELECT classTypeId, classTypeName "
                                 "FROM class_type "
                                 "WHERE deleted <> 1");

        i = 0;
        while (query.next())
        {
            ui->comboClassType->addItem(query.value(1).toString());
            ui->comboClassType->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        break;

    // LOAD table
    case 8:
        ui->loadTable->clearContents();
        ui->loadTable->setRowCount(0);
        ui->comboClassTypeLoad->clear();
        ui->comboTeacherLoad->clear();
        ui->comboSubjectLoad->clear();

        query = dbo.executeQuery("SELECT loadId, teacherName, subjectName, classTypeName "
                                 "FROM load "
                                 "JOIN teacher ON load.teacherId = teacher.teacherId "
                                 "JOIN subject ON load.subjectId = subject.subjectId "
                                 "JOIN class_type ON load.classTypeId = class_type.classtypeId "
                                 "WHERE load.deleted <> 1 "
                                 "ORDER BY subjectName");
        ui->loadTable->setRowCount(query.size());

        while (query.next())
        {
            ui->loadTable->insertRow(i);
            ui->loadTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->loadTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // teacher name
            ui->loadTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // subject
            ui->loadTable->setItem(i, 3, new QTableWidgetItem(query.value(3).toString())); // class type
            i++;
        }

        query = dbo.executeQuery("SELECT teacherId, teacherName "
                                 "FROM teacher "
                                 "WHERE deleted <> 1 "
                                 "ORDER BY department, teacherName");

        i = 0;
        while (query.next())
        {
            ui->comboTeacherLoad->addItem(query.value(1).toString());
            ui->comboTeacherLoad->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        query = dbo.executeQuery("SELECT subjectId, subjectName "
                                 "FROM subject "
                                 "WHERE deleted <> 1 "
                                 "ORDER BY subjectName");

        i = 0;
        while (query.next())
        {
            ui->comboSubjectLoad->addItem(query.value(1).toString());
            ui->comboSubjectLoad->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        query = dbo.executeQuery("SELECT classTypeId, classTypeName "
                                 "FROM class_type "
                                 "WHERE deleted <> 1 "
                                 "ORDER BY classTypeName");

        i = 0;
        while (query.next())
        {
            ui->comboClassTypeLoad->addItem(query.value(1).toString());
            ui->comboClassTypeLoad->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        break;

    // TEACHER_LIMITS table
    case 9:
        ui->limitsTable->clearContents();
        ui->limitsTable->setRowCount(0);
        ui->comboTeacherLimit->clear();
        ui->comboLimit->clear();

        query = dbo.executeQuery("SELECT teacherLimitId, teacherName, limitName "
                                 "FROM teacher_limits "
                                 "JOIN teacher ON teacher_limits.teacherId = teacher.teacherId "
                                 "JOIN limits ON teacher_limits.limitId = limits.limitId "
                                 "WHERE teacher_limits.deleted <> 1 "
                                 "ORDER BY teacherName");
        ui->limitsTable->setRowCount(query.size());

        while (query.next())
        {
            ui->limitsTable->insertRow(i);
            ui->limitsTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->limitsTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString())); // teacher name
            ui->limitsTable->setItem(i, 2, new QTableWidgetItem(query.value(2).toString())); // limit name
            i++;
        }

        query = dbo.executeQuery("SELECT teacherId, teacherName "
                                 "FROM teacher "
                                 "WHERE deleted <> 1 "
                                 "ORDER BY department, teacherName");

        i = 0;
        while (query.next())
        {
            ui->comboTeacherLimit->addItem(query.value(1).toString());
            ui->comboTeacherLimit->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        query = dbo.executeQuery("SELECT limitId, limitName "
                                 "FROM limits "
                                 "WHERE deleted <> 1");

        i = 0;
        while (query.next())
        {
            ui->comboLimit->addItem(query.value(1).toString());
            ui->comboLimit->setItemData(i, QVariant(query.value(0).toInt()));
            i++;
        }

        break;
    }
}

//
//  Function opens a database and fills current visible table
//
void MainWindow::on_action_4_triggered()
{
    QString databaseFileName = QFileDialog::getOpenFileName(this, tr("Open database file"), ".\\", tr("Files (*.db)"));

    // connecting to DB

    dbo.connect("..\\genetic\\curriculum.db");

    //dbo.connect(databaseFileName);


    // fills opened tab
    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

//
//  Function opens SUBJECT_HOURS view
//
void MainWindow::on_action_triggered()
{
    subjectHoursView = new SubjectHoursView(0, &dbo);
    subjectHoursView->show();
}

void MainWindow::on_open_action_2_triggered()
{
    schedule_constructor* algorithmForm = new schedule_constructor();
    algorithmForm->show();
}
