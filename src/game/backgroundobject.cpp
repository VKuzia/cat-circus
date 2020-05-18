#include "backgroundobject.h"

#include <QDir>
#include <limits>

#include "src/game/gameobject.h"

void BackgroundObject::SetUp(GameView* game_view, const QString& short_path) {
  setZValue(std::numeric_limits<qreal>::lowest());
  int32_t width = game_view->width();
  int32_t height = game_view->height();
  setOffset(-width / 2, -height / 2);
  setPos(0, 0);
  setPixmap(GameObject::GetPixmapLoader()->GetPixmap(
      short_path, QSizeF(width, height).toSize()));
}
