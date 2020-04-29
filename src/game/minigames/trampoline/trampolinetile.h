#ifndef TRAMPOLINETILE_H
#define TRAMPOLINETILE_H

#include "src/game/game_objects/pathobject.h"
#include "src/game/gameobject.h"

class TrampolineTile : public GameObject {
 public:
  enum class SwipeDirection { kUp, kDown, kLeft, kRight };

  TrampolineTile(GameView* graphics_view, qreal width, qreal height,
                 qreal x = 0, qreal y = 0);
  TrampolineTile(GameView* graphics_view, qreal width, qreal height,
                 QPointF pos);
  ~TrampolineTile() override = default;

  void SetPixmap(const QPixmap& pixmap);

  void Activate();

  bool CheckPath(const PathObject& path_item_, const QPointF& start,
                 const QPointF& finish);

  void SetDirection(SwipeDirection direction);

 private:
  const qreal kNoFocusOpacity = 0.8;
  const qreal kMinimalSwipeLength = 3;
  const qreal kMinimalPathRectRatio = 6;

  const QColor kFailColor = QColor::fromRgb(200, 0, 0);
  const QColor kPassColor = QColor::fromRgb(0, 200, 0);

  SwipeDirection direction_ = SwipeDirection::kUp;

  void Deactivate(bool is_path_correct);
};

#endif  // TRAMPOLINETILE_H
