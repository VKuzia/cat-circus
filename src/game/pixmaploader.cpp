#include "pixmaploader.h"

#include <QBitmap>

QPixmap PixmapLoader::GetPixmap(const QString& short_path, QSize size) {
  auto pixmaps_iterator = pixmaps_.find(short_path);
  if (pixmaps_iterator != pixmaps_.end()) {
    return pixmaps_iterator.value();
  }
  QPixmap new_pixmap = QPixmap(kPathToImages_ + short_path).scaled(size);
  new_pixmap.setMask(new_pixmap.createHeuristicMask());
  pixmaps_.insert(short_path, new_pixmap);
  return new_pixmap;
}

void PixmapLoader::ClearPixmaps() { pixmaps_.clear(); }
