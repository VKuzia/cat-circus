#include "trampolineminigame.h"

#include <QMouseEvent>
#include <QRandomGenerator>

TrampolineMinigame::TrampolineMinigame(GameView* graphics_view,
                                       qreal difficulty)
    : Minigame(graphics_view, difficulty) {
  graphics_view->SetPixelsInMeter(kPixelsInMeter);
}

void TrampolineMinigame::Start() { AnimateTutorial(); }

void TrampolineMinigame::SetUp() {
  SetParameters();
  time_bar_->setVisible(false);

  cat_ = new TrampolineCat(graphics_view_, kCatWidth, kCatHeight, kCatStartPos);
  cat_->SetUp();
  graphics_view_->scene()->addItem(cat_);

  trampoline_ = new Trampoline(graphics_view_, kTrampolineWidth,
                               kTrampolineHeight, kTrampolineStartPos);
  trampoline_->SetUp();
  graphics_view_->scene()->addItem(trampoline_);

  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &TrampolineMinigame::Tick);

  SetTiles();

  is_running_ = true;
  SetLabel();
}

void TrampolineMinigame::SetLabel() {
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::black);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(100);
  tutorial_label_->setPos(0, 0);
  tutorial_label_->setVisible(false);
}

void TrampolineMinigame::SetParameters() {
  flip_count_ = 3;
  flip_time_ = 2000;
  swipe_count_ = 1;
}

void TrampolineMinigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, this, &TrampolineMinigame::StartGame);
}

void TrampolineMinigame::StartGame() {
  tutorial_label_->setVisible(false);
  tick_timer_.start();
}

void TrampolineMinigame::AnimateOutro() {}

void TrampolineMinigame::Tick() {
  if (!cat_->IsMoving()) {
    return;
  }
  cat_->Update();
  if (!is_lost_ && cat_->GetY() < kCatFlipHeight && !cat_->IsJustFlipped()) {
    MakeFlip();
  } else if (cat_->collidesWithItem(trampoline_)) {
    if (cat_->IsFlying()) {
      cat_->SetFlying(false);
      cat_->SetJustFlipped(false);
      SetTilesVisible(false);
      PrepareTiles();
      if (is_lost_) {
        cat_->SetVelocity(kWrongVelocity);
      } else {
        cat_->SetVelocity(0, -cat_->GetVelocity().y());
      }
    }
  } else if (!cat_->IsFlying()) {
    cat_->SetFlying(true);
  }
}

void TrampolineMinigame::MakeFlip() {
  if (flip_count_ == 0) {
    Stop(Status::kPass);
    return;
  }
  SetTilesVisible(true);
  current_swipe_count_ = swipe_count_;
  is_making_flip_ = true;
  flip_count_--;
  cat_->SetJustFlipped(true);
  cat_->SetMoving(false);
  time_bar_->setVisible(true);
  time_bar_->Launch(flip_time_);
  is_successful_flip_ = false;
  QTimer::singleShot(flip_time_, this, [this] {
    if (is_making_flip_) {
      FinishFlip();
    }
  });
}

void TrampolineMinigame::PrepareTiles() {
  int32_t direction_num = QRandomGenerator::global()->bounded(3);
  switch (direction_num) {
    case 0:
      current_tile_->SetDirection(TrampolineTile::SwipeDirection::kUp);
      current_tile_->SetPixmap(
          kUp.scaled(qRound(current_tile_->boundingRect().width()),
                     qRound(current_tile_->boundingRect().height())));
      break;
    case 1:
      current_tile_->SetDirection(TrampolineTile::SwipeDirection::kDown);
      current_tile_->SetPixmap(
          kDown.scaled(qRound(current_tile_->boundingRect().width()),
                       qRound(current_tile_->boundingRect().height())));
      break;
    case 2:
      current_tile_->SetDirection(TrampolineTile::SwipeDirection::kLeft);
      current_tile_->SetPixmap(
          kLeft.scaled(qRound(current_tile_->boundingRect().width()),
                       qRound(current_tile_->boundingRect().height())));
      break;
    case 3:
      current_tile_->SetDirection(TrampolineTile::SwipeDirection::kRight);
      current_tile_->SetPixmap(
          kRight.scaled(qRound(current_tile_->boundingRect().width()),
                        qRound(current_tile_->boundingRect().height())));
      break;
  }
  current_tile_->SetUp();
}

void TrampolineMinigame::SetTiles() {
  current_tile_ =
      new TrampolineTile(graphics_view_, kTileWidth, kTileHeight, kTileX, 0);
  current_tile_->setVisible(false);
  graphics_view_->scene()->addItem(current_tile_);
}

void TrampolineMinigame::SetTilesVisible(bool visible) {
  if (current_tile_ != nullptr) {
    current_tile_->setVisible(visible);
  }
}

void TrampolineMinigame::FinishTile() {
  current_swipe_count_--;
  if (!current_tile_->CheckPath(*current_mouse_path_, first_mouse_pressed_,
                                last_mouse_pressed_)) {
    FinishFlip();
  } else if (current_swipe_count_ == 0) {
    is_successful_flip_ = true;
    FinishFlip();
  }
}

void TrampolineMinigame::FinishFlip() {
  time_bar_->setVisible(false);
  is_making_flip_ = false;
  cat_->SetMoving(true);
  if (!is_successful_flip_) {
    is_lost_ = true;
    QTimer::singleShot(kFlyAwayTime, this, [this] { Stop(Status::kFail); });
    cat_->RotateFor(kIncorrectFlipTime);
  } else {
    cat_->RotateFor(kCorrectFlipTime);
  }
  //  current_tile_->setVisible(false);
}

void TrampolineMinigame::Stop(Status status) {
  is_running_ = false;
  tick_timer_.stop();
  if (status == Status::kPass) {
    score_ = 100;
    Win();
  }
  if (status == Status::kFail) {
    Lose();
  }
}

void TrampolineMinigame::Win() {
  graphics_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Passed(score_);
  });
}

void TrampolineMinigame::Lose() {
  graphics_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    graphics_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Failed();
  });
}
void TrampolineMinigame::MousePressEvent(QMouseEvent* event) {
  if (!is_making_flip_) {
    return;
  }
  is_mouse_pressed_ = true;
  first_mouse_pressed_ = event->pos();
  last_mouse_pressed_ = first_mouse_pressed_;
  current_mouse_path_ = new PathObject(graphics_view_);
  current_mouse_path_->setPen(kMousePathPen);
  current_mouse_path_->MoveTo(first_mouse_pressed_);
  graphics_view_->scene()->addItem(current_mouse_path_);
}

void TrampolineMinigame::MouseReleaseEvent(QMouseEvent*) {
  is_mouse_pressed_ = false;
  if (!is_making_flip_) {
    return;
  }
  current_mouse_path_->FadeAway(kMousePathFadeAwayTime);
  FinishTile();
}

void TrampolineMinigame::MouseMoveEvent(QMouseEvent* event) {
  if (!is_mouse_pressed_ || !is_making_flip_) {
    return;
  }
  last_mouse_pressed_ = event->pos();
  current_mouse_path_->LineTo(last_mouse_pressed_);
}
