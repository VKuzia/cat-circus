#include "object.h"

Object::Object()
    : x_(0),
      y_(0),
      is_movable_(true),
      velocity_(0, 0),
      mass_(0),
      gitem_(nullptr) {}

Object::~Object() {}
