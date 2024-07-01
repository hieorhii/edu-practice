#ifndef FORMADD_H
#define FORMADD_H

#include <QWidget>

namespace Ui {
class FormAdd;
}

class FormAdd : public QWidget
{
    Q_OBJECT

public:
    explicit FormAdd(QWidget *parent = nullptr);
    ~FormAdd();

private:
    Ui::FormAdd *ui;
};

#endif // FORMADD_H
