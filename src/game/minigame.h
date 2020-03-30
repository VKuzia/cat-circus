#ifndef MINIGAME_H
#define MINIGAME_H

#include <QGraphicsView>
#include <QObject>

class MiniGame : public QObject {
  Q_OBJECT
 public:
  explicit MiniGame(QGraphicsView* graphics_view, int32_t width, int32_t height,
                    qreal difficulty);
  virtual ~MiniGame() = default;

  virtual void Start() = 0;
  virtual void Pause() = 0;

 signals:
  void Finish(int64_t score);

 public slots:

 private:
  QGraphicsView* graphics_view_;
  int32_t width_;
  int32_t height_;
  qreal difficulty_;

  virtual void Stop() = 0;
};

#endif  // MINIGAME_H
