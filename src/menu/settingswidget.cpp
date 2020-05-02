#include "settingswidget.h"

#include "mainwindow.h"
#include "ui_settingswidget.h"

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

void SettingsWidget::ChangeSound()
{
    TurnVolume();
}

void SettingsWidget::ChangeResolution()
{
    if(ui_->ui_resolution_combo_box_->currentIndex() == 1) {
    }
}

