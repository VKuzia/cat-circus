#ifndef CANNONCAT_H
#define CANNONCAT_H

#include "src/game/gameobject.h"

class CannonCat : public GameObject {
  Q_OBJECT

 public:
  CannonCat(GameView* game_view, qreal width, qreal height, qreal x = 0,
            qreal y = 0, qreal floor_y_ = 0);
  ~CannonCat() override = default;

  void SetUp() override;

  void Update() override;

  qreal GetRadius() const;
  void SetAngle(qreal);
  void SetPower(qreal);

 private:
  void CatchSausage();
  const Vector2D kGravityCannon = physics::kGravity / 6000;
  qreal radius_;
  qreal floor_y_;
  qreal angle_ = 0;
  qreal power_ = 0;
  Vector2D cat_velocity_ = {0, 0};
  bool is_in_flight_ = true;
};

#endif  // CANNONCAT_H
