#ifndef TRAMPOLINECAT_H
#define TRAMPOLINECAT_H

#include <QPropertyAnimation>

#include "src/game/gameobject.h"

class TrampolineCat : public GameObject {
  Q_OBJECT
  Q_PROPERTY(qreal rotation READ rotation WRITE SetRotation)

 public:
  TrampolineCat(GameView* game_view, QSizeF size, QPointF pos);
  ~TrampolineCat() override;

  void SetUp() override;

  void Update() override;

  void RotateFor(int32_t millis);

  void SetMoving(bool moving);
  bool IsMoving() const;

  void SetFlying(bool flying);
  bool IsFlying() const;

  void SetJustFlipped(bool flipped);
  bool IsJustFlipped() const;

 private:
  QPropertyAnimation rotation_animation_;
  bool is_moving_ = true;
  bool is_flying_ = true;
  bool is_just_flipped_ = true;

  void SetRotation(qreal rotation);
};

#endif  // TRAMPOLINECAT_H
