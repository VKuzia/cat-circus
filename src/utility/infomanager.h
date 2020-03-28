#ifndef INFOMANAGER_H
#define INFOMANAGER_H

#include <QString>

class InfoManager {
 public:
  InfoManager() = default;

  bool LoadInfo(const QString& path);        // Loads basic game data from file
  bool SaveInfo(const QString& path) const;  // Saves basic game data to file

  int32_t GetWindowWidth() const;
  int32_t GetWindowHeight() const;

 private:
  QString load_path_;  // Last loading path (for further saving)
  int32_t window_width_;
  int32_t window_height_;
  QString players_name_;
  int64_t best_score_;
};

#endif  // INFOMANAGER_H
