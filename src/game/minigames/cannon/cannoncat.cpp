#include "cannoncat.h"

#include "sausage.h"

const qreal Cannoncat::kZValue_ = 2;

Cannoncat::Cannoncat(GameView *game_view, qreal width, qreal height, qreal x,
                     qreal y, qreal floor_y)
    : GameObject(game_view, width, height, x, y),
      radius_(width / 2),
      floor_y_(floor_y) {}

void Cannoncat::SetUp() {
  this->setZValue(kZValue_);
  this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
  QPixmap pixmap =
      QPixmap(game_view_->GetPathToMinigameImages() + "juggling/cat.png");
  pixmap.setMask(pixmap.createHeuristicMask());
  this->setPixmap(pixmap.scaled(boundingRect().size().toSize()));
}

void Cannoncat::Update() {
  was_caught_last_tick_ = false;
  if (start_vil_.x() == 0 && start_vil_.y() == 0) {
    start_vil_.setX(cos(angle_) * power_);
    start_vil_.setY(-sin(angle_) * power_);
  }
  if (in_flight_) {
    AddVelocity(start_vil_.x(), start_vil_.y());
    start_vil_ += physics::kGravity / 6000;
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
        if (dynamic_cast<Sausage *>(item)) {
          item->setVisible(false);
          was_caught_last_tick_ = true;
          caught_sausages_++;
        }
      }
    }
  }
}

qreal Cannoncat::GetRadius() const { return radius_; }

void Cannoncat::SetAngle(qreal angle) { angle_ = angle; }

void Cannoncat::SetPower(qreal power) { power_ = power; }

void Cannoncat::SetFallen(bool is_fallen) { is_fallen_ = is_fallen; }

int Cannoncat::GetCaught() const { return caught_sausages_; }
