#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
#include<QSqlError>
#include<QStringList>
#include<QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList type=QSqlDatabase::drivers();
    qDebug()<<type;//显示一下支持哪些类型

    /*
use test;//这个数据库,默认mysql自带
create table fam(
    id int primary key AUTO_INCREMENT,
    name varchar(20),
    address varchar(40),
    age int,
    gender varchar(20));
mysql> show tables;
+---------------+
| Tables_in_db2 |
+---------------+
| fam           |
+---------------+
1 row in set (0.00 sec)

mysql> desc fam;
+---------+-------------+------+-----+---------+-------+
| Field   | Type        | Null | Key | Default | Extra |
+---------+-------------+------+-----+---------+-------+
| id      | int         | NO   | PRI | NULL    |       |
| name    | varchar(20) | YES  |     | NULL    |       |
| address | varchar(40) | YES  |     | NULL    |       |
| age     | int         | YES  |     | NULL    |       |
| gender  | varchar(20) | YES  |     | NULL    |       |
+---------+-------------+------+-----+---------+-------+
5 rows in set (0.00 sec)
mysql> insert into fam (id,name,address,age,gender) values(0,'tom','shanghai',20,'male');
Query OK, 1 row affected (0.00 sec)

mysql> insert into fam (name,address,age,gender) values('liutao','shanghai',23,'male');
Query OK, 1 row affected (0.00 sec)

mysql> insert into fam (name,address,age,gender) values('bin','suzhou',25,'male');
Query OK, 1 row affected (0.00 sec)

mysql> insert into fam (name,address,age,gender) values('hong','suzhou',34,'female');
Query OK, 1 row affected (0.00 sec)
mysql> select * from fam;
+----+--------+----------+------+--------+
| id | name   | address  | age  | gender |
+----+--------+----------+------+--------+
|  0 | tom    | shanghai |   20 | male   |
|  1 | liutao | shanghai |   23 | male   |
|  2 | bin    | suzhou   |   25 | male   |
|  3 | hong   | suzhou   |   34 | female |
+----+--------+----------+------+--------+
4 rows in set (0.00 sec)

mysql>
*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("127.0.0.1");  //连接本地主机
    db.setPort(3306);
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("123456");
    bool ok = db.open();
    if (ok){
        QMessageBox::information(this, "infor", "link success");
    }
    else {
        QMessageBox::information(this, "infor", "link failed");
        qDebug()<<"error open database because"<<db.lastError().text();
    }

}

void MainWindow::on_pushButtonSelect_clicked()
{
    QString sql="select * from fam";
    QSqlQuery query;
    query.exec(sql);
    ui->textEdit->clear();
    while(query.next())
    {
        ui->textEdit->insertPlainText(QString::number(query.value(0).toInt())+' ');
        ui->textEdit->insertPlainText(QString(query.value(1).toString())+' ');
        ui->textEdit->insertPlainText(QString(query.value(2).toString())+' ');
        ui->textEdit->insertPlainText(QString::number(query.value(3).toInt())+' ');
        ui->textEdit->insertPlainText(QString(query.value(4).toString()+="\n"));
    }
}

void MainWindow::on_pushButtonInsert_clicked()
{
    db.transaction();
    QSqlQuery query;
    QString name=ui->lineEditName->text();
    QString addres=ui->lineEditAddress->text();
    QString gender=ui->lineEditGender->text();
    if(name.trimmed() == "" ||addres.trimmed() == "" ||ui->lineEditAge->text().trimmed() == "" ||gender.trimmed() == "" ){
        QMessageBox::information(this, "infor", "please input all values!");
        return;
    }
    int age=ui->lineEditAge->text().toInt();
    QString sql=QString("insert into fam (name,address,age,gender) values ('%1','%2','%3','%4')").arg(name).arg(addres).arg(age).arg(gender);
    if(query.exec(sql)&&addres!=""&&gender!="")
    {
        db.commit();
        ui->lineEditName->clear();
        ui->lineEditAddress->clear();
        ui->lineEditAge->clear();
        ui->lineEditGender->clear();

        ui->textEdit->insertPlainText("insert ");
        ui->textEdit->insertPlainText(name+' ');
        ui->textEdit->insertPlainText(addres+' ');
        ui->textEdit->insertPlainText(QString::number(age)+' ');
        ui->textEdit->insertPlainText(gender+="\n");
    }
    else
    {
        db.rollback();
        QMessageBox::information(this,"connection info","add failed!");
    }
}

void MainWindow::on_pushButtonDelete_clicked()
{
    db.transaction();
    QSqlQuery query;

    if(ui->lineEditIndex->text()!="")
    {
        int index=ui->lineEditIndex->text().toInt();
        QString sql=QString("delete from fam where id='%1' ").arg(index);
        if(query.exec(sql))
        {
            db.commit();
            QMessageBox::information(this,"Info","Deleted!");
        }
        else
        {
            QMessageBox::information(this,"connection info","delete failed!");
            db.rollback();
        }
    }else{
        QMessageBox::information(this,"Info","index is empty!");
    }
}

void MainWindow::on_pushButtonQuery_clicked()
{
    db.transaction();
    QSqlQuery query;
    if(ui->lineEditIndex->text()!="")
    {
        int index=ui->lineEditIndex->text().toInt();
        QString sql=QString("select * from fam where id='%1' ").arg(index);
        query.exec(sql);
        ui->lineEditIndex->clear();
        while(query.next())
        {
            ui->textEdit->insertPlainText(QString::number(query.value(0).toInt())+' ');
            ui->textEdit->insertPlainText(QString(query.value(1).toString())+' ');
            ui->textEdit->insertPlainText(QString(query.value(2).toString())+' ');
            ui->textEdit->insertPlainText(QString::number(query.value(3).toInt())+' ');
            ui->textEdit->insertPlainText(QString(query.value(4).toString()+="\n"));
        }
    }else{
        QMessageBox::information(this,"Info","index is empty!");
    }
}

void MainWindow::on_pushButtonUpdate_clicked()
{
    db.transaction();
    QSqlQuery query;
    QString name=ui->lineEditName->text();
    QString addres=ui->lineEditAddress->text();
    QString gender=ui->lineEditGender->text();
    if(name.trimmed() == "" ||addres.trimmed() == "" ||ui->lineEditAge->text().trimmed() == "" ||gender.trimmed() == ""
            || ui->lineEditIndex->text().trimmed() == ""){
        QMessageBox::information(this, "infor", "please input all values!");
        return;
    }
    int age=ui->lineEditAge->text().toInt();
    int index=ui->lineEditIndex->text().toInt();
    QString sql=QString("update fam set name='%1',address='%2',age='%3',gender='%4' where id='%5'")
            .arg(name).arg(addres).arg(age).arg(gender).arg(index);
    if(query.exec(sql))
    {
        db.commit();
        ui->lineEditName->clear();
        ui->lineEditAddress->clear();
        ui->lineEditAge->clear();
        ui->lineEditGender->clear();

        ui->textEdit->insertPlainText("update ");
        ui->textEdit->insertPlainText(QString::number(index)+' ');
        ui->textEdit->insertPlainText(name+' ');
        ui->textEdit->insertPlainText(addres+' ');
        ui->textEdit->insertPlainText(QString::number(age)+' ');
        ui->textEdit->insertPlainText(gender+="\n");
    }
    else
    {
        db.rollback();
        QMessageBox::information(this,"connection info","update failed!");
    }
}
