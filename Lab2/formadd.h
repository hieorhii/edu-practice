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

signals:
    void signalFormAdd(QString);
    void signalFormAdd1(QString, QString, QString);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // FORMADD_H
