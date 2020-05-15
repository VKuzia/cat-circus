#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QDir>
#include <QMap>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SettingsWidget(QWidget* parent = nullptr);
  ~SettingsWidget();

  void Load();
  QSize GetResolution() const;

 signals:
  void MainMenu();
  void ResolutionChanged();

 public slots:
  void ReturnToMainMenu();

  void ChangeSound();

  void ChangeVolume();

  void ChangeLanguage();

  void ChangeUserName();

  void ChangeResolution();

 private:
  const QString kPathToSettings = QDir::currentPath() + "/data/settings/";
  const QVector<QSize> kResolutions_ = {
      {1024, 576}, {1366, 768}, {1600, 900}, {1920, 1080}, {3200, 1800}};
  bool volume_on_ = false;
  int volume_ = 1;
  int current_language_index_ = 0;
  QString user_name_ = "Player";

  Ui::SettingsWidget* ui_;

  void Save() const;
};

#endif  // SETTINGSWIDGET_H
