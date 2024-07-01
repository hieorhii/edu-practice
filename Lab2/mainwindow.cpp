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
    connect(&formDelete, &FormDelete::removeItemSignal, this, &MainWindow::removeItem);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Up:
        on_pushButton_3_clicked();
        break;
    case Qt::Key_Left:
        on_pushButton_clicked();
        break;
    case Qt::Key_Right:
        on_pushButton_2_clicked();
        break;
    case Qt::Key_Down:
        on_pushButton_3_clicked();
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    formAdd.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    formDelete.setModelData(getItems());
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

QStringList MainWindow::getItems() const
{
    QStringList items;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        items << ui->listWidget->item(i)->text();
    }
    return items;
}

void MainWindow::removeItem(const QString &item)
{
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        if (ui->listWidget->item(i)->text() == item) {
            delete ui->listWidget->takeItem(i);
            break;
        }
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        if (ui->tableWidget->item(i, 0) && ui->tableWidget->item(i, 0)->text() == item) {
            ui->tableWidget->removeRow(i);
            break;
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->listWidget->sortItems();
}


void MainWindow::on_pushButton_5_clicked()
{
    QStringList items;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        items << ui->listWidget->item(i)->text();
    }

    int n = items.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (items[j] < items[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            qSwap(items[i], items[minIndex]);
        }
    }

    ui->listWidget->clear();
    for (const QString &item : items) {
        ui->listWidget->addItem(item);
    }
}

