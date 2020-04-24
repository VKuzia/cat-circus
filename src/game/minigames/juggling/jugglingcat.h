#ifndef JUGGLINGCAT_H
#define JUGGLINGCAT_H

#include <QGraphicsEllipseItem>

#include "src/game/gameobject.h"
#include "src/game/minigames/juggling/jugglinghand.h"

class JugglingCat : public GameObject {
 public:
  JugglingCat(GameView* graphics_view, qreal width, qreal height, qreal x = 0,
              qreal y = 0);
  ~JugglingCat() override;
  void SetUp();

  void Update() override;

  JugglingHand* GetLeftHand();
  JugglingHand* GetRightHand();

 private:
  const qreal kHandRadius = 0.25;

  JugglingHand* left_hand_;
  JugglingHand* right_hand_;

  void SetUpHands();
};

#endif  // JUGGLINGCAT_H
