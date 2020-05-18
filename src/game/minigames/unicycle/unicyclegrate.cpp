#include "unicyclegrate.h"

UnicycleGrate::UnicycleGrate(GameView* game_view, QSizeF size, QPointF pos)
    : GameObject(game_view, size, pos) {}

void UnicycleGrate::SetUp() {
  setPixmap(LoadPixmap("unicycle/grate_opened.png"));
}

void UnicycleGrate::Close() {
  setPixmap(LoadPixmap("unicycle/grate_closed.png"));
}
