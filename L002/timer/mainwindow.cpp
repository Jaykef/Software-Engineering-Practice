#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "outtimer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dtl = new OutTimer();
    dtl->setParent(this);
    dtl->setGeometry(10,20,2000,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}
