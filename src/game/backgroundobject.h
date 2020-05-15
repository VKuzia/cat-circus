#ifndef BACKGROUNDOBJECT_H
#define BACKGROUNDOBJECT_H
#include <QGraphicsPixmapItem>

#include "src/game/gameview.h"

class BackgroundObject : public QGraphicsPixmapItem {
 public:
  BackgroundObject() = default;
  ~BackgroundObject() = default;

  void SetUp(GameView* game_view, const QString& short_path);
};

#endif  // BACKGROUNDOBJECT_H
