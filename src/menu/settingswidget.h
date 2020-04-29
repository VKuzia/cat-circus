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
  void OnUiSoundCheckBoxStateChanged();

  void OnUiStatisticsButtonClicked();

private:

  void TurnVolume();

  Ui::SettingsWidget* ui_;
};

#endif  // SETTINGSWIDGET_H
