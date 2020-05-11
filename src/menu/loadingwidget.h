#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QGraphicsOpacityEffect>
#include <QMovie>
#include <QPropertyAnimation>
#include <QWidget>

namespace Ui {
class LoadingWidget;
}

class LoadingWidget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(int opacity READ GetOpacity WRITE SetOpacity)

 public:
  explicit LoadingWidget(QWidget* parent = nullptr);
  ~LoadingWidget();

  void SetUp();
  void Animate();

 signals:
  void AnimationFinished();
  void BecameOpaque();

 private:
  const QColor kBackgroundColor = QColor::fromRgb(163, 44, 31);
  const int32_t kAnimationFadeDuration = 600;
  const int32_t kAnimationStayDuration = 1000;

  QMovie loading_movie_;

  QPropertyAnimation animation_;
  Ui::LoadingWidget* ui_;
  // Effect is handled by qt, no need to delete it in destructor
  QGraphicsOpacityEffect* effect_ = nullptr;
  int32_t opacity_ = 0;
  bool is_opaque_ = false;

  void SetOpacity(int opacity);
  int GetOpacity() const;
};

#endif  // LOADINGWIDGET_H
