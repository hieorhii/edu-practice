#include "formadd.h"
#include "ui_formadd.h"

FormAdd::FormAdd(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormAdd)
{
    ui->setupUi(this);
}

FormAdd::~FormAdd()
{
    delete ui;
}

void FormAdd::on_buttonBox_accepted()
{
    emit signalFormAdd(ui->lineEdit->text());
    emit signalFormAdd1(ui->lineEdit->text(), ui->lineEdit_2->text(),ui->lineEdit_3->text());
    close();
}


void FormAdd::on_buttonBox_rejected()
{
    close();
}

