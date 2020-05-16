#include "settingswidget.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_settingswidget.h"


SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget(parent), ui_(new Ui::SettingsWidget) {
  ui_->setupUi(this);

  for (auto element : kLanguages_) {
    ui_->ui_language_combo_box_->addItem(element);
  }

  for (auto element : kResolutions_) {
    ui_->ui_resolution_combo_box_->addItem(QString::number(element.width()) +
                                         "×" +
                                         QString::number(element.height()));
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
        QMessageBox::warning(
            nullptr, "Warning",
            "Settings were not saved. \n");
        return;
    }

    QTextStream save(&file);
    save.setCodec("UTF-8");

    int current_resolution_index =
            ui_->ui_resolution_combo_box_->currentIndex();
    int current_language_index = ui_->ui_language_combo_box_->currentIndex();
    save << volume_on_ << '\n'
         << volume_ << '\n'
         << kResolutions_[current_resolution_index].width() << ' '
         << kResolutions_[current_resolution_index].height() << '\n'
         << kLanguages_[current_language_index] << '\n'
         << user_name_ << '\n';

    file.close();
}

void SettingsWidget::Load() {
    QFile file(kPathToSettings + "basic_settings.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(
            nullptr, "Warning",
            "Settings file was not found. Default settings were applied.\n");
        return;
    }
    QTextStream load(&file);
    load.setCodec("UTF-8");

    volume_on_ = load.readLine().toInt() == 1;
    ui_->ui_sound_check_box_->setChecked(volume_on_);

    int volume = load.readLine().toInt();
    if (volume >= ui_->ui_volume_->minimum() &&
            volume <= ui_->ui_volume_->maximum()) {
        volume_ = volume;
        ui_->ui_volume_->setValue(volume_);
    } else {
        QMessageBox::warning(
            nullptr, "Warning",
            "Invalid volume. Default volume was applied.\n");
    }

    QStringList size_pair = load.readLine().split(' ');
    if (size_pair.size() > 1) {
        QSize loaded_size{size_pair[0].toInt(), size_pair[1].toInt()};
        int resolution_index = kResolutions_.indexOf(loaded_size);
        if (resolution_index == -1) {
            QMessageBox::warning(
                nullptr, "Warning",
                "Invalid resolution. Default resolution was applied.\n");
        } else {
            ui_->ui_resolution_combo_box_->setCurrentIndex(resolution_index);
        }
    } else {
        QMessageBox::warning(
            nullptr, "Warning",
            "Invalid resolution. Default resolution was applied.\n");
    }

    QString loaded_language = load.readLine();
    int language_index = kLanguages_.indexOf(loaded_language);
    if (language_index == -1) {
        QMessageBox::warning(
            nullptr, "Warning",
            "Invalid language. Default language was applied.\n");
    } else {
        ui_->ui_language_combo_box_->setCurrentIndex(language_index);
    }

    user_name_ = load.readLine();
    ui_->ui_user_line_edit_->setText(user_name_);

    file.close();
}

QSize SettingsWidget::GetResolution() const {
    return kResolutions_[ui_->ui_resolution_combo_box_->currentIndex()];
}

QString SettingsWidget::GetLanguage() const {
    return kLanguages_[ui_->ui_language_combo_box_->currentIndex()];
}

void SettingsWidget::ChangeSound() {
    if (ui_->ui_sound_check_box_->isChecked()) {
        ui_->ui_sound_check_box_->setText("Off");
        volume_on_ = false;
        return;
    }
    ui_->ui_sound_check_box_->setText("On");
    volume_on_ = true;
}

void SettingsWidget::ChangeVolume() {
    volume_ = ui_->ui_volume_->value();
}

void SettingsWidget::ChangeLanguage() {
    emit LanguageChanged();
}

void SettingsWidget::ChangeUserName() {
    user_name_ = ui_->ui_user_line_edit_->text();
}

void SettingsWidget::ChangeResolution() {
    emit ResolutionChanged();
}
