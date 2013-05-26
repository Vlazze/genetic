#include "schedule_constructor.h"
#include "ui_schedule_constructor.h"
#include "algorithm/galgorithm.h"
#include <QtCore>
#include <QtWidgets>

schedule_constructor::schedule_constructor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::schedule_constructor)
{
    ui->setupUi(this);

    m_algorithm = NULL;
    m_currentPopulationToShowIndex = 0;
    ui->pushButtonPreviousGenome->setEnabled(false);
    ui->pushButtonNextGenome->setEnabled(false);
    ui->spinBoxPopulationNavigation->setEnabled(false);
    ui->pushButton_2->setEnabled(false);

    //make empty table
    // set table TEACHER_LIMITS appearance
    ui->scheduleTable->setColumnCount(12);
    ui->scheduleTable->setRowCount(60);

    QStringList limitsHorHeaders;
    limitsHorHeaders.push_back("I-11");
    limitsHorHeaders.push_back("I-12");
    limitsHorHeaders.push_back("I-13");

    limitsHorHeaders.push_back("I-21");
    limitsHorHeaders.push_back("I-22");
    limitsHorHeaders.push_back("I-23");

    limitsHorHeaders.push_back("I-31");
    limitsHorHeaders.push_back("I-32");
    limitsHorHeaders.push_back("I-33");

    limitsHorHeaders.push_back("I-41");
    limitsHorHeaders.push_back("I-42");
    limitsHorHeaders.push_back("I-43");

    QStringList limitVerHeaders;
    QString dayName;
    int cnt = 1;
    for (int i = 1; i <= 60; i++){
        if(cnt > 5) {
            cnt = 1;
        }
        if(i <= 5) dayName = "Monday ";
        else if (i > 5 && i <=10) dayName = "Tuessday ";
        else if (i > 10 && i <=15) dayName = "Wednesday ";
        else if (i > 15 && i <=20) dayName = "Thursday ";
        else if (i > 20 && i <=25) dayName = "Friday ";
        else if (i > 25 && i <=30) dayName = "Saturday ";

        else if (i > 30 && i <=35) dayName = "Monday ";
        else if (i > 35 && i <=40) dayName = "Tuessday ";
        else if (i > 40 && i <=45) dayName = "Wednesday ";
        else if (i > 45 && i <=50) dayName = "Thursday ";
        else if (i > 50 && i <=55) dayName = "Friday ";
        else if (i > 55 && i <=60) dayName = "Saturday ";
        limitVerHeaders.push_back(dayName + QString::number(cnt));

        cnt++;
    }

    ui->scheduleTable->setHorizontalHeaderLabels(limitsHorHeaders);
    ui->scheduleTable->setVerticalHeaderLabels(limitVerHeaders);
    //table complete

}

schedule_constructor::~schedule_constructor()
{
    delete m_algorithm;
    delete ui;
}

void schedule_constructor::setScheduleValue(QVector<QVector<lesson *> > schedule){

    ui->scheduleTable->clearContents();

    //QVector< QVector<lesson*> > schedule;
    schedule = m_algorithm->generateGenome();

    for (int i = 0; i < schedule.count(); i++){
        QVector<lesson*> currentGroup = schedule[i];
        for (int j = 0; j < currentGroup.count(); j++){
            QString roomId = QString::number(currentGroup[j]->getRoom()->getID());
            QString subjId = QString::number(currentGroup[j]->getSubject()->getID());
            QString teachId = QString::number(currentGroup[j]->getTeacher()->getID());
            QString resultString = "Room - " + roomId + "|Subj - " + subjId + "|Teach - " + teachId;

            //old content
            QModelIndex index = ui->scheduleTable->model()->index(j, currentGroup[j]->getTimeIndex());
            QString oldString = index.data().toString();

            int timeCurrentTimeIndex = currentGroup[j]->getTimeIndex();

            ui->scheduleTable->setItem(j, timeCurrentTimeIndex,
                                       new QTableWidgetItem(oldString + "#" +resultString));//

        }
    }
}

//setPools on click
void schedule_constructor::on_pushButton_clicked()
{

    if(m_algorithm){
        delete m_algorithm;
    }

    m_algorithm = new GAlgorithm();
    if(ui->radioRandomly->isChecked()){
        m_algorithm->setPoolsWithRandomValues(ui->spinBoxSubjCount->value(),
                                              ui->spinBoxTeachCount->value(),
                                              ui->spinBoxRoomCount->value(),
                                              12); //HARDCODE!!!!
    } else if (ui->radioFromDB->isChecked()){
        //algorithm->setPools();
        return;
    }

    //spin box "Population Count" value check
    if(ui->spinBoxPopulationCount->value()){
        m_algorithm->generatePopulation(ui->spinBoxPopulationCount->value());
        setScheduleValue(m_algorithm->getPopulationAtIndex(m_currentPopulationToShowIndex));
        //if more than 1 genome - show scroll button
        if(m_algorithm->getPopulationCount() > 1){
            ui->pushButtonNextGenome->setEnabled(true);
            ui->spinBoxPopulationNavigation->setEnabled(true);
            ui->spinBoxPopulationNavigation->setMaximum(ui->spinBoxPopulationCount->value());
            ui->pushButton_2->setEnabled(true);
        }
    } else {
        QMessageBox msg;
        msg.setText("Population count must be greater than 0");
        msg.exec();
    }
}

void schedule_constructor::on_schedule_constructor_destroyed()
{

}

void schedule_constructor::on_radioRandomly_toggled(bool checked)
{
        ui->spinBoxRoomCount->setEnabled(checked);
        ui->spinBoxSubjCount->setEnabled(checked);
        ui->spinBoxTeachCount->setEnabled(checked);
}

void schedule_constructor::on_pushButtonPreviousGenome_clicked()
{
    m_currentPopulationToShowIndex--;
    setScheduleValue(m_algorithm->getPopulationAtIndex(m_currentPopulationToShowIndex));
    if(m_currentPopulationToShowIndex == 0){
        ui->pushButtonPreviousGenome->setEnabled(false);
    }
    ui->pushButtonNextGenome->setEnabled(true);
    ui->spinBoxPopulationNavigation->setValue(m_currentPopulationToShowIndex+1);
}

void schedule_constructor::on_pushButtonNextGenome_clicked()
{
    m_currentPopulationToShowIndex++;
    setScheduleValue(m_algorithm->getPopulationAtIndex(m_currentPopulationToShowIndex));
    if(m_currentPopulationToShowIndex == m_algorithm->getPopulationCount() - 1){
        ui->pushButtonNextGenome->setEnabled(false);
    }
    ui->pushButtonPreviousGenome->setEnabled(true);
    ui->spinBoxPopulationNavigation->setValue(m_currentPopulationToShowIndex+1);
}

void schedule_constructor::on_spinBoxPopulationNavigation_valueChanged(int arg1)
{
    //nothing
}

void schedule_constructor::on_pushButton_2_clicked()
{
        m_currentPopulationToShowIndex = ui->spinBoxPopulationNavigation->value() - 1;
        setScheduleValue(m_algorithm->getPopulationAtIndex(m_currentPopulationToShowIndex));
        if(m_currentPopulationToShowIndex == 0){
            ui->pushButtonPreviousGenome->setEnabled(false);
        } else {
            ui->pushButtonPreviousGenome->setEnabled(true);
        }
        if(m_currentPopulationToShowIndex == m_algorithm->getPopulationCount() - 1){
            ui->pushButtonNextGenome->setEnabled(false);
        } else {
            ui->pushButtonNextGenome->setEnabled(true);
        }
}
