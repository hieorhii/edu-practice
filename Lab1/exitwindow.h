#ifndef EXITWINDOW_H
#define EXITWINDOW_H

#include <QDialog>

namespace Ui {
class ExitWindow;
}

class ExitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ExitWindow(QWidget *parent = nullptr);
    ~ExitWindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ExitWindow *ui;
};

#endif // EXITWINDOW_H
