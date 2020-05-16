#ifndef CANNONSTATUS_H
#define CANNONSTATUS_H

#include "src/game/gameobject.h"

class CannonStatus : public GameObject {
 public:
  CannonStatus(GameView* game_view, qreal width, qreal height, qreal x = 0,
               qreal y = 0);
  ~CannonStatus() override = default;

  void SetUp() override;
  void ChangeStatus();

 private:
  QPixmap success_pixmap_;
};

#endif  // CANNONSTATUS_H
