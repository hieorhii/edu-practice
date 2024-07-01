#ifndef FORMDELETE_H
#define FORMDELETE_H

#include <QWidget>

namespace Ui {
class FormDelete;
}

class FormDelete : public QWidget
{
    Q_OBJECT

public:
    explicit FormDelete(QWidget *parent = nullptr);
    ~FormDelete();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::FormDelete *ui;
};

#endif // FORMDELETE_H
