#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "studentaddwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->AddButton, &QPushButton::clicked, this, &MainWindow::showAddWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAddWindow()
{
    QWidget *addWindow = new StudentAddWindow(this);
    addWindow->show();
}

