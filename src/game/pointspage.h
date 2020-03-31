#ifndef POINTSPAGE_H
#define POINTSPAGE_H

#include <QWidget>

namespace Ui {
class PointsPage;
}

class PointsPage : public QWidget {
  Q_OBJECT

 public:
  explicit PointsPage(QWidget* parent = nullptr);

 signals:

 public slots:

 private:
  Ui::PointsPage* ui;
};

#endif  // POINTSPAGE_H
