#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>

namespace Ui {
class AboutWidget;
}

class AboutWidget : public QWidget {
  Q_OBJECT

 public:
  explicit AboutWidget(QWidget* parent = nullptr);
  ~AboutWidget();

 signals:
  void MainMenu();

 public slots:
  void ReturnToMainMenu();

 private:
  Ui::AboutWidget* ui_;
};

#endif  // ABOUTWIDGET_H
