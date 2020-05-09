#ifndef TRAMPOLINETILE_H
#define TRAMPOLINETILE_H

#include "QPropertyAnimation"
#include "src/game/gameobject.h"
#include "src/game/minigames/trampoline/trampolinepath.h"

class TrampolineTile : public GameObject {
  Q_OBJECT
  Q_PROPERTY(qreal animationProgress READ GetAnimationProgress WRITE
                 SetAnimationProgress)

 public:
  enum class SwipeDirection { kUp, kDown, kLeft, kRight };

  TrampolineTile(GameView* game_view, QSizeF size, qreal x, qreal y);
  ~TrampolineTile() override = default;

  void SetPixmap(const QPixmap& pixmap);

  void Activate();
  void Deactivate(bool is_path_correct);

  bool CheckPath(const TrampolinePath& path_item_, QPointF start,
                 QPointF finish);

  void SetDirection(SwipeDirection direction);

 private:
  const qreal kMinimalSwipeLength_ = 3;
  const qreal kMinimalPathRectRatio_ = 6;

  const qreal kNoFocusOpacity_ = 0.8;
  const qreal kScaleAnimationAmount_ = 0.1;
  const int32_t kScaleAnimationDuration_ = 300;

  const QColor kFailColor_ = QColor::fromRgb(200, 0, 0);
  const QColor kPassColor_ = QColor::fromRgb(0, 200, 0);
  const qreal kEffectStrength_ = 0.7;

  QPropertyAnimation animation_;
  SwipeDirection direction_ = SwipeDirection::kUp;
  qreal animation_progress_ = 0;

  qreal GetAnimationProgress() const;
  void SetAnimationProgress(qreal progress);
};

#endif  // TRAMPOLINETILE_H
