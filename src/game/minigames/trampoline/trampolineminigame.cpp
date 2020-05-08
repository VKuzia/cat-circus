#include "trampolineminigame.h"

#include <QMouseEvent>
#include <QRandomGenerator>

TrampolineMinigame::TrampolineMinigame(GameView* game_view, qreal difficulty,
                                       qreal pixels_in_meter)
    : Minigame(game_view, difficulty, pixels_in_meter) {}

void TrampolineMinigame::Start() { AnimateTutorial(); }

void TrampolineMinigame::SetUp() {
  SetUpParameters();
  time_bar_->setVisible(false);

  cat_ = new TrampolineCat(game_view_, kCatWidth, kCatHeight, kCatStartPos);
  cat_->SetUp();
  game_view_->scene()->addItem(cat_);

  trampoline_ = new Trampoline(game_view_, kTrampolineWidth, kTrampolineHeight,
                               kTrampolineStartPos);
  trampoline_->SetUp();
  game_view_->scene()->addItem(trampoline_);

  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &TrampolineMinigame::Tick);

  SetUpTiles();
  SetUpLabel();
}

void TrampolineMinigame::SetUpLabel() {
  tutorial_label_->setHtml("[TUTORIAL]");
  tutorial_label_->setDefaultTextColor(Qt::black);
  tutorial_label_->setTextWidth(300);
  tutorial_label_->setZValue(100);
  tutorial_label_->setPos(0, 0);
  tutorial_label_->setVisible(false);
}

void TrampolineMinigame::SetUpParameters() {
  int32_t difficulty_level_ = qRound(difficulty_ / (0.1));
  switch (difficulty_level_) {
    case 1:
      flip_time_ = 2000;
      flip_count_ = 2;
      swipe_count_ = 2;
      break;
    case 2:
      flip_time_ = 2000;
      flip_count_ = 2;
      swipe_count_ = 3;
      break;
    case 3:
      flip_time_ = 2000;
      flip_count_ = 3;
      swipe_count_ = 3;
      break;
    case 4:
      flip_time_ = 1500;
      flip_count_ = 3;
      swipe_count_ = 3;
      break;
    case 5:
      flip_time_ = 2000;
      flip_count_ = 3;
      swipe_count_ = 4;
      break;
    default:
      flip_time_ = 2200;
      flip_count_ = 3;
      swipe_count_ = 5;
      break;
  }
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
  if (!is_failed_ && cat_->GetY() < kCatFlipHeight && !cat_->IsJustFlipped()) {
    MakeFlip();
  } else if (cat_->collidesWithItem(trampoline_)) {
    // Jump up if cat reached trampoline
    if (cat_->IsFlying()) {
      cat_->SetFlying(false);
      trampoline_->SetPushed(true);
      cat_->SetJustFlipped(false);
      // Hide tiles from previous jump
      SetTilesVisible(false);
      PrepareTiles();
      if (is_failed_) {
        cat_->SetVelocity(kWrongVelocity);
      } else {
        cat_->SetVelocity(0, -cat_->GetVelocity().y());
      }
    }
  } else if (!cat_->IsFlying()) {
    cat_->SetFlying(true);
    trampoline_->SetPushed(false);
  }
}

void TrampolineMinigame::MakeFlip() {
  if (flip_count_ == 0) {
    Stop(Status::kPass);
    return;
  }
  SetTilesVisible(true);
  tiles_.at(0)->Activate();
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
  for (auto current_tile : tiles_) {
    int32_t direction_num = QRandomGenerator::global()->bounded(3);
    switch (direction_num) {
      case 0:
        current_tile->SetDirection(TrampolineTile::SwipeDirection::kUp);
        current_tile->SetPixmap(kUpPixmap);
        break;
      case 1:
        current_tile->SetDirection(TrampolineTile::SwipeDirection::kDown);
        current_tile->SetPixmap(kDownPixmap);
        break;
      case 2:
        current_tile->SetDirection(TrampolineTile::SwipeDirection::kLeft);
        current_tile->SetPixmap(kLeftPixmap);
        break;
      case 3:
        current_tile->SetDirection(TrampolineTile::SwipeDirection::kRight);
        current_tile->SetPixmap(kRightPixmap);
        break;
    }
    current_tile->SetUp();
  }
}

void TrampolineMinigame::SetUpTiles() {
  for (int32_t i = -swipe_count_ / 2; i <= (swipe_count_ - 1) / 2; i++) {
    TrampolineTile* tile =
        new TrampolineTile(game_view_, kTileWidth, kTileHeight,
                           kTileX + i * (kTileWidth + kTileXInterval), kTileY);
    tile->setVisible(false);
    tiles_.push_back(tile);
    game_view_->scene()->addItem(tile);
  }
}

void TrampolineMinigame::SetTilesVisible(bool visible) {
  for (auto current_tile : tiles_) {
    current_tile->setVisible(visible);
  }
}

void TrampolineMinigame::FinishTile() {
  current_swipe_count_--;
  int32_t current_tile_index = swipe_count_ - current_swipe_count_ - 1;
  TrampolineTile* current_tile = tiles_.at(current_tile_index);
  // If the path is acceptable
  if (!current_tile->CheckPath(*current_mouse_path_, first_mouse_pressed_,
                               last_mouse_pressed_)) {
    current_tile->Deactivate(false);
    FinishFlip();
  } else {
    current_tile->Deactivate(true);
    if (current_swipe_count_ == 0) {
      is_successful_flip_ = true;
      FinishFlip();
    }
    if (current_tile_index + 1 < swipe_count_) {
      tiles_.at(current_tile_index + 1)->Activate();
    }
  }
}

void TrampolineMinigame::FinishFlip() {
  time_bar_->setVisible(false);
  is_making_flip_ = false;
  cat_->SetMoving(true);
  if (!is_successful_flip_) {
    is_failed_ = true;
    QTimer::singleShot(kFlyAwayTime, this, [this] { Stop(Status::kFail); });
    cat_->RotateFor(kIncorrectFlipTime);
  } else {
    cat_->RotateFor(kCorrectFlipTime);
  }
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
  game_view_->scene()->setBackgroundBrush(kWinBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
    emit Passed(score_);
  });
}

void TrampolineMinigame::Lose() {
  game_view_->scene()->setBackgroundBrush(kLoseBackgroundBrush);
  QTimer::singleShot(kOutroDuration, this, [this] {
    game_view_->scene()->setBackgroundBrush(kEmptyBackgroundBrush);
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
  current_mouse_path_ = new TrampolinePath(game_view_);
  current_mouse_path_->setPen(kMousePathPen);
  current_mouse_path_->MoveTo(first_mouse_pressed_);
  game_view_->scene()->addItem(current_mouse_path_);
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
