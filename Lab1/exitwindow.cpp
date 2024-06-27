#include "exitwindow.h"
#include "ui_exitwindow.h"

ExitWindow::ExitWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExitWindow)
{
    ui->setupUi(this);
}

ExitWindow::~ExitWindow()
{
    delete ui;
}

void ExitWindow::on_buttonBox_accepted()
{
    QApplication::quit();
}

