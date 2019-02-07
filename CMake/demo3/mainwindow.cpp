#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->quitButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
