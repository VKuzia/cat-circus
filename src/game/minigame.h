#ifndef MINIGAME_H
#define MINIGAME_H

#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>

#include "src/game/backgroundobject.h"
#include "src/game/timebar.h"

class GameView;

class Minigame : public QObject {
  Q_OBJECT

 public:
  Minigame(GameView* game_view, qreal difficulty, qreal pixels_in_meter);
  virtual ~Minigame();

  void Init();

  virtual void Start() = 0;

  virtual void MousePressEvent(QMouseEvent* event);
  virtual void MouseReleaseEvent(QMouseEvent* event);
  virtual void MouseMoveEvent(QMouseEvent* event);
  virtual void KeyPressEvent(QKeyEvent* event);
  virtual void KeyReleaseEvent(QKeyEvent* event);

  int32_t GetScore() const;

 protected:
  enum class Status { kFail, kPass };

  const qreal kTimeBarHeightFactor = 0.08;
  const int32_t kFps = 60;
  const int32_t kTutorialDuration = 2500;
  const int32_t kOutroDuration = 2000;

  GameView* game_view_;
  QTimer timer_;       // For minigame progress
  QTimer tick_timer_;  // For 1 frame updates

  int32_t time_ = 0;
  int32_t score_ = 0;
  qreal width_;
  qreal height_;

  TimeBar* time_bar_ = nullptr;
  QGraphicsTextItem* tutorial_label_;
  BackgroundObject* background_;

  qreal difficulty_;
  qreal pixels_in_meter_;

  bool is_running_ = false;

  // Sets up a certain Minigame child
  // Adds start GameObjects to scene
  virtual void SetUp() = 0;
  virtual void SetUpLabel() = 0;
  virtual void SetUpParameters() = 0;

  virtual void AnimateTutorial() = 0;
  virtual void StartGame() = 0;

  virtual void Tick() = 0;

  virtual void Stop(Status) = 0;
  virtual void Win();
  virtual void Lose();
};

#endif  // MINIGAME_H
