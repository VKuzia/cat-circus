#ifndef PIXMAPLOADER_H
#define PIXMAPLOADER_H

#include <QDir>
#include <QHash>
#include <QPixmap>

class PixmapLoader {
 public:
  PixmapLoader() = default;
  ~PixmapLoader() = default;

  QPixmap GetPixmap(const QString& short_path, QSize size);

  void ClearPixmaps();

 private:
  const QString kPathToImages_ =
      QDir::currentPath() + "/data/images/minigames/";

  QHash<QString, QPixmap> pixmaps_;
};

#endif  // PIXMAPLOADER_H
