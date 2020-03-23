#ifndef OBJECT_H
#define OBJECT_H
#include <QGraphicsItem>
#include <QPoint>

class Object {
 public:
  Object();
  virtual ~Object();

 private:
  int32_t x_;
  int32_t y_;
  bool is_movable_;
  QPoint velocity_;  // vector of current velocity
  double mass_;
  QGraphicsItem* gitem_;  // sprite
};

#endif  // OBJECT_H
