#ifndef BOARD_H
#define BOARD_H

#include <QMainWindow>
#include <QVector>
#include <QStackedWidget>
#include "qboxlayout.h"
#include "startmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

enum PieceType {
    Empty = 0,
    BlackPiece = 1,
    WhitePiece = 2,
    BlackKing = 3,
    WhiteKing = 4
};

class Board : public QMainWindow {
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    ~Board();
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Board *ui;
    QVector<QVector<int>> boardState;
    int currentPlayer;
    int selectedRow;
    int selectedCol;
    bool pieceSelected;
    bool multiCapture;
    QStackedWidget *stackedWidget;
    StartMenu *startMenu;
    QVBoxLayout *layout;

    void drawBoard(QPainter &painter);
    void drawPieces(QPainter &painter);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isKingMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isCaptureMove(int fromRow, int fromCol, int toRow, int toCol);
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    void checkForKing(int row, int col);
    bool hasCaptureMoves(int player);
    bool isCaptureAvailable(int row, int col);
    bool checkWinCondition();
    void resetGame();

private slots:
    void returnToBoard();
};

#endif // BOARD_H
