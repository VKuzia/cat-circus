#ifndef JUGGLINGHAND_H
#define JUGGLINGHAND_H

#include <QSet>
#include <QVector2D>

#include "src/game/gameobject.h"
#include "src/game/minigames/juggling/jugglingball.h"

class JugglingHand : public GameObject {
 public:
  JugglingHand(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
               qreal y = 0, bool left = true);
  ~JugglingHand() override;
  void SetUp() override;

  void Update() override;
  void Throw();

  void SetAimPoint(const QPointF& point);

  void AddBall(JugglingBall*);
  QPointF GetBasePos() const;

 private:
  const QPointF base_pos_;
  const bool is_left_;

  QSet<JugglingBall*> balls_;
  QPixmap* pixmap_free_ = nullptr;
  QPixmap* pixmap_closed_ = nullptr;
  QPointF aim_point_;

  Vector2D GetThrowVelocity() const;
};

#endif  // JUGGLINGHAND_H
