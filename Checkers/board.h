// board.h
#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QVector>

class Board : public QWidget {
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void drawBoard(QPainter &painter);
    void drawPieces(QPainter &painter);
    QVector<QVector<int>> boardState;
    int currentPlayer;
    int selectedRow, selectedCol;
    bool pieceSelected;
    bool multiCapture;

    bool checkWinCondition();
    void resetGame();
    bool hasCaptureMoves(int player);
    void continueMultiCapture(int row, int col);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isCaptureMove(int fromRow, int fromCol, int toRow, int toCol);
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
};

#endif // BOARD_H
