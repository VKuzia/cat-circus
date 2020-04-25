#ifndef TRAMPOLINECAT_H
#define TRAMPOLINECAT_H

#include "src/game/gameobject.h"

class TrampolineCat : public GameObject {
 public:
  TrampolineCat(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
                qreal y = 0);
  TrampolineCat(GameView* graphics_view, qreal width, qreal height,
                QPointF pos);
  ~TrampolineCat() override = default;

  void SetUp() override;
  void Update() override;

  void SetMoving(bool moving);

  void SetFlying(bool flying);
  bool GetFlying() const;

 private:
  bool is_moving_ = true;
  bool is_flying_ = true;
};

#endif  // TRAMPOLINECAT_H
