#include "infomanager.h"

#include <QFile>
#include <QTextStream>

bool InfoManager::LoadInfo(const QString &path) {
  load_path_ = path;
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    return false;
  }
  // bad but easy
  QTextStream input(&file);
  QString temp;
  temp = input.readLine();
  window_width_ = temp.toInt();
  temp = input.readLine();
  window_height_ = temp.toInt();
  players_name_ = input.readLine();
  temp = input.readLine();
  best_score_ = temp.toInt();
  file.close();
  return true;
}

bool InfoManager::SaveInfo(const QString &) const { return true; }

int32_t InfoManager::GetWindowWidth() const { return window_width_; }

int32_t InfoManager::GetWindowHeight() const { return window_height_; }
