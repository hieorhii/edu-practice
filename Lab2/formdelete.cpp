#include "formdelete.h"
#include "ui_formdelete.h"

FormDelete::FormDelete(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDelete)
{
    ui->setupUi(this);
}

FormDelete::~FormDelete()
{
    delete ui;
}

void FormDelete::on_buttonBox_rejected()
{
    close();
}


void FormDelete::on_buttonBox_accepted()
{
    close();
}

