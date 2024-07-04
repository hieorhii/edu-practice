#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class StartMenu;
}

class StartMenu : public QMainWindow
{
    Q_OBJECT

signals:
    void returnToBoard();
public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu();

private:
    Ui::StartMenu *ui;

protected:
    void keyPressEvent(QKeyEvent *e) override;
private slots:
    void on_playButton_clicked();
};

#endif
