#ifndef POINTSPAGE_H
#define POINTSPAGE_H

#include <QTimer>
#include <QWidget>

namespace Ui {
class PointsPage;
}

class PointsPage : public QWidget {
  Q_OBJECT

 public:
  explicit PointsPage(QWidget* parent = nullptr);

  void Animate();

  void MiniGamePassed(int64_t score);
  void MiniGameFailed();

 signals:
  void Expired();

 public slots:

 private:
  int32_t kExpireTime = 2000;

  Ui::PointsPage* ui;
  QTimer* expire_timer_;
};

#endif  // POINTSPAGE_H
