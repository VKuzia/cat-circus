#ifndef BUTTON_H
#define BUTTON_H

#include <QPropertyAnimation>
#include <QPushButton>

class Button : public QPushButton {
  Q_OBJECT
  Q_PROPERTY(qreal animationProgress READ GetAnimationProgress WRITE
                 SetAnimationProgress)

 public:
  explicit Button(QWidget* parent = nullptr);
  ~Button() override = default;

 private:
  const int32_t kMouseHoverAnimationDuration_ = 150;
  const qreal kMouseHoverScaleFactor_ = 1.15;

  QPropertyAnimation hover_animation_;
  QSize last_size_;
  qreal animation_progress_ = 0;

  void enterEvent(QEvent*) override;
  void leaveEvent(QEvent*) override;

  void SetAnimationProgress(qreal progress);
  qreal GetAnimationProgress() const;
};

#endif  // BUTTON_H
