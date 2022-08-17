#include "mainwindow.h"
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(800,480);
    QWidget *centralWidget = new QWidget(&w);

    QGridLayout * layout = new QGridLayout();
    layout->addWidget(new QPushButton("Button 1"),0,0);
    layout->addWidget(new QPushButton("Button 2"),0,1);
    layout->addWidget(new QPushButton("Button 3"),0,2);

    QPushButton *pb1 = new QPushButton("Button 4");
    pb1->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    pb1->setMaximumSize(100,100);
    pb1->setMinimumSize(10,10);
    layout->addWidget(pb1,1,3);

    centralWidget->setLayout(layout);
    w.setCentralWidget(centralWidget);

    w.show();
    return a.exec();
}
