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

void PixmapLoader::PreloadPixmaps() const {
  QStringList minigame_folders = QDir(kPathToImages_).entryList(QDir::Dirs);
  for (auto folder_name : minigame_folders) {
    QDir minigame_dir(kPathToImages_ + "/" + folder_name);
    QStringList file_names =
        minigame_dir.entryList(QStringList() << "*.png", QDir::Files);
    for (auto file_name : file_names) {
      QPixmap pixmap(kPathToImages_ + "/" + folder_name + "/" + file_name);
      pixmap.setMask(pixmap.createHeuristicMask());
      pixmaps_.insert(folder_name + "/" + file_name, pixmap);
    }
  }
}
