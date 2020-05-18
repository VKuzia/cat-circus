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
  ~PausePage() override;

 signals:
  void MainMenu();
  void Resume();

 public slots:
  void ReturnToMainMenu();

 private:
  Ui::PausePage* ui_;

  void mousePressEvent(QMouseEvent* event) override;

  void resizeEvent(QResizeEvent* event) override;
};

#endif  // PAUSEPAGE_H
