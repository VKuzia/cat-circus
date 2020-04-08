#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QTextStream>
#include <qfile.h>

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
  QFile file("score.txt");
  if(file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
      // We're going to streaming text to the file
      QTextStream stream(&file);
      QString points = "";
      stream >> points;
      int pr = ui->progressBar->value();
      int add = points.toInt()/100;
      ui->progressBar->setValue(pr + add);
      ui->progressBar->repaint();
      file.close();
  }
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
