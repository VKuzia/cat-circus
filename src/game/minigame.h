#ifndef MINIGAME_H
#define MINIGAME_H

#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QObject>
#include <QTimer>

#include "src/game/game_objects/timebar.h"

class Minigame : public QObject {
  Q_OBJECT

 public:
  Minigame(QGraphicsView* graphics_view, float difficulty);
  virtual ~Minigame();

  virtual void SetUp() = 0;

  virtual void Start() = 0;
  virtual void Stop() = 0;

  virtual void MousePressEvent(QMouseEvent* event) = 0;
  virtual void MouseReleaseEvent(QMouseEvent* event) = 0;
  virtual void MouseMoveEvent(QMouseEvent* event) = 0;
  virtual void KeyPressEvent(QKeyEvent* event) = 0;
  virtual void KeyReleaseEvent(QKeyEvent* event) = 0;

 signals:
  void Passed(int64_t score);
  void Failed();

 protected:
  const float kTimeBarHeightFactor = 0.08f;
  const int32_t kFps = 60;
  const int32_t kTutorialDuration = 2500;
  const int32_t kOutroDuration = 2000;

  QGraphicsView* graphics_view_;
  QTimer timer_;       // For minigame progress
  QTimer tick_timer_;  // For 1 frame updates

  int32_t time_ = 0;
  int32_t points_ = 0;
  int32_t width_;
  int32_t height_;

  TimeBar* time_bar_;
  QGraphicsTextItem* tutorial_label_;

  float difficulty_;

  bool is_running_ = false;

  // Sets time_bar_ and tutorial_label_
  // Should be called in every SetUp implementation
  void SetUpBasicItems();

  virtual void AnimateTutorial() = 0;
  virtual void StartGame() = 0;
  virtual void AnimateOutro() = 0;

  virtual void Tick() = 0;

  virtual void Win() = 0;
  virtual void Lose() = 0;
};

#endif  // MINIGAME_H
