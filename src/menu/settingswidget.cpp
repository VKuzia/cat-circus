#include "settingswidget.h"
#include <QFile>
#include <QTextStream>

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

void SettingsWidget::Save() {
    QFile file(kPathToSettings + "basic_settings.txt");
    try {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            throw std::runtime_error("Error, imposible to save changes!");
        }
    }
    catch(std::exception const& exception) {
        QTextStream error(stdout);
        error << exception.what() << "\n";
    }

    QTextStream save(&file);
    save.setCodec("UTF-8");

//    save << resolution_.width() << " " << resolution_.height() << "\n";

    save << volume_off_ << "\n";

    volume_ = ui_->ui_volume_->value();
    save << volume_ << "\n";

//    save << current_resolution_index_ << "\n";

    save << ui_->ui_resolution_combo_box_->currentIndex() << "\n";

    current_language_index_ = ui_->ui_language_combo_box_->currentIndex();
    save << current_language_index_ << "\n";

    user_name_ = ui_->ui_user_line_edit_->text();
    save << user_name_ << "\n";

    file.close();
}

void SettingsWidget::Load() {
    QFile file(kPathToSettings + "basic_settings.txt");
    try {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw std::runtime_error("Error, imposible to load changes!");
        }
    }
    catch(std::exception const& exception) {
        QTextStream error(stdout);
        error << exception.what() << "\n";
    }

    QTextStream load(&file);
    load.setCodec("UTF-8");

    QString volume_off_line = load.readLine();
    int64_t volume_off_int_ = volume_off_line.toInt();
    volume_off_ = (volume_off_int_ == 0 ? false : true);
    ui_->ui_sound_check_box_->setChecked(volume_off_);

    QString volume_line = load.readLine();
    volume_ = volume_line.toInt();
    ui_->ui_volume_->setValue(volume_);

    QString current_resolution_line = load.readLine();
    ui_->ui_resolution_combo_box_->setCurrentIndex(
                current_resolution_line.toInt());

    QString current_language_index_line = load.readLine();
    current_language_index_ = current_language_index_line.toInt();
    ui_->ui_language_combo_box_->setCurrentIndex(current_language_index_);

    user_name_ = load.readLine();
    ui_->ui_user_line_edit_->setText(user_name_);
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

void SettingsWidget::ChangeResolution() {
    emit ResolutionChanged();
}

