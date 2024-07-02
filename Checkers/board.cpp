// board.cpp
#include "board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

Board::Board(QWidget *parent) : QWidget(parent), boardState(8, QVector<int>(8, 0)),
    currentPlayer(2), selectedRow(-1), selectedCol(-1), pieceSelected(false), multiCapture(false) {
    // Начальное расположение шашек на черных клетках
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {
                boardState[row][col] = 1; // Черные шашки
            }
        }
    }

    for (int row = 5; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {
                boardState[row][col] = 2; // Белые шашки
            }
        }
    }
}

QSize Board::sizeHint() const {
    return QSize(400, 400);
}

void Board::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    drawBoard(painter);
    drawPieces(painter);
}

void Board::drawBoard(QPainter &painter) {
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, width(), height());

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {
                painter.setBrush(Qt::gray);
                painter.drawRect(col * width() / 8, row * height() / 8, width() / 8, height() / 8);
            }
        }
    }
}

void Board::drawPieces(QPainter &painter) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (boardState[row][col] == 1) {
                painter.setBrush(Qt::black);
                painter.drawEllipse(col * width() / 8, row * height() / 8, width() / 8, height() / 8);
            } else if (boardState[row][col] == 2) {
                painter.setBrush(Qt::white);
                painter.drawEllipse(col * width() / 8, row * height() / 8, width() / 8, height() / 8);
            }
            // Визуализация выделенной шашки
            if (pieceSelected && row == selectedRow && col == selectedCol) {
                painter.setBrush(Qt::red);
                painter.drawEllipse(col * width() / 8 + width() / 32, row * height() / 8 + height() / 32, width() / 16, height() / 16);
            }
        }
    }
}

void Board::mousePressEvent(QMouseEvent *event) {
    int row = event->y() / (height() / 8);
    int col = event->x() / (width() / 8);

    if (!pieceSelected) {
        if (boardState[row][col] == currentPlayer) {
            selectedRow = row;
            selectedCol = col;
            pieceSelected = true;
        }
    } else {
        if (isValidMove(selectedRow, selectedCol, row, col)) {
            movePiece(selectedRow, selectedCol, row, col);
            if (multiCapture) {
                selectedRow = row;
                selectedCol = col;
                pieceSelected = true;
                if (!hasCaptureMoves(currentPlayer)) {
                    multiCapture = false;
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                }
            } else {
                pieceSelected = false;
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        } else {
            pieceSelected = false;
        }
    }
}



bool Board::isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = toRow - fromRow;
    int colDiff = abs(toCol - fromCol);

    // Только диагональные ходы
    if (colDiff != rowDiff && colDiff != -rowDiff) return false;

    // Проверка наличия обязательных ходов с захватом
    if (hasCaptureMoves(currentPlayer)) {
        return isCaptureMove(fromRow, fromCol, toRow, toCol);
    }

    // Обычный ход на одну клетку
    if (colDiff == 1 && rowDiff == ((currentPlayer == 1) ? 1 : -1) && boardState[toRow][toCol] == 0) {
        return true;
    }

    // Ход с захватом
    if (colDiff == 2 && abs(rowDiff) == 2) {
        return isCaptureMove(fromRow, fromCol, toRow, toCol);
    }

    return false;
}



bool Board::isCaptureMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowMid = (fromRow + toRow) / 2;
    int colMid = (fromCol + toCol) / 2;

    if (boardState[toRow][toCol] != 0) return false; // Целевая клетка должна быть пустой

    int opponent = (currentPlayer == 1) ? 2 : 1;
    if (boardState[rowMid][colMid] == opponent) return true; // На средней клетке должна быть шашка противника

    return false;
}


void Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    if (isValidMove(fromRow, fromCol, toRow, toCol)) {
        if (abs(toRow - fromRow) == 2) {
            // Если это ход с захватом, удаляем захваченную шашку
            int rowMid = (fromRow + toRow) / 2;
            int colMid = (fromCol + toCol) / 2;
            boardState[rowMid][colMid] = 0;
        }
        boardState[toRow][toCol] = boardState[fromRow][fromCol];
        boardState[fromRow][fromCol] = 0;
        update();

        // Проверка возможности множественного захвата
        if (abs(toRow - fromRow) == 2 && hasCaptureMoves(currentPlayer)) {
            multiCapture = true;
        } else {
            multiCapture = false;
            // Проверка условия победы
            if (checkWinCondition()) {
                QString winner = (currentPlayer == 1) ? "Black" : "White";
                QMessageBox::information(this, "Game Over", winner + " wins!");
                resetGame();
            }
        }
    }
}


void Board::resetGame() {
    boardState = QVector<QVector<int>>(8, QVector<int>(8, 0));
    currentPlayer = 2;
    selectedRow = -1;
    selectedCol = -1;
    pieceSelected = false;
    multiCapture = false;

    // Начальное расположение шашек на черных клетках
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {
                boardState[row][col] = 1; // Черные шашки
            }
        }
    }

    for (int row = 5; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 == 1) {
                boardState[row][col] = 2; // Белые шашки
            }
        }
    }
    update();
}


bool Board::checkWinCondition() {
    int opponent = (currentPlayer == 1) ? 2 : 1;
    bool opponentHasPieces = false;
    bool opponentHasMoves = false;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (boardState[row][col] == opponent) {
                opponentHasPieces = true;

                // Проверяем, есть ли возможные ходы для шашки противника
                for (int dRow = -1; dRow <= 1; dRow += 2) {
                    for (int dCol = -1; dCol <= 1; dCol += 2) {
                        int newRow = row + dRow;
                        int newCol = col + dCol;

                        // Проверяем ход на одну клетку
                        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && boardState[newRow][newCol] == 0) {
                            if (isValidMove(row, col, newRow, newCol)) {
                                opponentHasMoves = true;
                            }
                        }

                        // Проверяем ход с захватом
                        newRow = row + 2 * dRow;
                        newCol = col + 2 * dCol;
                        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && boardState[newRow][newCol] == 0) {
                            if (isCaptureMove(row, col, newRow, newCol)) {
                                opponentHasMoves = true;
                            }
                        }
                    }
                }
            }
        }
    }

    return !opponentHasPieces || !opponentHasMoves;
}

bool Board::hasCaptureMoves(int player) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (boardState[row][col] == player) {
                for (int dRow = -2; dRow <= 2; dRow += 4) {
                    for (int dCol = -2; dCol <= 2; dCol += 4) {
                        int newRow = row + dRow;
                        int newCol = col + dCol;
                        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
                            if (isCaptureMove(row, col, newRow, newCol)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
