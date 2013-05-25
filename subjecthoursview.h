#ifndef SUBJECTHOURSVIEW_H
#define SUBJECTHOURSVIEW_H

#include <QWidget>
#include "dboperations.h"

namespace Ui {
class SubjectHoursView;
}

class SubjectHoursView : public QWidget
{
    Q_OBJECT
    
public:
    explicit SubjectHoursView(QWidget *parent = 0, DbOperations *dbo = 0);
    ~SubjectHoursView();
    
private:
    Ui::SubjectHoursView *ui;
};

#endif // SUBJECTHOURSVIEW_H
