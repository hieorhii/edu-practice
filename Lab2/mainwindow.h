#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QStringList>
#include <QTableWidgetItem>
#include "formadd.h"
#include "formdelete.h"

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

    QStringList getItems() const;

protected:
    void keyPressEvent(QKeyEvent *e) override;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void removeItem(const QString &item);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    FormAdd formAdd;
    FormDelete formDelete;

public slots:
    void slotFormAdd(QString a);
    void slotFormAdd1(QString a, QString b, QString c);

signals:
    void signalDel();
};

#endif // MAINWINDOW_H
