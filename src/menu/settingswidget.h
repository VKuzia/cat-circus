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

    void Load();
    QSize GetSize();

 signals:
  void MainMenu();

 public slots:
  void ReturnToMainMenu();

private slots:
  void ChangeSound();

  void ChangeResolution();

private:

  void TurnVolume();

  static const QString kPathToSettings;
  QSize resolution_;
  bool volume_on_;
  int volume_;
  int current_resolution_index_;
  int current_language_index_;
  QString user_name_;


  Ui::SettingsWidget* ui_;
};

#endif  // SETTINGSWIDGET_H
