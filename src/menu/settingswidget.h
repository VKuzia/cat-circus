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

 private slots:
  void ChangeSound();

  void ChangeResolution();

 private:
  const QString kPathToSettings = QDir::currentPath() + "/data/settings/";
  const QVector<QSize> kResolutions_ = {{1024, 576}, {1366, 768}, {1600, 900}, {1920, 1080}, {3200, 1800}};
  bool volume_off_;
  int volume_;
  int current_language_index_;
  QString user_name_;

  Ui::SettingsWidget* ui_;

  void Save();
};

#endif  // SETTINGSWIDGET_H
