#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(int32_t width, int32_t height, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  this->setFixedSize(width, height);
  connect(ui_->ui_settings_widget_, &SettingsWidget::MainMenu, this,
          &MainWindow::ChangeToMainMenu);
  connect(ui_->ui_about_widget_, &AboutWidget::MainMenu, this,
          &MainWindow::ChangeToMainMenu);
  connect(ui_->ui_game_widget_, &GameWidget::MainMenu, this,
          &MainWindow::ChangeToMainMenu);
}

void MainWindow::ChangeToMainMenu() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_main_menu_widget_);
}

void MainWindow::ChangeToGame() {
  ui_->ui_game_widget_->SetUp();
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_game_widget_);
}

void MainWindow::ChangeToSettings() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_settings_widget_);
}

void MainWindow::ChangeToAbout() {
  ui_->ui_stacked_widget_->setCurrentWidget(ui_->ui_about_widget_);
}

void MainWindow::Exit() { QApplication::exit(0); }

MainWindow::~MainWindow() { delete ui_; }
