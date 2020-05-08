#ifndef TRAMPOLINETILE_H
#define TRAMPOLINETILE_H

#include "src/game/gameobject.h"
#include "src/game/minigames/trampoline/trampolinepath.h"

class TrampolineTile : public GameObject {
 public:
  enum class SwipeDirection { kUp, kDown, kLeft, kRight };

  TrampolineTile(GameView* game_view, qreal width, qreal height,
                 qreal x = 0, qreal y = 0);
  TrampolineTile(GameView* game_view, qreal width, qreal height,
                 QPointF pos);
  ~TrampolineTile() override = default;

  void SetPixmap(const QPixmap& pixmap);

  void Activate();

  bool CheckPath(const TrampolinePath& path_item_, QPointF start,
                 QPointF finish);

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
