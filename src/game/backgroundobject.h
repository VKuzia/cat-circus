#ifndef BACKGROUNDOBJECT_H
#define BACKGROUNDOBJECT_H
#include <QGraphicsPixmapItem>

#include "src/game/gameview.h"

class BackgroundObject : public QGraphicsPixmapItem {
 public:
  BackgroundObject() = default;
  void SetUp(GameView* game_view, const QString& path_to_image);
  ~BackgroundObject() = default;
};

#endif  // BACKGROUNDOBJECT_H
