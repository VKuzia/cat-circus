#include "backgroundobject.h"

#include <QDir>
#include <limits>

void BackgroundObject::SetUp(GameView* game_view,
                             const QString& path_to_image) {
  setZValue(std::numeric_limits<qreal>::lowest());
  setOffset(-game_view->width() / 2, -game_view->height() / 2);
  setPos(0, 0);
  setPixmap(
      QPixmap(QDir::currentPath() + "/data/images/minigames/" + path_to_image)
          .scaled(game_view->width(), game_view->height()));
}
