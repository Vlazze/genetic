#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDialog>
#include "dboperations.h"
#include "subjecthoursview.h"
#include "schedule_constructor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    DbOperations dbo;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_showButton_clicked();

    void on_deleteButton_clicked();

    void on_addButton_clicked();

    void on_specialtyTable_cellClicked(int row);

    void on_subjectTable_cellClicked(int row);

    void on_roomTable_cellClicked(int row);

    void on_teacherTable_cellClicked(int row);

    void on_groupsTable_cellClicked(int row);

    void on_classTypeTable_cellClicked(int row);

    void on_saveButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_semesterTable_cellClicked(int row);

    void on_curriculumTable_cellClicked(int row);


    //void on_open_action_triggered();
    void on_action_4_triggered();

    void on_action_triggered();


    void on_open_action_2_triggered();

private:
    Ui::MainWindow *ui;
    SubjectHoursView *subjectHoursView;
    schedule_constructor* m_algorithmForm;
};

#endif // MAINWINDOW_H
