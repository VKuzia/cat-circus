#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QObject>
#include <QPropertyAnimation>

#include "src/game/gameobject.h"

class TimeBar : public GameObject {
  Q_OBJECT
  Q_PROPERTY(qreal progress READ GetProgress WRITE SetProgress)

 public:
  TimeBar(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
          qreal y = 0);
  TimeBar(GameView* graphics_view, qreal width, qreal height, QPointF pos);
  ~TimeBar() override = default;

  void SetUp() override;

  QRectF boundingRect() const override;

  void Launch(int32_t millis);

 private:
  const QColor kBasicColor = QColor::fromRgb(81, 204, 24);
  qreal progress_ = 1;
  QPropertyAnimation progress_animation_;

  void SetProgress(qreal progress);
  qreal GetProgress() const;
};

#endif  // TIMEBAR_H
