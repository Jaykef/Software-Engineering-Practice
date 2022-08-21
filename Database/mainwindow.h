#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlDatabase db;

private slots:
    void on_pushButton_clicked();

    void on_pushButtonSelect_clicked();

    void on_pushButtonInsert_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonQuery_clicked();

    void on_pushButtonUpdate_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
