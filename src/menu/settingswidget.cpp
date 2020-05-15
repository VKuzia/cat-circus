#include "settingswidget.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_settingswidget.h"


SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::SettingsWidget) {
  ui_->setupUi(this);
  ui_->ui_language_combo_box_->addItem("english");
  ui_->ui_language_combo_box_->addItem("русский");
  ui_->ui_language_combo_box_->addItem("беларуская");

  for (auto element = kResolutions_.begin();
      element != kResolutions_.end(); ++element) {
  ui_->ui_resolution_combo_box_->addItem(QString::number(element->width())
                                         + "×"
                                         + QString::number(element->height()));
  }

  Load();
}

SettingsWidget::~SettingsWidget() { delete ui_; }

void SettingsWidget::ReturnToMainMenu() {
    Save();
    emit MainMenu();
}

void SettingsWidget::Save() const {
    QDir(kPathToSettings).mkpath(".");

    QFile file(kPathToSettings + "basic_settings.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Imposible to save changes! \n");
        return;
    }

    QTextStream save(&file);
    save.setCodec("UTF-8");

    save << volume_off_ << "\n";

    save << volume_ << "\n";

    int current_index = ui_->ui_resolution_combo_box_->currentIndex();
    save << kResolutions_[current_index].width();
    save << " ";
    save << kResolutions_[current_index].height() << "\n";

    save << current_language_index_ << "\n";

    save << user_name_ << "\n";

    file.close();
}

void SettingsWidget::Load() {
    QFile file(kPathToSettings + "basic_settings.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Imposible to load changes! \n");
        return;
    }

    QTextStream load(&file);
    load.setCodec("UTF-8");

    volume_off_ = load.readLine().toInt() == 1;
    ui_->ui_sound_check_box_->setChecked(volume_off_);

    int volume = load.readLine().toInt();
    if (volume >= ui_->ui_volume_->minimum() &&
            volume <= ui_->ui_volume_->maximum()) {
        volume_ = volume;
        ui_->ui_volume_->setValue(volume_);
    }

    QSize loaded_size;
    QStringList size_pair = load.readLine().split(' ');
    loaded_size.setWidth(size_pair[0].toInt());
    loaded_size.setHeight(size_pair[1].toInt());
    for (int i = 0; i < kResolutions_.size(); i++) {
        if (loaded_size == kResolutions_[i]) {
            ui_->ui_resolution_combo_box_->setCurrentIndex(i);
            break;
        }
    }

    int language_index = load.readLine().toInt();
    if (language_index >= 0 && language_index <=
            ui_->ui_language_combo_box_->count()) {
        current_language_index_ = language_index;
        ui_->ui_language_combo_box_->setCurrentIndex(
                    current_language_index_);
    }

    user_name_ = load.readLine();
    ui_->ui_user_line_edit_->setText(user_name_);

    file.close();
}

QSize SettingsWidget::GetResolution() const {
    return kResolutions_[ui_->ui_resolution_combo_box_->currentIndex()];
}

void SettingsWidget::ChangeSound() {
    if (ui_->ui_sound_check_box_->isChecked()) {
        ui_->ui_sound_check_box_->setText("Off");
        volume_off_ = true;
        return;
    }
    ui_->ui_sound_check_box_->setText("On");
    volume_off_ = false;
}

void SettingsWidget::ChangeVolume() {
    volume_ = ui_->ui_volume_->value();
}

void SettingsWidget::ChangeLanguage() {
    current_language_index_ = ui_->ui_language_combo_box_->currentIndex();
}

void SettingsWidget::ChangeUserName() {
    user_name_ = ui_->ui_user_line_edit_->text();
}

void SettingsWidget::ChangeResolution() {
    emit ResolutionChanged();
}

