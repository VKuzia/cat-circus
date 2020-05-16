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
  QString GetLanguage() const;

 signals:
  void MainMenu();
  void ResolutionChanged();
  void LanguageChanged();

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
      {1024, 576}, {1366, 768}, {1280, 720},
      {1600, 900}, {1920, 1030}, {3200, 1800}};
  const QVector<QString> kLanguages_ = {"english"};

  bool volume_on_ = true;
  int volume_ = 1;
  QString user_name_ = "Player";

  Ui::SettingsWidget* ui_;

  void Save() const;
};

#endif  // SETTINGSWIDGET_H
