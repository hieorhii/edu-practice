#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>

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
};

#endif // STARTMENU_H
