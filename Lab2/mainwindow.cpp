#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&formAdd, &FormAdd::signalFormAdd, this, &MainWindow::slotFormAdd);
    connect(&formAdd, &FormAdd::signalFormAdd1, this, &MainWindow::slotFormAdd1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Up){
        on_pushButton_3_clicked();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QFile file("in.txt");

    if(!file.exists())
    {
        ui->label->setText("File doesn't exists");
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->label->setText("Can't open the file");
    }

    int rowcount = file.readLine().toInt();


    ui->tableWidget->setRowCount(rowcount);
}


void MainWindow::on_pushButton_clicked()
{
    formAdd.show();
}


void MainWindow::on_pushButton_2_clicked()
{
    formDelete.show();
}

void MainWindow::slotFormAdd(QString a)
{
    QListWidgetItem *listItem = new QListWidgetItem(a);
    ui->listWidget->addItem(listItem);
}

int s = 0;
void MainWindow::slotFormAdd1(QString a, QString b, QString c)
{
    int *i = &s;
    QTableWidgetItem *tableItem1 = new QTableWidgetItem(a);
    ui->tableWidget->setItem(*i,0,tableItem1);
    QTableWidgetItem *tableItem2 = new QTableWidgetItem(b);
    ui->tableWidget->setItem(*i,1,tableItem2);
    QTableWidgetItem *tableItem3 = new QTableWidgetItem(c);
    ui->tableWidget->setItem(*i,2,tableItem3);
    ++(*i);
}

