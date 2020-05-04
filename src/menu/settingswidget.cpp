#include "settingswidget.h"
#include <QtCore>
#include <QSettings>
#include <QDir>

#include "mainwindow.h"
#include "ui_settingswidget.h"

const QString SettingsWidget::kPathToSettings =
    QDir::currentPath() + "/data/settings/";

// this->setOffset(qRound(boundingRect().x()), qRound(boundingRect().y()));
// QPixmap pixmap = QPixmap(kPathToMinigameImages + "juggling/cat.png");

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


//  QSettings resolutionSetting("my company","catsProject");
//  resolutionSetting.beginGroup("SettingWindow");
//  ui_->ui_resolution_combo_box_->setCurrentIndex(resolutionSetting.value("position").toInt());
//  resolutionSetting.endGroup();
}

void SettingsWidget::ReturnToMainMenu() { emit MainMenu(); }

void SettingsWidget::TurnVolume()
{
    if (ui_->ui_sound_check_box_->isChecked()) {
        ui_->ui_sound_check_box_->setText("Off");
    }
    else {
        ui_->ui_sound_check_box_->setText("On");
    }
}

SettingsWidget::~SettingsWidget() { delete ui_; }

void SettingsWidget::Load()
{

}

QSize SettingsWidget::GetSize()
{
    QSize* test_size = new QSize(0, 0);
    return *test_size;
}

void SettingsWidget::ChangeSound()
{
    TurnVolume();
}

void SettingsWidget::ChangeResolution()
{
    QSettings resolutionSetting("my company","catsProject");
    resolutionSetting.beginGroup("SettingWindow");
    if(ui_->ui_resolution_combo_box_->currentIndex() == 1) {
        resolutionSetting.setValue("position", 1);
//        QRect* currentRect = new QRect(0, 0, 1024, 576);
//        setGeometry(*currentRect);
    }
    if(ui_->ui_resolution_combo_box_->currentIndex() == 2) {
        resolutionSetting.setValue("position", 2);
//        QRect* currentRect = new QRect(0, 0, 1280, 800);
//        setGeometry(*currentRect);
    }
    if(ui_->ui_resolution_combo_box_->currentIndex() == 3) {
        resolutionSetting.setValue("position", 3);
//        QRect* currentRect = new QRect(0, 0, 1920, 1080);
//        setGeometry(*currentRect);
    }
    if(ui_->ui_resolution_combo_box_->currentIndex() == 4) {
        resolutionSetting.setValue("position", 4);

//        QRect* currentRect = new QRect(0, 0, 4096, 2160);
//        this->setGeometry(0, 0, 4096, 2160);
//        setGeometry(*currentRect);
    }
    resolutionSetting.endGroup();

}

