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
    ui->spinBoxFitnessValue->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButtonFitnessSort->setEnabled(false);
    ui->pushButtonGoAlgorithm->setEnabled(false);
    ui->spinBoxIterationCount->setEnabled(false);

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
        if(i <= 5) dayName = QObject::trUtf8("Понедельник ");
        else if (i > 5 && i <=10) dayName = QObject::trUtf8("Вторник ");
        else if (i > 10 && i <=15) dayName = QObject::trUtf8("Среда ");
        else if (i > 15 && i <=20) dayName = QObject::trUtf8("Четврег ");
        else if (i > 20 && i <=25) dayName = QObject::trUtf8("Пятница ");
        else if (i > 25 && i <=30) dayName = QObject::trUtf8("Суббота ");

        else if (i > 30 && i <=35) dayName = QObject::trUtf8("Понедельник ");
        else if (i > 35 && i <=40) dayName = QObject::trUtf8("Вторник ");
        else if (i > 40 && i <=45) dayName = QObject::trUtf8("Среда ");
        else if (i > 45 && i <=50) dayName = QObject::trUtf8("Четврег ");
        else if (i > 50 && i <=55) dayName = QObject::trUtf8("Пятница ");
        else if (i > 55 && i <=60) dayName = QObject::trUtf8("Суббота ");
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
    //schedule = m_algorithm->generateGenome();

    for (int i = 0; i < schedule.count(); i++){
        QVector<lesson*> currentGroup = schedule[i];
        for (int j = 0; j < currentGroup.count(); j++){
            QString roomId = QString::number(currentGroup[j]->getRoom()->getID());
            QString subjId = currentGroup[j]->getSubject()->getTitle();
            QString teachId = currentGroup[j]->getTeacher()->getName();
            QString groupId = QString::number(currentGroup[j]->getGroup()->getID());
            QString timeStr = QString::number(currentGroup[j]->getTimeIndex());
            QString resultString = "Room - " + roomId + "|Subj - " +
                    subjId + "|Teach - " + teachId + "|Group: " + groupId +
                    "|Time: " + timeStr;

            int timeCurrentTimeIndex = currentGroup[j]->getTimeIndex();

            //old content
//            QModelIndex index = ui->scheduleTable->model()->index(j, currentGroup[j]->getTimeIndex());
            QModelIndex index = ui->scheduleTable->model()->index(timeCurrentTimeIndex, i);

            QString oldString = index.data().toString();

            QTableWidgetItem *item = new QTableWidgetItem(oldString + "#" +resultString);

            if(oldString != ""){
                QColor col(255,0,0);

                item->setBackgroundColor(col);
            }



            ui->scheduleTable->setItem(timeCurrentTimeIndex, i, item);//

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
        m_currentPopulationToShowIndex = 0;
        setScheduleValue(m_algorithm->getPopulationAtIndex(m_currentPopulationToShowIndex));

        //if more than 1 genome - show scroll button
        ui->spinBoxPopulationNavigation->setValue(1);
        ui->spinBoxPopulationNavigation->setMaximum(ui->spinBoxPopulationCount->value());
        ui->pushButtonPreviousGenome->setEnabled(false);
        ui->pushButtonFitnessSort->setEnabled(true);
        ui->pushButtonGoAlgorithm->setEnabled(true);
        ui->spinBoxIterationCount->setEnabled(true);
        if(m_algorithm->getPopulationCount() > 1){
            ui->pushButtonNextGenome->setEnabled(true);
            ui->spinBoxPopulationNavigation->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
        } else {
            ui->pushButtonNextGenome->setEnabled(false);
            ui->spinBoxPopulationNavigation->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
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

//count fitness function for current genome
void schedule_constructor::on_pushButton_3_clicked()
{
    unsigned long result = m_algorithm->fitnessFunction(
                m_algorithm->getPopulationAtIndex(m_currentPopulationToShowIndex));

    ui->spinBoxFitnessValue->setValue(result);
}

void schedule_constructor::on_tabWidget_currentChanged(int index)
{
    switch(index){
        case 0:
        break;

        case 1:
        {
            if(m_algorithm != NULL){
                if(m_algorithm->getPopulationCount()){
                    ui->spinBoxFitnessValue->setEnabled(true);
                    ui->pushButton_3->setEnabled(true);
                } else {
                    ui->spinBoxFitnessValue->setEnabled(false);
                    ui->pushButton_3->setEnabled(false);
                }
            } else {
                ui->spinBoxFitnessValue->setEnabled(false);
                ui->pushButton_3->setEnabled(false);
            }
        }
        break;
    }


}
//woot?
void schedule_constructor::on_pushButton_4_clicked()
{

}

void schedule_constructor::on_pushButtonGoAlgorithm_clicked()
{
    if(m_algorithm->getPopulationCount() > 1){
        m_algorithm->runAlgorithm(ui->spinBoxIterationCount->value());
        m_currentPopulationToShowIndex = 0;
        setScheduleValue(m_algorithm->getPopulationAtIndex(m_currentPopulationToShowIndex));
        ui->spinBoxPopulationNavigation->setValue(m_currentPopulationToShowIndex + 1);
        ui->pushButtonPreviousGenome->setEnabled(false);
        ui->pushButtonNextGenome->setEnabled(true);
    }
}

void schedule_constructor::on_pushButtonFitnessSort_clicked()
{
    m_algorithm->fitnessSortPopulation();
    m_currentPopulationToShowIndex = 0;
    setScheduleValue(m_algorithm->getPopulationAtIndex(m_currentPopulationToShowIndex));
}
