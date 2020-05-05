#include "settingswidget.h"
#include <QtCore>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_settingswidget.h"

const QString SettingsWidget::kPathToSettings =
    QDir::currentPath() + "/data/settings/";

SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::SettingsWidget) {
  ui_->setupUi(this);
  ui_->ui_language_combo_box_->addItem("english");
  ui_->ui_language_combo_box_->addItem("русский");
  ui_->ui_language_combo_box_->addItem("беларуская");
  ui_->ui_resolution_combo_box_->addItem("1024×576");
  ui_->ui_resolution_combo_box_->addItem("1280×800");
  ui_->ui_resolution_combo_box_->addItem("1920×1080");
  ui_->ui_resolution_combo_box_->addItem("4096×2160");
  Load();

//  QSettings resolutionSetting("my company","catsProject");
//  resolutionSetting.beginGroup("SettingWindow");
//  ui_->ui_resolution_combo_box_->setCurrentIndex(resolutionSetting.value("position").toInt());
//  resolutionSetting.endGroup();
}

SettingsWidget::~SettingsWidget() { delete ui_; }

void SettingsWidget::ReturnToMainMenu()
{
    Save();
    emit MainMenu();
}

void SettingsWidget::TurnVolume()
{
    if (ui_->ui_sound_check_box_->isChecked()) {
        ui_->ui_sound_check_box_->setText("Off");
        volume_off_ = true;
    }
    else {
        ui_->ui_sound_check_box_->setText("On");
        volume_off_ = false;
    }
}

void SettingsWidget::Save()
{
    QFile file (kPathToSettings + "basic.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {}

    QTextStream save(&file);
    save.setCodec("UTF-8");

    save << resolution_.width() << " " << resolution_.height() << "\n";

    save << volume_off_ << "\n";

    volume_ = ui_->ui_volume_->value();
    save << volume_ << "\n";

    current_resolution_index_ = ui_->ui_resolution_combo_box_->currentIndex();
    save << current_resolution_index_ << "\n";

    current_language_index_ = ui_->ui_language_combo_box_->currentIndex();
    save << current_language_index_ << "\n";

    user_name_ = ui_->ui_user_line_edit_->text();
    save << user_name_ << "\n";

    file.close();
}

void SettingsWidget::Load()
{
    QFile file (kPathToSettings + "basic.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {}

    QTextStream load(&file);
    load.setCodec("UTF-8");

    QString resolution_line = load.readLine();
    QStringList resolution_pair = resolution_line.split(' ');
    resolution_.setWidth(resolution_pair[0].toInt());
    resolution_.setHeight(resolution_pair[1].toInt());

    QString volume_off_line = load.readLine();
    volume_off_ = volume_off_line.toInt();
    ui_->ui_sound_check_box_->setChecked(volume_off_);

    QString volume_line = load.readLine();
    volume_ = volume_line.toInt();
    ui_->ui_volume_->setValue(volume_);

    QString current_resolution_index_line = load.readLine();
    current_resolution_index_ = current_resolution_index_line.toInt();
    ui_->ui_resolution_combo_box_->setCurrentIndex(current_resolution_index_);

    QString current_language_index_line = load.readLine();
    current_language_index_ = current_language_index_line.toInt();
    ui_->ui_language_combo_box_->setCurrentIndex(current_language_index_);

    user_name_ = load.readLine();
    ui_->ui_user_line_edit_->setText(user_name_);
}

QSize SettingsWidget::GetSize()
{
    return resolution_;
}

void SettingsWidget::ChangeSound()
{
    TurnVolume();
}

void SettingsWidget::ChangeResolution()
{
    switch(ui_->ui_resolution_combo_box_->currentIndex())
    {
    case 0:
        resolution_.setWidth(1024);
        resolution_.setHeight(576);
        break;
    case 1:
        resolution_.setWidth(1280);
        resolution_.setHeight(800);
        break;
    case 2:
        resolution_.setWidth(1920);
        resolution_.setHeight(1080);
        break;
    case 3:
        resolution_.setWidth(4096);
        resolution_.setHeight(2160);
        break;
    }

//    QSettings resolutionSetting("my company","catsProject");
//    resolutionSetting.beginGroup("SettingWindow");
//    if(ui_->ui_resolution_combo_box_->currentIndex() == 1) {
//        resolutionSetting.setValue("position", 1);
//        QRect* currentRect = new QRect(0, 0, 1024, 576);
//        setGeometry(*currentRect);
//    }
//    if(ui_->ui_resolution_combo_box_->currentIndex() == 2) {
//        resolutionSetting.setValue("position", 2);
//        QRect* currentRect = new QRect(0, 0, 1280, 800);
//        setGeometry(*currentRect);
//    }
//    if(ui_->ui_resolution_combo_box_->currentIndex() == 3) {
//        resolutionSetting.setValue("position", 3);
//        QRect* currentRect = new QRect(0, 0, 1920, 1080);
//        setGeometry(*currentRect);
//    }
//    if(ui_->ui_resolution_combo_box_->currentIndex() == 4) {
//        resolutionSetting.setValue("position", 4);

//        QRect* currentRect = new QRect(0, 0, 4096, 2160);
//        this->setGeometry(0, 0, 4096, 2160);
//        setGeometry(*currentRect);
//    }
//    resolutionSetting.endGroup();
}

