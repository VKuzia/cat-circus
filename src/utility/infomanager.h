#ifndef INFOMANAGER_H
#define INFOMANAGER_H
#include <QString>

class InfoManager {
 public:
  InfoManager();

  bool LoadInfo(const QString& path);        // loads basic game data from file
  bool SaveInfo(const QString& path) const;  // saves basic game data to file

  int32_t GetWindowWidth() const;
  int32_t GetWindowHeight() const;

 private:
  QString load_path_;      // last loading path (to save something there)
  int32_t window_width_;   // width of main window in pixels
  int32_t window_height_;  // height of main window in pixels
  QString players_name_;  // curent players name; may be used to save comptetive
                          // results further
  int64_t
      best_score_;  // best score achieved by current player to track records
};

#endif  // INFOMANAGER_H
