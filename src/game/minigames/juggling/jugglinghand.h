#ifndef JUGGLINGHAND_H
#define JUGGLINGHAND_H

#include <QSet>

#include "src/game/gameobject.h"
#include "src/game/minigames/juggling/jugglingball.h"

class JugglingHand : public GameObject {
 public:
  JugglingHand(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
               qreal y = 0, bool left = true);
  ~JugglingHand() override = default;

  void SetUp() override;

  void Update() override;
  void Throw();

  void SetAimPoint(const QPointF& point);

  void AddBall(JugglingBall*);
  QPointF GetBasePos() const;

  void SetBallAirTime(qreal sec);

 private:
  // Hand motion durations
  const qreal kThrowTime = 0.15;
  const qreal kComeBackTime = 0.05;

  // Horizontal distance hand passes throwing
  const qreal kThrowXRange = 0.4;

  // Set's parabolic motion of a hand while throwing
  const Vector2D kAcceleration = {0, -18};
  const bool is_left_;
  const QPointF base_pos_;
  const QPointF throw_pos_;

  QSet<JugglingBall*> balls_;
  QPixmap pixmap_free_;
  QPixmap pixmap_closed_;
  bool is_throwing_ = false;
  bool is_just_thrown_ = false;
  QPointF aim_point_;
  qreal ball_air_time_ = 0;

  // Used to direct thrown balls
  Vector2D GetThrowVelocity() const;
};

#endif  // JUGGLINGHAND_H
