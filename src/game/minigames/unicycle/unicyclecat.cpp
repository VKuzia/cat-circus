#include "unicyclecat.h"

UnicycleCat::UnicycleCat(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos),
      movie_(game_view->GetPathToMinigameImages() + "unicycle/unicycle.gif") {}

void UnicycleCat::SetUp() {
  setOffset(-boundingRect().center());
  movie_.setScaledSize(boundingRect().size().toSize() / 2);
  movie_.jumpToFrame(0);
  setPixmap(movie_.currentPixmap());
  connect(&movie_, &QMovie::frameChanged, this,
          [this] { setPixmap(movie_.currentPixmap()); });
  SetVelocity(0, 0);
}

void UnicycleCat::Update() {
  MoveByMeters(velocity_ * kUpdateTime);
  if (velocity_.x() >= speed_loss_.x()) {
    velocity_ -= speed_loss_;
  } else {
    velocity_ = {0, 0};
  }
  movie_.setSpeed(kMovieSpeeds_[qMin(
      kMovieSpeeds_.size() - 1, qFloor(velocity_.x() / kMovieSpeedUnit_))]);
}

void UnicycleCat::StartAnimation() { movie_.start(); }

void UnicycleCat::StopAnimation() { movie_.stop(); }
