#include "schedule_constructor.h"
#include "ui_schedule_constructor.h"

schedule_constructor::schedule_constructor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::schedule_constructor)
{
    ui->setupUi(this);
}

schedule_constructor::~schedule_constructor()
{
    delete ui;
}
