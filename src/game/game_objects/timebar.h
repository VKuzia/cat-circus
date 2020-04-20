#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QObject>
#include <QPropertyAnimation>

#include "src/game/graphicsobject.h"

class TimeBar : public QObject, public GraphicsObject {
  Q_OBJECT

 public:
  TimeBar(QGraphicsView* graphics_view, float width, float height, float x = 0,
          float y = 0);
  ~TimeBar() override;

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

  void SetProgress(float progress);

 private:
  const QColor kBasicColor = QColor::fromRgb(81, 204, 24);
  float progress_ = 1;
};

#endif  // TIMEBAR_H
