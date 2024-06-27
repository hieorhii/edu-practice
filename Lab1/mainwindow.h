#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <exitwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_convertButton_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    ExitWindow dialogWindow;
};
#endif // MAINWINDOW_H
