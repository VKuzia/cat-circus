#ifndef PATHOBJECT_H
#define PATHOBJECT_H

#include <QGraphicsPathItem>
#include <QObject>
#include <QPainterPath>
#include <QPropertyAnimation>

#include "src/game/gameview.h"

class PathObject : public QObject, public QGraphicsPathItem {
  Q_OBJECT
  Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

 public:
  PathObject(GameView* graphics_view);
  ~PathObject() override = default;

  void MoveTo(const QPointF point);
  void LineTo(const QPointF& point);
  void FadeAway(int32_t millis);

 signals:
  void FadedAway();

 private:
  GameView* graphics_view_;
  QPainterPath path_;
  QPropertyAnimation animation_;
};

#endif  // PATHOBJECT_H
