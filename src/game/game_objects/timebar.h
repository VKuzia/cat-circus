#ifndef TIMEBAR_H
#define TIMEBAR_H

#include <QObject>
#include <QPropertyAnimation>

#include "src/game/graphicsobject.h"

class TimeBar : public QObject, public GraphicsObject {
  Q_OBJECT

 public:
  TimeBar(QGraphicsView* graphics_view, qreal width, qreal height, qreal x = 0,
          qreal y = 0);
  ~TimeBar() override;
  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

  void SetProgress(qreal progress);

 signals:

 public slots:

 private:
  const QColor kBasicColor = QColor::fromRgb(81, 204, 24);
  qreal progress_ = 1;
};

#endif  // TIMEBAR_H
