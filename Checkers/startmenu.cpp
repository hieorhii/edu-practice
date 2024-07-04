#include "startmenu.h"
#include "ui_startmenu.h"
#include <QPixmap>

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
    connect(ui->playButton, &QPushButton::clicked, this, &StartMenu::returnToBoard);
    QPixmap pix("://background.jpg");
    int w = ui->label->width();
    int h = ui->label->height();

    ui->label->setPixmap(pix.scaled(w, h));
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_1:
        on_playButton_clicked();
        break;
    }
}

void StartMenu::on_playButton_clicked()
{
    emit returnToBoard();
}
