#ifndef PIXMAPLOADER_H
#define PIXMAPLOADER_H

#include <QDir>
#include <QHash>
#include <QPixmap>

class PixmapLoader {
 public:
  PixmapLoader() = default;
  ~PixmapLoader() = default;

  QPixmap GetPixmap(const QString& short_path, QSize size,
                    bool mask = false) const;

  void PreloadPixmaps() const;

 private:
  const QString kPathToImages_ =
      QDir::currentPath() + "/data/images/minigames/";

  mutable QHash<QString, QPixmap> pixmaps_;
};

#endif  // PIXMAPLOADER_H
