#ifndef JUGGLINGBALL_H
#define JUGGLINGBALL_H

#include "src/game/gameobject.h"

class JugglingBall : public GameObject {
 public:
  JugglingBall(GameView* game_view, qreal width, qreal height, qreal x = 0,
               qreal y = 0, qreal floor_y = 0);
  ~JugglingBall() override = default;

  void SetUp() override;

  void Update() override;

  void SetCaught(bool is_caught);
  qreal GetRadius() const;

  void SetFallen(bool is_fallen);
  bool IsFallen() const;

 private:
  static const qreal kZValue;

  qreal radius_;
  qreal floor_y_;
  bool is_caught_ = false;
  bool is_fallen_ = false;
};

#endif  // JUGGLINGBALL_H
