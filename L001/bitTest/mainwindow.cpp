#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:black");
    this->resize(500,500);

    labTitle=new QLabel();

    labTitle->setParent(this);
    labTitle->setText("T-");
    labTitle->setStyleSheet("font-size:56px;color:rgb(255,0,255)");
    labTitle->setGeometry(50,50,100,100);

    labTemperature=new QLabel;
    labTemperature->setParent(this);
    labTemperature->setText("36.5");
    labTemperature->setStyleSheet("font-size:66px;color:rgb(255,0,255)");
    labTemperature->setGeometry(200,50,200,105);
}

MainWindow::~MainWindow()
{
    delete ui;
}

