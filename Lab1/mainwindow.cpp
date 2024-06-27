#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <regex>
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

void MainWindow::on_actionExit_triggered()
{
    dialogWindow.setModal(true);
    dialogWindow.exec();
}

void MainWindow::on_convertButton_clicked()
{

    QList<QString> degrees = {"Celsium", "Fahrengeit", "Kelvin", "Reaumur"};
    QString firstBox = ui->comboBox_3->currentText();
    QString secondBox = ui->comboBox_2->currentText();
    qint8 secondBoxIndex = ui->comboBox_2->currentIndex();
    qint8 firstInput = ui->res_1->text().toInt();
    std::string checkString = ui->res_1->text().toStdString();
    std::regex rgx("^([1-9])|([1-9])([0-9]){1,9}|-([1-9])|-([1-9])([0-9]){1,9}$");
    if(regex_match(checkString, rgx)){
    if (firstBox == degrees.at(0)){
        switch(secondBoxIndex) {
        case 0:
        {
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 1:
        {
            firstInput = firstInput * 9 / 5 + 32;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 2:
        {
            firstInput += 273;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 3:
        {
            firstInput = firstInput * 0.8;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        }
    }
    else if (firstBox == degrees.at(1)){
        switch(secondBoxIndex) {
        case 0:
        {
            firstInput = (firstInput - 32) * 5 / 9;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 1:
        {
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 2:
        {
            firstInput = (firstInput - 32) * 5 / 9;
            firstInput += 273;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 3:
        {
            firstInput = (firstInput - 32) * 5 / 9;
            firstInput = firstInput * 0.8;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        }
    }
    else if (firstBox == degrees.at(2)){
        switch(secondBoxIndex) {
        case 0:
        {
            firstInput -= 273;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 1:
        {
            firstInput -= 273;
            firstInput = firstInput * 9 / 5 + 32;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 2:
        {
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 3:
        {
            firstInput -= 273;
            firstInput = firstInput * 0.8;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        }
    }
    else if (firstBox == degrees.at(3)){
        switch(secondBoxIndex) {
        case 0:
        {
            firstInput /= 0.8;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 1:
        {
            firstInput /= 0.8;
            firstInput = firstInput * 9 / 5 + 32;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 2:
        {
            firstInput /= 0.8;
            firstInput += 273;
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        case 3:
        {
            QString str = QString::number(firstInput);
            ui->res_2->setText(str);
            break;
        }
        }
    }
    }
    else
    {
        ui->res_2->setText("Wrong number");
    }

}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked){ui->convertButton->setEnabled(true);}
    else{ui->convertButton->setEnabled(false);};
}


void MainWindow::on_pushButton_clicked()
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

    QByteArray text = file.readLine();

    ui->res_1->setText(text);
}

