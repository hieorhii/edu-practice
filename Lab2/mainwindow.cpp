#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    form_add.show();
}


void MainWindow::on_pushButton_2_clicked()
{
    form_delete.show();
}

