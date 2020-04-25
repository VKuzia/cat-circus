#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QGraphicsItemAnimation>
#include <QObject>
#include <QTimeLine>

#include "src/game/gameobject.h"

class TimeBar : public GameObject {
  Q_OBJECT

 public:
  TimeBar(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
          qreal y = 0);
  TimeBar(GameView* graphics_view, qreal width, qreal height, QPointF pos);
  ~TimeBar() override = default;

  void SetUp() override;

  QRectF boundingRect() const override;

  void Launch(int32_t millis);
  void SetProgress(qreal progress);

 private:
  static const qreal kDefaultHeightFactor;

  const QColor kBasicColor = QColor::fromRgb(81, 204, 24);
  qreal progress_ = 1;

  QTimeLine timeline_;
  QGraphicsItemAnimation animation_;
};

#endif  // TIMEBAR_H
