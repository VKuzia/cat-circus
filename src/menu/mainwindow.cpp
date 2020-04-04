#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(int32_t width, int32_t height, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFixedSize(width, height);
  connect(ui->_settings_widget, SIGNAL(MainMenu()), this,
          SLOT(ChangeToMainMenu()));
  connect(ui->_about_widget, SIGNAL(MainMenu()), this,
          SLOT(ChangeToMainMenu()));
  connect(ui->_game_widget, SIGNAL(MainMenu()), this, SLOT(ChangeToMainMenu()));
}

void MainWindow::ChangeToMainMenu() {
  ui->_stacked_widget->setCurrentWidget(ui->_main_menu_widget);
}

void MainWindow::ChangeToGame() {
  ui->_game_widget->SetUp();
  ui->_stacked_widget->setCurrentWidget(ui->_game_widget);
}

void MainWindow::ChangeToSettings() {
  ui->_stacked_widget->setCurrentWidget(ui->_settings_widget);
}

void MainWindow::ChangeToAbout() {
  ui->_stacked_widget->setCurrentWidget(ui->_about_widget);
}

void MainWindow::Exit() { QApplication::exit(0); }

MainWindow::~MainWindow() { delete ui; }
