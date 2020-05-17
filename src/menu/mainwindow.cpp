#include "mainwindow.h"

#include <QResizeEvent>
#include <QStackedLayout>

#include "src/game/gameobject.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  connect(ui_->ui_settings_widget_, &SettingsWidget::MainMenu, this,
          &MainWindow::ChangeToMainMenu);
  connect(ui_->ui_about_widget_, &AboutWidget::MainMenu, this,
          &MainWindow::ChangeToMainMenu);
  connect(ui_->ui_game_widget_, &GameWidget::MainMenu, this,
          &MainWindow::ChangeToMainMenu);
  connect(ui_->ui_settings_widget_, &SettingsWidget::ResolutionChanged, this,
          &MainWindow::SetUp);
  dynamic_cast<QStackedLayout*>(ui_->ui_base_stacked_widget_->layout())
      ->setStackingMode(QStackedLayout::StackingMode::StackAll);
  ui_->ui_loading_page_->SetUp();
  connect(ui_->ui_loading_page_, &LoadingWidget::BecameOpaque, this,
          &MainWindow::ChangeWidget);
  connect(ui_->ui_loading_page_, &LoadingWidget::AnimationFinished, this,
          &MainWindow::SetGamePage);

  GameObject::GetPixmapLoader()->PreloadPixmaps();
}

void MainWindow::ChangeToMainMenu() {
  widget_to_change_to_ = ui_->ui_main_menu_widget_;
  AnimateLoading();
}

void MainWindow::ChangeToGame() {
  widget_to_change_to_ = ui_->ui_game_widget_;
  ui_->ui_game_widget_->SetUp();
  AnimateLoading();
}

void MainWindow::ChangeToSettings() {
  widget_to_change_to_ = ui_->ui_settings_widget_;
  AnimateLoading();
}

void MainWindow::ChangeToAbout() {
  widget_to_change_to_ = ui_->ui_about_widget_;
  AnimateLoading();
}

void MainWindow::Exit() { QApplication::exit(0); }

void MainWindow::AnimateLoading() {
  ui_->ui_base_stacked_widget_->setCurrentWidget(ui_->ui_loading_page_);
  ui_->ui_loading_page_->Animate();
}

void MainWindow::SetGamePage() {
  ui_->ui_base_stacked_widget_->setCurrentWidget(ui_->ui_game_page_);
  if (widget_to_change_to_ == ui_->ui_game_widget_) {
    ui_->ui_game_widget_->Start();
  }
}

void MainWindow::resizeEvent(QResizeEvent* event) {
  ui_->ui_exit_button_->Resize(event);
  ui_->ui_play_button_->Resize(event);
  ui_->ui_settings_button_->Resize(event);
  ui_->ui_about_button_->Resize(event);
}

void MainWindow::ChangeWidget() {
  ui_->ui_stacked_widget_->setCurrentWidget(widget_to_change_to_);
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::SetUp() {
  QSize resolution = ui_->ui_settings_widget_->GetResolution();
  this->setFixedSize(resolution);
  ui_->ui_game_widget_->SetResolution(resolution);
}
