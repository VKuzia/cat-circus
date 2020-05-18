#ifndef SAUSAGE_H
#define SAUSAGE_H

#include "src/game/gameobject.h"

class CannonSausage : public GameObject {
  Q_OBJECT
 public:
  CannonSausage(GameView* game_view, qreal width, qreal height, qreal x = 0,
                qreal y = 0);
  ~CannonSausage() override = default;

  void SetUp() override;
  void Update() override;
  void WasCaught();
  bool IsMovingDown() const;
  void SetMovingDown(bool);

 signals:
  void CaughtSausage();

 private:
  bool is_moving_down_ = true;
  qreal delta_pos_ = 0;
  qreal one_step_ = 0.01;
  bool is_caught_ = false;
};

#endif  // SAUSAGE_H
