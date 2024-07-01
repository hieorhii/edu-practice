#include "formdelete.h"
#include "ui_formdelete.h"

FormDelete::FormDelete(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDelete)
    , model(new QStringListModel(this))
{
    ui->setupUi(this);
    ui->listView->setModel(model);
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
    QModelIndex index = ui->listView->currentIndex();
    if (index.isValid()) {
        QString item = model->data(index, Qt::DisplayRole).toString();
        emit removeItemSignal(item);
    }
    close();
}

void FormDelete::setModelData(const QStringList &items)
{
    model->setStringList(items);
}
