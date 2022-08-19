// Jaward/Jaykef (苏杰）- main.cpp
#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QWidget * widgetMainTile  = new QWidget();
    widgetMainTile->setStyleSheet("background-color:rgb(100,100,100)");

    QWidget * widgetWaveEcg = new QWidget();
    widgetWaveEcg->setStyleSheet("background-color:white");
    QWidget * widgetWaveSpo2 = new QWidget();
    widgetWaveSpo2->setStyleSheet("background-color:green");
    QWidget * widgetWaveResp = new QWidget();
    widgetWaveResp->setStyleSheet("background-color:white");
    QVBoxLayout * layoutWave = new QVBoxLayout();
    layoutWave->addWidget(widgetWaveEcg);
    layoutWave->addWidget(widgetWaveSpo2);
    layoutWave->addWidget(widgetWaveResp);

    QWidget *widgetHr = new QWidget();
    widgetHr->setStyleSheet("background-color:rgb(100,100,100)");
    QWidget *widgetSt = new QWidget();
    widgetSt->setStyleSheet("background-color:rgb(100,100,200)");
    QWidget *widgetNibp = new QWidget();
    widgetNibp->setStyleSheet("background-color:rgb(100,200,100)");
    QWidget *widgetSpo2 = new QWidget();
    widgetSpo2->setStyleSheet("background-color:rgb(200,100,100)");
    QWidget *widgetTemp = new QWidget();
    widgetTemp->setStyleSheet("background-color:rgb(200,200,100)");
    QWidget *widgetResp = new QWidget();
    widgetResp->setStyleSheet("background-color:rgb(100,200,200)");
    QWidget *widgetCo2 = new QWidget();
    widgetCo2->setStyleSheet("background-color:rgb(200,100,200)");

    QHBoxLayout * layoutTableLine1 = new QHBoxLayout();
    layoutTableLine1->addWidget(widgetHr);
    layoutTableLine1->addWidget(widgetSt);

    QHBoxLayout * layoutTableLine2 = new QHBoxLayout();
    layoutTableLine2->addWidget(widgetNibp);

    QHBoxLayout * layoutTableLine3 = new QHBoxLayout();
    layoutTableLine3->addWidget(widgetSpo2);
    layoutTableLine3->addWidget(widgetTemp);

    QHBoxLayout * layoutTableLine4 = new QHBoxLayout();
    layoutTableLine4->addWidget(widgetResp);
    layoutTableLine4->addWidget(widgetCo2);

    QVBoxLayout * layoutTable = new QVBoxLayout();
    layoutTable->addLayout(layoutTableLine1);
    layoutTable->addLayout(layoutTableLine2);
    layoutTable->addLayout(layoutTableLine3);
    layoutTable->addLayout(layoutTableLine4);

    QHBoxLayout * layoutDown = new QHBoxLayout();
    layoutDown->addLayout(layoutWave);
    layoutDown->addLayout(layoutTable);
    layoutDown->setStretch(0,2);
    layoutDown->setStretch(1,1);

    QVBoxLayout * layoutMain = new QVBoxLayout();
    layoutMain->addWidget(widgetMainTile);
    layoutMain->addLayout(layoutDown);
    layoutMain->setStretch(0,1);
    layoutMain->setStretch(1,9);

    QWidget *widgetMain = new QWidget();
    widgetMain->setStyleSheet("background-color:black");
    widgetMain->setLayout(layoutMain);
    widgetMain->resize(800,480);

    //widgetMain->setParent(&w);
    w.setCentralWidget(widgetMain);
    w.resize(800,480);
    w.show();

    return a.exec();
}
