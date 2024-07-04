#include "board.h"
#include "ui_board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>



Board::Board(QWidget *parent)
    : QMainWindow(parent) 
    , ui(new Ui::Board) 
    , boardState(8, QVector<int>(8, Empty)) 
    , currentPlayer(WhitePiece) 
    , selectedRow(-1) 
    , selectedCol(-1) 
    , pieceSelected(false) 
    , multiCapture(false)
{
    ui->setupUi(this);

    setFixedSize(600,600);
    
    for (int row = 0; row < 3; ++row) { 
        for (int col = 0; col < 8; ++col) { 
            if ((row + col) % 2 == 1) { 
                boardState[row][col] = BlackPiece; 
            }
        }
    }

    for (int row = 5; row < 8; ++row) { 
        for (int col = 0; col < 8; ++col) { 
            if ((row + col) % 2 == 1) { 
                boardState[row][col] = WhitePiece; 
            }
        }
    }

    stackedWidget = new QStackedWidget(this); 
    startMenu = new StartMenu(this); 
    QWidget *mainWidget = new QWidget(this); 
    layout = new QVBoxLayout(mainWidget); 
    layout->setContentsMargins(0, 0, 0, 0); 
    layout->setSpacing(0); 
    mainWidget->setLayout(layout); 

    stackedWidget->addWidget(startMenu); 
    stackedWidget->addWidget(ui->centralwidget); 

    layout->addWidget(stackedWidget); 
    setCentralWidget(mainWidget); 

    stackedWidget->setCurrentWidget(startMenu); 

    connect(startMenu, &StartMenu::returnToBoard, this, &Board::returnToBoard); 
}


void Board::returnToBoard() {
    stackedWidget->setCurrentWidget(ui->centralwidget); 
}


Board::~Board() {
    delete ui; 
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
            if (boardState[row][col] == BlackPiece || boardState[row][col] == BlackKing) { 
                painter.setBrush(Qt::black); 
                painter.drawEllipse(col * width() / 8, row * height() / 8, width() / 8, height() / 8); 
                if (boardState[row][col] == BlackKing) { 
                    painter.setBrush(Qt::yellow); 
                    painter.drawEllipse(col * width() / 8 + width() / 32, row * height() / 8 + height() / 32, width() / 16, height() / 16); 
                }
            } else if (boardState[row][col] == WhitePiece || boardState[row][col] == WhiteKing) { 
                painter.setBrush(Qt::white); 
                painter.drawEllipse(col * width() / 8, row * height() / 8, width() / 8, height() / 8); 
                if (boardState[row][col] == WhiteKing) { 
                    painter.setBrush(Qt::yellow); 
                    painter.drawEllipse(col * width() / 8 + width() / 32, row * height() / 8 + height() / 32, width() / 16, height() / 16); 
                }
            }
            if (pieceSelected && row == selectedRow && col == selectedCol) { 
                painter.setBrush(Qt::red); 
                painter.drawEllipse(col * width() / 8 + width() / 32, row * height() / 8 + height() / 32, width() / 16, height() / 16); 
            }
        }
    }
}


void Board::mousePressEvent(QMouseEvent *event) {
    int row = event->position().y() / (height() / 8); 
    int col = event->position().x() / (width() / 8); 

    if (event->button() == Qt::RightButton) { 
        undoMove(); 
        return;
    }

    if (!pieceSelected) { 
        if (boardState[row][col] == currentPlayer || boardState[row][col] == currentPlayer + 2) { 
            selectedRow = row; 
            selectedCol = col; 
            pieceSelected = true; 
            update(); 
        }
    } else { 
        if (isValidMove(selectedRow, selectedCol, row, col)) { 
            boardHistory.push(boardState); 
            movePiece(selectedRow, selectedCol, row, col); 
            if (multiCapture) { 
                selectedRow = row; 
                selectedCol = col; 
                pieceSelected = true; 
                if (!hasCaptureMoves(currentPlayer)) { 
                    multiCapture = false; 
                    currentPlayer = (currentPlayer == BlackPiece) ? WhitePiece : BlackPiece; 
                }
            } else { 
                pieceSelected = false; 
                currentPlayer = (currentPlayer == BlackPiece) ? WhitePiece : BlackPiece; 
            }
            update(); 
        } else { 
            pieceSelected = false; 
            update(); 
        }
    }
}


bool Board::isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = toRow - fromRow; 
    int colDiff = abs(toCol - fromCol); 

    if (boardState[fromRow][fromCol] == BlackKing || boardState[fromRow][fromCol] == WhiteKing) { 
        return isKingMove(fromRow, fromCol, toRow, toCol); 
    }

    if (colDiff != rowDiff && colDiff != -rowDiff) return false; 

    if (hasCaptureMoves(currentPlayer)) { 
        return isCaptureMove(fromRow, fromCol, toRow, toCol); 
    }

    if (colDiff == 1 && rowDiff == ((currentPlayer == BlackPiece) ? 1 : -1) && boardState[toRow][toCol] == Empty) { 
        return true; 
    }

    if (colDiff == 2 && abs(rowDiff) == 2) { 
        return isCaptureMove(fromRow, fromCol, toRow, toCol); 
    }

    return false; 
}


bool Board::isKingMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = abs(toRow - fromRow); 
    int colDiff = abs(toCol - fromCol); 

    if (rowDiff != colDiff) return false; 

    int rowStep = (toRow > fromRow) ? 1 : -1; 
    int colStep = (toCol > fromCol) ? 1 : -1; 
    int row = fromRow + rowStep; 
    int col = fromCol + colStep; 
    bool opponentPieceFound = false; 

    while (row != toRow && col != toCol) { 
        if (boardState[row][col] != Empty) { 
            if ((boardState[row][col] == currentPlayer) || (boardState[row][col] == currentPlayer + 2)) { 
                return false; 
            }
            if (opponentPieceFound) { 
                return false; 
            }
            opponentPieceFound = true; 
        }
        row += rowStep; 
        col += colStep; 
    }

    return opponentPieceFound; 
}


void Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    if (isValidMove(fromRow, fromCol, toRow, toCol)) { 
        if (boardState[fromRow][fromCol] == BlackKing || boardState[fromRow][fromCol] == WhiteKing) { 
            
            int rowStep = (toRow > fromRow) ? 1 : -1; 
            int colStep = (toCol > fromCol) ? 1 : -1; 
            int row = fromRow + rowStep; 
            int col = fromCol + colStep; 

            while (row != toRow && col != toCol) { 
                if (boardState[row][col] != Empty &&
                    boardState[row][col] != currentPlayer &&
                    boardState[row][col] != currentPlayer + 2) { 
                    boardState[row][col] = Empty; 
                }
                row += rowStep; 
                col += colStep; 
            }
        } else { 
            
            if (abs(toRow - fromRow) == 2) { 
                int rowMid = (fromRow + toRow) / 2; 
                int colMid = (fromCol + toCol) / 2; 
                boardState[rowMid][colMid] = Empty; 
            }
        }

        boardState[toRow][toCol] = boardState[fromRow][fromCol]; 
        boardState[fromRow][fromCol] = Empty; 
        checkForKing(toRow, toCol); 
        update(); 

        if ((abs(toRow - fromRow) == 2 || isKingMove(fromRow, fromCol, toRow, toCol)) && hasCaptureMoves(currentPlayer)) { 
            multiCapture = true; 
        } else {
            multiCapture = false; 
            if (checkWinCondition()) { 
                QString winner = (currentPlayer == BlackPiece || currentPlayer == BlackKing) ? "Black" : "White"; 
                QMessageBox::information(this, "Game Over", winner + " wins!"); 
                resetGame(); 
            }
        }
    }
}


void Board::checkForKing(int row, int col) {
    if (boardState[row][col] == BlackPiece && row == 7) { 
        boardState[row][col] = BlackKing; 
    } else if (boardState[row][col] == WhitePiece && row == 0) { 
        boardState[row][col] = WhiteKing; 
    }
}


bool Board::hasCaptureMoves(int player) {
    for (int row = 0; row < 8; ++row) { 
        for (int col = 0; col < 8; ++col) { 
            if (boardState[row][col] == player || boardState[row][col] == player + 2) { 
                if (isCaptureAvailable(row, col)) { 
                    return true; 
                }
            }
        }
    }
    return false; 
}


bool Board::isCaptureMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowMid = (fromRow + toRow) / 2; 
    int colMid = (fromCol + toCol) / 2; 

    if (boardState[fromRow][fromCol] == BlackKing || boardState[fromRow][fromCol] == WhiteKing) { 
        return isKingMove(fromRow, fromCol, toRow, toCol); 
    }

    if (boardState[toRow][toCol] == Empty &&
        boardState[rowMid][colMid] != Empty &&
        boardState[rowMid][colMid] != boardState[fromRow][fromCol] &&
        boardState[rowMid][colMid] != boardState[fromRow][fromCol] + 2) { 
        return true; 
    }

    return false; 
}


bool Board::isCaptureAvailable(int row, int col) {
    if (boardState[row][col] == BlackKing || boardState[row][col] == WhiteKing) { 
        
        for (int dRow = -1; dRow <= 1; dRow += 2) { 
            for (int dCol = -1; dCol <= 1; dCol += 2) { 
                int newRow = row + dRow * 2; 
                int newCol = col + dCol * 2; 
                while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) { 
                    if (isCaptureMove(row, col, newRow, newCol)) { 
                        return true; 
                    }
                    newRow += dRow; 
                    newCol += dCol; 
                }
            }
        }
    } else { 
        
        for (int dRow = -1; dRow <= 1; dRow += 2) { 
            for (int dCol = -1; dCol <= 1; dCol += 2) { 
                int newRow = row + dRow * 2; 
                int newCol = col + dCol * 2; 
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && isCaptureMove(row, col, newRow, newCol)) { 
                    return true; 
                }
            }
        }
    }
    return false; 
}


bool Board::checkWinCondition() {
    int blackCount = 0; 
    int whiteCount = 0; 

    for (int row = 0; row < 8; ++row) { 
        for (int col = 0; col < 8; ++col) { 
            if (boardState[row][col] == BlackPiece || boardState[row][col] == BlackKing) { 
                blackCount++; 
            } else if (boardState[row][col] == WhitePiece || boardState[row][col] == WhiteKing) { 
                whiteCount++; 
            }
        }
    }

    return blackCount == 0 || whiteCount == 0; 
}


void Board::resetGame() {
    boardState.fill(QVector<int>(8, Empty)); 
    currentPlayer = WhitePiece; 
    selectedRow = -1; 
    selectedCol = -1; 
    pieceSelected = false; 
    multiCapture = false; 

    
    for (int row = 0; row < 3; ++row) { 
        for (int col = 0; col < 8; ++col) { 
            if ((row + col) % 2 == 1) { 
                boardState[row][col] = BlackPiece; 
            }
        }
    }

    for (int row = 5; row < 8; ++row) { 
        for (int col = 0; col < 8; ++col) { 
            if ((row + col) % 2 == 1) { 
                boardState[row][col] = WhitePiece; 
            }
        }
    }

    update(); 
}

void Board::undoMove() {
    if (!boardHistory.isEmpty()) { 
        boardState = boardHistory.pop(); 
        pieceSelected = false; 
        multiCapture = false; 
        currentPlayer = (currentPlayer == BlackPiece) ? WhitePiece : BlackPiece; 
        update(); 
    }
}
