#include "backgroundobject.h"

#include <QDir>

void BackgroundObject::SetUp(GameView* graphics_view,
                             const QString& path_to_image) {
  setOffset(-graphics_view->width() / 2, -graphics_view->height() / 2);
  setPos(0, 0);
  setPixmap(
      QPixmap(QDir::currentPath() + "/data/images/minigames/" + path_to_image)
          .scaled(graphics_view->width(), graphics_view->height()));
  graphics_view->scene()->addItem(this);
}
