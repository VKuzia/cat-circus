#include "cannoncat.h"

#include "cannonsausage.h"

CannonCat::CannonCat(GameView *game_view, qreal width, qreal height, qreal x,
                     qreal y, qreal floor_y)
    : GameObject(game_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

void CannonCat::SetUp() {
  this->setOffset(boundingRect().topLeft());
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "juggling/cat.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
}

void CannonCat::Update() {
  was_caught_last_tick_ = false;
  if (start_vil_.x() == 0 && start_vil_.y() == 0) {
    start_vil_.setX(cos(angle_) * power_);
    start_vil_.setY(-sin(angle_) * power_);
  }
  if (in_flight_) {
    AddVelocity(start_vil_.x(), start_vil_.y());
    start_vil_ += kGravityCannon;
    qreal x_difference = (velocity_.x()) * kUpdateTime;
    qreal y_difference = (velocity_.y()) * kUpdateTime;
    this->MoveByMeters(x_difference, y_difference);
    setRotation(rotation() + atan(x_difference / y_difference));
    // Check if Sausage is caught
    const QList<QGraphicsItem *> sausages =
        scene()->items(QPolygonF() << mapToScene(0, 0) << mapToScene(-30, -30)
                                   << mapToScene(30, -30));

    for (QGraphicsItem *item : sausages) {
      if (item == this) {
        continue;
      } else {
        if (dynamic_cast<CannonSausage *>(item)) {
          item->setVisible(false);
          was_caught_last_tick_ = true;
          caught_sausages_++;
        }
      }
    }
  }
}

qreal CannonCat::GetRadius() const { return radius_; }

void CannonCat::SetAngle(qreal angle) { angle_ = angle; }

void CannonCat::SetPower(qreal power) { power_ = power; }

void CannonCat::SetFallen(bool is_fallen) { is_fallen_ = is_fallen; }

int CannonCat::GetCaught() const { return caught_sausages_; }

bool CannonCat::GetLastTickStatus() const { return was_caught_last_tick_; }
