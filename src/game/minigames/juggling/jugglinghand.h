#ifndef JUGGLINGHAND_H
#define JUGGLINGHAND_H

#include <QSet>

#include "src/game/gameobject.h"
#include "src/game/minigames/juggling/jugglingball.h"

class JugglingHand : public GameObject {
 public:
  enum class Side { kLeft, kRight };

  JugglingHand(GameView* game_view, qreal width, qreal height, qreal x, qreal y,
               Side side);
  ~JugglingHand() override = default;

  void SetUp() override;

  void Update() override;

  void Throw();

  void SetAimPoint(const QPointF& point);

  // Set current ball to be thrown
  void SetBall(JugglingBall*);

  QPointF GetBasePos() const;

  void SetBallAirTime(qreal sec);

  bool IsThrowing() const;

 private:
  // Hand motion durations
  const qreal kThrowTime = 0.15;
  const qreal kComeBackTime = 0.05;

  // Horizontal distance hand passes throwing
  const qreal kSwingXRange = 0.4;

  // Sets parabolic motion of a hand while throwing
  const Vector2D kAcceleration = {0, -18};
  const Side kSide_;
  const QPointF kBasePos_;
  const QPointF kThrowPos_;

  JugglingBall* current_ball_ = nullptr;
  QPixmap pixmap_free_;
  QPixmap pixmap_closed_;
  bool is_throwing_ = false;
  bool is_coming_back_ = false;
  QPointF aim_point_;
  qreal ball_air_time_ = 0;

  // Used to direct thrown balls
  Vector2D GetThrowVelocity() const;
  qreal GetHorizontalSwing() const;
};

#endif  // JUGGLINGHAND_H
