#include "pixmaploader.h"

#include <QBitmap>

QPixmap PixmapLoader::GetPixmap(const QString& short_path, QSize size) const {
  if (pixmaps_.contains(short_path)) {
    return pixmaps_[short_path].scaled(size);
  }
  QPixmap new_pixmap = QPixmap(kPathToImages_ + short_path);
  new_pixmap.setMask(new_pixmap.createHeuristicMask());
  pixmaps_.insert(short_path, new_pixmap);
  return new_pixmap.scaled(size);
}
