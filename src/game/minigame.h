#ifndef MINIGAME_H
#define MINIGAME_H

#include <QGraphicsView>
#include <QObject>
#include <QTimer>

#include "src/game/game_objects/timebar.h"

class MiniGame : public QObject {
  Q_OBJECT

 public:
  MiniGame(QGraphicsView* graphics_view, qreal difficulty);
  virtual ~MiniGame();

  virtual void Start() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;
  virtual void Stop() = 0;

  virtual void MousePressEvent(QMouseEvent* event) = 0;
  virtual void MouseReleaseEvent(QMouseEvent* event) = 0;
  virtual void MouseMoveEvent(QMouseEvent* event) = 0;
  virtual void KeyPressEvent(QKeyEvent* event) = 0;
  virtual void KeyReleaseEvent(QKeyEvent* event) = 0;

 signals:
  void Passed(int64_t score);
  void Failed();

 public slots:

 protected:
  const qreal kTimeBarHeightFactor = 0.05;

  QGraphicsView* graphics_view_;
  QTimer* finish_timer_;

  int32_t width_;
  int32_t height_;
  TimeBar* time_bar_;
  qreal difficulty_;

  bool is_running_ = false;

  virtual void Win() = 0;
  virtual void Lose() = 0;
};

#endif  // MINIGAME_H
