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
