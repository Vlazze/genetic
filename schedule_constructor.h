#ifndef SCHEDULE_CONSTRUCTOR_H
#define SCHEDULE_CONSTRUCTOR_H

#include <QWidget>

namespace Ui {
class schedule_constructor;
}

class schedule_constructor : public QWidget
{
    Q_OBJECT
    
public:
    explicit schedule_constructor(QWidget *parent = 0);
    ~schedule_constructor();
    
private:
    Ui::schedule_constructor *ui;
};

#endif // SCHEDULE_CONSTRUCTOR_H
