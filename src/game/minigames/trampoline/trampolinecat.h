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
  bool IsMoving() const;

  void SetFlying(bool flying);
  bool IsFlying() const;

  void SetJustFlipped(bool flipped);
  bool IsJustFlipped() const;

 private:
  bool is_moving_ = true;
  bool is_flying_ = true;
  bool is_just_flipped_ = true;
};

#endif  // TRAMPOLINECAT_H
