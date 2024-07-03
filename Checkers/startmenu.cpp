#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    connect(ui->playButton, &QPushButton::clicked, this, &StartMenu::returnToBoard);
}

StartMenu::~StartMenu()
{
    delete ui;
}
