#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SettingsWidget(QWidget* parent = nullptr);
  ~SettingsWidget();

 signals:
  void MainMenu();

 public slots:
  void ReturnToMainMenu();

private slots:
  void ChangeSound();

  void ChangeResolution();

  void on_ui_sound_check_box__stateChanged(int arg1);

private:

  void TurnVolume();

  Ui::SettingsWidget* ui_;
};

#endif  // SETTINGSWIDGET_H
