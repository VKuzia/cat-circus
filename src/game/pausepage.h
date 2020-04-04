#ifndef PAUSEPAGE_H
#define PAUSEPAGE_H

#include <QObject>
#include <QWidget>

namespace Ui {
class PausePage;
}

class PausePage : public QWidget {
  Q_OBJECT

 public:
  explicit PausePage(QWidget* parent = nullptr);

 signals:
  void MainMenu();
  void Resume();

 public slots:
  void EmitMainMenu();

 private:
  Ui::PausePage* ui;

  void mousePressEvent(QMouseEvent* event) override;
};

#endif  // PAUSEPAGE_H
