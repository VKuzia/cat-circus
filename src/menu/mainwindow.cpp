#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(int32_t width, int32_t height, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFixedSize(width, height);
  connect(ui->ui_settings_widget, SIGNAL(MainMenu()), this,
          SLOT(ChangeToMainMenu()));
  connect(ui->ui_about_widget, SIGNAL(MainMenu()), this,
          SLOT(ChangeToMainMenu()));
  connect(ui->ui_game_widget, SIGNAL(MainMenu()), this,
          SLOT(ChangeToMainMenu()));
}

void MainWindow::ChangeToMainMenu() {
  ui->ui_stacked_widget->setCurrentWidget(ui->ui_main_menu_widget);
}

void MainWindow::ChangeToGame() {
  ui->ui_game_widget->SetUp();
  ui->ui_stacked_widget->setCurrentWidget(ui->ui_game_widget);
}

void MainWindow::ChangeToSettings() {
  ui->ui_stacked_widget->setCurrentWidget(ui->ui_settings_widget);
}

void MainWindow::ChangeToAbout() {
  ui->ui_stacked_widget->setCurrentWidget(ui->ui_about_widget);
}

void MainWindow::Exit() { QApplication::exit(0); }

MainWindow::~MainWindow() { delete ui; }
