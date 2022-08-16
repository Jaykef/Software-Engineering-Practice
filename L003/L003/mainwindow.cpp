#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylabel.h"
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    qDebug()<<"MainWindow";
    ui->setupUi(this);

    QPushButton * pushButton = new QPushButton(this);
    pushButton->setText("PushButton");
    pushButton->setGeometry(20,20,100,100);
    connect(pushButton,&QPushButton::clicked,this,&MainWindow::pushButtonClick);

    pushButton->setStyleSheet("\
            QPushButton{border-radius:50px;background-color:blue;}\
            QPushButton:hover{border-radius:50px;background-color:green;}\
            QPushButton:pressed{border-radius:50px;background-color:red;}\
        ");


    myLabel = new MyLabel(this);
    myLabel->setGeometry(100,100,50,50);
    myLabel->setText("Hello");

}


void MainWindow::pushButtonClick() {
   qDebug()<<"Push button clicked";
   myLabel->soltLabelStyleSheetUpdate();
}

MainWindow::~MainWindow() {
    delete ui;
    if(myLabel) delete myLabel;
}

void MainWindow::on_btnClose2_clicked() {
    qDebug()<<"on_btnClose_clicked";
    myLabel->soltLabelStyleSheetUpdate();
}
