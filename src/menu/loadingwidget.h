#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QDir>
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
  const QString kBackgroundStyleSheet = "background-color: rgba(163, 44, 31);";
  const int32_t kAnimationInOutDuration = 600;
  const int32_t kAnimationStayDuration = 1000;

  QMovie* loading_movie_ =
      new QMovie(QDir::currentPath() + "/data/images/loading/loading.gif");

  Ui::LoadingWidget* ui_;
  QPropertyAnimation animation_;
  int32_t opacity_ = 0;
  bool is_opaque_ = false;

  void SetOpacity(int opacity);
  int GetOpacity() const;
};

#endif  // LOADINGWIDGET_H
