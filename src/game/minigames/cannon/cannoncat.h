#ifndef CANNONCAT_H
#define CANNONCAT_H

#include "src/game/gameobject.h"

class Cannoncat : public GameObject {
 public:
  Cannoncat(GameView* game_view, qreal width, qreal height, qreal x = 0,
            qreal y = 0, qreal floor_y_ = 0);
  ~Cannoncat() override = default;

  void SetUp() override;

  void Update() override;

  void SetCaught(bool is_caught);
  qreal GetRadius() const;
  void SetAngle(qreal);
  void SetPower(qreal);
  void SetFallen(bool is_fallen);
  int GetCaught() const;
  bool was_caught_last_tick_ = false;

 private:
  static const qreal kZValue_;

  qreal radius_;
  qreal floor_y_;
  qreal angle_ = 0;
  qreal power_ = 0;
  Vector2D start_vil_ = {0, 0};
  bool is_caught_ = false;
  bool is_fallen_ = false;
  bool in_flight_ = true;
  int caught_sausages_ = 0;
};

#endif  // CANNONCAT_H
