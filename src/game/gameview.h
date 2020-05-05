#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QDir>
#include <QGraphicsView>

class Minigame;

class GameView : public QGraphicsView {
  Q_OBJECT

 public:
  enum class Key { kAny, kUp, kDown, kLeft, kRight };

  explicit GameView(QWidget* parent = nullptr);
  ~GameView() override = default;

  void SetUp(int32_t width, int32_t height);

  void SetMinigame(Minigame* current_minigame);

  void SetPixelsInMeter(qreal pixels_in_meter);
  qreal GetPixelsInMeter() const;

  QString GetPathToMinigameImages() const;

  uint32_t GetKey(Key key) const;

 private:
  const uint32_t kKeyLeft_ = 0x41;
  const uint32_t kKeyRight_ = 0x44;
  const uint32_t kKeyDown_ = 0x53;
  const uint32_t kKeyUp_ = 0x57;
  const uint32_t kKeyAny_ = 0;

  const QString kPathToMinigameImages_ =
      QDir::currentPath() + "/data/images/minigames/";
  Minigame* current_minigame_ = nullptr;
  qreal pixels_in_meter_ = 0;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
};

#endif  // GAMEVIEW_H
