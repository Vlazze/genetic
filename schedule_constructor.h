#ifndef SCHEDULE_CONSTRUCTOR_H
#define SCHEDULE_CONSTRUCTOR_H

#include <QWidget>
#include <QtCore>
#include "algorithm/galgorithm.h"

namespace Ui {
class schedule_constructor;
}

class schedule_constructor : public QWidget
{
    Q_OBJECT
    
public:
    explicit schedule_constructor(QWidget *parent = 0);
    ~schedule_constructor();

    void setScheduleValue(QVector< QVector <lesson*> > schedule);
    
private slots:
    void on_pushButton_clicked();

    void on_schedule_constructor_destroyed();

    void on_radioRandomly_toggled(bool checked);

    void on_pushButtonPreviousGenome_clicked();

    void on_pushButtonNextGenome_clicked();

    void on_spinBoxPopulationNavigation_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::schedule_constructor *ui;
    GAlgorithm *m_algorithm;

    int m_currentPopulationToShowIndex;
};

#endif // SCHEDULE_CONSTRUCTOR_H
