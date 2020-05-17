#ifndef TRAMPOLINEPATH_H
#define TRAMPOLINEPATH_H

#include <QGraphicsPathItem>
#include <QObject>
#include <QPainterPath>
#include <QPropertyAnimation>

#include "src/game/gameview.h"

class TrampolinePath : public QObject, public QGraphicsPathItem {
  Q_OBJECT
  Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

 public:
  explicit TrampolinePath(GameView* game_view);
  ~TrampolinePath() override = default;

  void MoveTo(QPointF point);
  void LineTo(QPointF point);

  void FadeAway(int32_t millis);

 signals:
  void FadedAway();

 private:
  GameView* game_view_;
  QPainterPath path_;
  QPropertyAnimation opacity_animation_;
};

#endif  // TRAMPOLINEPATH_H
