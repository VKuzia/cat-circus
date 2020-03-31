#include "pointspage.h"

#include "ui_pointspage.h"

PointsPage::PointsPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PointsPage) {
  ui->setupUi(this);
}
