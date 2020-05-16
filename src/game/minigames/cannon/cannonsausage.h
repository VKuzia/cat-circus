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
  bool GetMoveDown() const;
  void SetMoveDown(bool);

 signals:
  void CaughtSausage();

 private:
  bool move_down_ = true;
  qreal delta_pos = 0;
  bool is_caught_ = false;
};

#endif  // SAUSAGE_H
