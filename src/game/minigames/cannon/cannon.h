#ifndef CANNON_H
#define CANNON_H

#include <QSet>

#include "src/game/gameobject.h"
#include "src/game/minigames/cannon/cannoncat.h"

class Cannon : public GameObject {
 public:
  Cannon(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
         qreal y = 0);
  ~Cannon() override = default;

  void SetUp() override;

  void Update() override;
  void Throw();

  void SetAimPoint(const QPointF& point);

  void AddCat(Cannoncat*);
  QPointF GetBasePos() const;

  void SetBallAirTime(qreal sec);

 private:
  // Hand motion durations
  const qreal kThrowTime = 0.15;
  const qreal kComeBackTime = 0.05;

  // Horizontal distance hand passes throwing
  const qreal kThrowXRange = 0.4;

  // Set's parabolic motion of a hand while throwing
  // Here should be random
  const Vector2D kAcceleration = {0, -18};
  const QPointF base_pos_;
  const QPointF throw_pos_;

  Cannoncat* cat_;
  QPixmap pixmap_free_;
  QPixmap pixmap_closed_;
  bool is_throwing_ = false;
  bool is_just_thrown_ = false;
  bool angle_choosen = false;
  bool power_choosen = false;
  QPointF aim_point_;
  qreal ball_air_time_ = 0;

  // Used to direct thrown balls
  Vector2D GetThrowVelocity() const;
};

#endif  // CANNON_H
