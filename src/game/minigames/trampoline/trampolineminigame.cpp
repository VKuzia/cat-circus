#include "trampolineminigame.h"

#include <QMouseEvent>
#include <QRandomGenerator>

#include "src/game/gameobject.h"

TrampolineMinigame::TrampolineMinigame(GameView* game_view, qreal difficulty,
                                       qreal pixels_in_meter)
    : Minigame(game_view, difficulty, pixels_in_meter) {}

void TrampolineMinigame::Start() { AnimateTutorial(); }

void TrampolineMinigame::SetUp() {
  background_->SetUp(game_view_, "trampoline/background.png");
  game_view_->scene()->addItem(background_);

  SetUpLabel(kTutorialText_);

  cat_ = new TrampolineCat(game_view_, kCatSize_, kCatStartPos_);
  cat_->SetUp();
  game_view_->scene()->addItem(cat_);

  trampoline_ =
      new Trampoline(game_view_, kTrampolineSize_, kTrampolineStartPos_);
  trampoline_->SetUp();
  game_view_->scene()->addItem(trampoline_);

  SetUpTiles();
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

void TrampolineMinigame::SetUpTiles() {
  for (int32_t i = -swipe_count_ / 2; i <= (swipe_count_ - 1) / 2; i++) {
    TrampolineTile* tile = new TrampolineTile(
        game_view_, kTileSize_,
        kTileCentrePos_.x() + i * (kTileSize_.width() + kTileXInterval_),
        kTileCentrePos_.y());
    tile->setVisible(false);
    tiles_.push_back(tile);
    game_view_->scene()->addItem(tile);
  }
}

void TrampolineMinigame::AnimateTutorial() {
  tutorial_label_->setVisible(true);
  QTimer::singleShot(kTutorialDuration, this, &TrampolineMinigame::StartGame);
}

void TrampolineMinigame::StartGame() {
  is_running_ = true;
  tutorial_label_->setVisible(false);
  tick_timer_.setInterval(1000 / kFps);
  connect(&tick_timer_, &QTimer::timeout, this, &TrampolineMinigame::Tick);
  tick_timer_.start();
}

void TrampolineMinigame::Tick() {
  if (!cat_->IsMoving()) {
    return;
  }
  cat_->Update();
  if (!is_failed_ && cat_->GetY() < kCatFlipY_ && !cat_->IsJustFlipped()) {
    StartFlip();
  } else if (cat_->collidesWithItem(trampoline_)) {
    // Jump up if cat reached trampoline from above
    if (cat_->IsInAir()) {
      trampoline_->SetPushed(true);
      // If cat is sufficiently deep in the trampoline
      if (cat_->Bottom() > trampoline_->Top() + kTrampolineDepth_) {
        cat_->SetInAir(false);
        cat_->SetJustFlipped(false);
        // Hide tiles from previous jump
        SetTilesVisible(false);
        PrepareTiles();
        if (is_failed_) {
          QTimer::singleShot(kFailFlyAwayTime_, this,
                             [this] { Stop(MinigameStatus::kFailed); });

          cat_->SetVelocity(physics::Throw(cat_->GetPos(), kFailAimPoint_,
                                           kFailFlyAwayTime_ / 1000.0));
        } else {
          cat_->SetMood(TrampolineCat::Mood::kNormal);
          cat_->SetVelocity(0, -cat_->GetVelocity().y());
        }
      }
    }
  } else if (!cat_->IsInAir()) {
    // If cat has just jumped off
    cat_->SetInAir(true);
    trampoline_->SetPushed(false);
  }
}

void TrampolineMinigame::PrepareTiles() {
  for (auto current_tile : tiles_) {
    current_tile->SetDirection(static_cast<TrampolineTile::SwipeDirection>(
        QRandomGenerator::global()->bounded(3)));
    current_tile->SetUp();
  }
}

void TrampolineMinigame::SetTilesVisible(bool visible) {
  for (auto current_tile : tiles_) {
    current_tile->setVisible(visible);
  }
}

void TrampolineMinigame::StartFlip() {
  if (flip_count_ == 0) {
    Stop(MinigameStatus::kPassed);
    return;
  }
  SetTilesVisible(true);
  tiles_.at(0)->Activate();
  remaining_swipe_count_ = swipe_count_;
  is_making_flip_ = true;
  flip_count_--;
  cat_->SetJustFlipped(true);
  cat_->SetMoving(false);
  time_bar_->setVisible(true);
  time_bar_->Launch(flip_time_);
  is_successful_flip_ = false;
  QTimer::singleShot(flip_time_, this, [this] {
    if (is_making_flip_) {
      if (swipe_count_ - remaining_swipe_count_ < tiles_.size()) {
        tiles_.at(swipe_count_ - remaining_swipe_count_)
            ->Deactivate(TrampolineTile::Status::kIncorrectPath);
      }
      cat_->SetMood(TrampolineCat::Mood::kSad);
      FinishFlip();
    }
  });
}

void TrampolineMinigame::FinishTile() {
  remaining_swipe_count_--;
  int32_t current_tile_index = swipe_count_ - remaining_swipe_count_ - 1;
  TrampolineTile* current_tile = tiles_.at(current_tile_index);
  if (current_tile->CheckPath(current_mouse_path_->path())) {
    current_tile->Deactivate(TrampolineTile::Status::kCorrectPath);
    cat_->SetMood(TrampolineCat::Mood::kHappy);
    if (remaining_swipe_count_ == 0) {
      is_successful_flip_ = true;
      FinishFlip();
    }
    if (current_tile_index + 1 < swipe_count_) {
      tiles_.at(current_tile_index + 1)->Activate();
    }
  } else {
    current_tile->Deactivate(TrampolineTile::Status::kIncorrectPath);
    cat_->SetMood(TrampolineCat::Mood::kSad);
    FinishFlip();
  }
}

void TrampolineMinigame::FinishFlip() {
  time_bar_->setVisible(false);
  is_making_flip_ = false;
  cat_->SetMoving(true);
  if (!is_successful_flip_) {
    is_failed_ = true;
    cat_->RotateFor(kIncorrectFlipTime_);
  } else {
    cat_->RotateFor(kCorrectFlipTime_);
  }
}

void TrampolineMinigame::Stop(MinigameStatus status) {
  is_running_ = false;
  tick_timer_.stop();
  switch (status) {
    case MinigameStatus::kPassed:
      score_ = 100;
      Win();
      break;
    case MinigameStatus::kFailed:
      Lose();
  }
}

void TrampolineMinigame::MousePressEvent(QMouseEvent* event) {
  if (!is_making_flip_ || !is_running_) {
    return;
  }
  is_mouse_pressed_ = true;
  current_mouse_path_ = new TrampolinePath(game_view_);
  current_mouse_path_->setPen(kMousePathPen_);
  current_mouse_path_->MoveTo(event->pos());
  game_view_->scene()->addItem(current_mouse_path_);
}

void TrampolineMinigame::MouseReleaseEvent(QMouseEvent*) {
  if (!is_making_flip_ || !is_running_ || !is_mouse_pressed_) {
    return;
  }
  is_mouse_pressed_ = false;
  current_mouse_path_->FadeAway(kMousePathFadeAwayTime_);
  FinishTile();
}

void TrampolineMinigame::MouseMoveEvent(QMouseEvent* event) {
  if (!is_mouse_pressed_ || !is_making_flip_ || !is_running_) {
    return;
  }
  current_mouse_path_->LineTo(event->pos());
}
