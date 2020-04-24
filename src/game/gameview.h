#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

class Minigame;

class GameView : public QGraphicsView {
  Q_OBJECT

 public:
  explicit GameView(QWidget* parent = nullptr);
  ~GameView() override = default;

  void SetUp(int32_t width, int32_t height);

  void SetMinigame(Minigame* current_minigame);

  void SetPixelsInMeter(qreal pixels_in_meter);
  qreal GetPixelsInMeter() const;

 private:
  Minigame* current_minigame_ = nullptr;
  qreal pixels_in_meter_ = 0;

  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
};

#endif  // GAMEVIEW_H
