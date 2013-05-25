#include "subjecthoursview.h"
#include "ui_subjecthoursview.h"

SubjectHoursView::SubjectHoursView(QWidget *parent, DbOperations *dbo) :
    QWidget(parent),
    ui(new Ui::SubjectHoursView)
{
    ui->setupUi(this);

    ui->subjectHoursTable->setColumnCount(2);
    ui->subjectHoursTable->setColumnWidth(0, 405);
    ui->subjectHoursTable->setColumnWidth(1, 50);

    QStringList viewHorHeaders;
    viewHorHeaders.push_back("Subject");
    viewHorHeaders.push_back("Hours");

    ui->subjectHoursTable->setHorizontalHeaderLabels(viewHorHeaders);
    ui->subjectHoursTable->clearContents();
    ui->subjectHoursTable->setRowCount(0);

    QSqlQuery query = dbo->executeQuery("SELECT * "
                                        "FROM subject_hours");

    int i = 0;
    while (query.next())
    {
        ui->subjectHoursTable->insertRow(i);
        ui->subjectHoursTable->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->subjectHoursTable->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
        i++;
    }
}

SubjectHoursView::~SubjectHoursView()
{
    delete ui;
}
