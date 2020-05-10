#ifndef UNICYCLECAT_H
#define UNICYCLECAT_H

#include <QMovie>

#include "src/game/gameobject.h"

class UnicycleCat : public GameObject {
 public:
  UnicycleCat(GameView* game_view, QSizeF size, QPointF pos);
  ~UnicycleCat() override = default;

  void SetUp() override;

  void Update() override;

  void StartAnimation();
  void StopAnimation();

 private:
  const QVector<int32_t> kMovieSpeeds_ = {0, 20, 40, 60, 80, 100, 120, 150};
  const qreal kMovieSpeedUnit_ = 0.07;

  Vector2D speed_loss_ = {0.02, 0};
  QMovie movie_;
};

#endif  // UNICYCLECAT_H
