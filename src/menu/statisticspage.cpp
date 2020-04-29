#include "statisticspage.h"
#include "ui_statisticspage.h"

StatisticsPage::StatisticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);
}

StatisticsPage::~StatisticsPage()
{
    delete ui;
}
