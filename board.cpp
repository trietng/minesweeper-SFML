#include "board.h"

board::board() {
    width = 0;
    length = 0;
    size = 0;
    countRevealedCells = 0;
    mines = 0;
    isFailure = false;
    isVictory = false;
    isFirstLeftClick = false;
    isGameRunning = false;
}
board::board(const int& x, const int& y, const int& z) {
    isGameRunning = true;
    width = x;
    length = y;
    size = x * y;
    mines = z;
    countRevealedCells = 0;
    mem_cell.assign(x, std::vector<int>(y, 0));
    cell.assign(x, std::vector<int>(y, 0));
    isFailure = false;
    isVictory = false;
    isFirstLeftClick = true;
    int count = 0;
    setMine(z, count);
    for (int a = 0; a < x; ++a) {
        for (int b = 0; b < y; ++b) {
            cell[a][b] = 10;
            if (!isMine(a, b)) {
                countSurroundingMines(a, b);
            }
        }
    }
}
void board::setMine(const int& mines, int &count) {
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            if ((count < mines) && !isMine(a, b)) {
                if ((rand() % 10 + 1) == 1) {
                    mem_cell[a][b] = 9;
                    count++;
                }
            }
            if (mines == count) {
                break;
            }
        }
    }
    if (count < mines) {
        setMine(mines, count);
    }
}
void board::resetCellNum() {
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            if (!isMine(a, b)) {
                countSurroundingMines(a, b);
            }
        }
    }
}
bool board::isMine(const int& x, const int& y) {
    if (mem_cell[x][y] == 9) {
        return true;
    }
    else {
        return false;
    }
}
bool board::isZero(const int& x, const int& y) {
    if (mem_cell[x][y] == 0) {
        return true;
    }
    else {
        return false;
    }
}
bool board::isRevealed(const int& x, const int& y) {
    if (cell[x][y] == 10) {
        return false;
    }
    else {
        return true;
    }
}
bool board::isPositive(const int& x, const int& y) {
    if ((mem_cell[x][y] >= 1) && (mem_cell[x][y] <= 8)) {
        return true;
    }
    else {
        return false;
    }
}
void board::countSurroundingMines(const int& x, const int& y) {
    int n = 0;
    if (y < length - 1) {
        if (isMine(x, y + 1)) {
            ++n;
        }
    }
    if (x < width - 1) {
        if (isMine(x + 1, y)) {
            ++n;
        }
    }
    if (x > 0) {
        if (isMine(x - 1, y)) {
            ++n;
        }
    }
    if (y > 0) {
        if (isMine(x, y - 1)) {
            ++n;
        }
    }
    if ((x < width - 1) && (y < length - 1)) {
        if (isMine(x + 1, y + 1)) {
            ++n;
        }
    }
    if ((x > 0) && (y < length - 1)) {
        if (isMine(x - 1, y + 1)) {
            ++n;
        }
    }
    if ((y > 0) && (x < width - 1)) {
        if (isMine(x + 1, y - 1)) {
            ++n;
        }
    }
    if ((y > 0) && (x > 0)) {
        if (isMine(x - 1, y - 1)) {
            ++n;
        }
    }
    mem_cell[x][y] = n;
}
void board::revealCell(const int& x, const int& y) {
    if ((x >= 0) && (y >= 0) && (x <= width - 1) && (y <= length - 1) && !isRevealed(x, y)) {
        cell[x][y] = mem_cell[x][y];
        countRevealedCells++;
    }
}
void board::revealSurroundingZero(const int& x, const int& y) {
    if (y < length - 1) {
        if (isZero(x, y + 1) && !isRevealed(x, y + 1)) {
            revealCell(x, y + 1);
            revealSurroundingZero(x, y + 1);
        }
    }
    if (x < width - 1) {
        if (isZero(x + 1, y) && !isRevealed(x + 1, y)) {
            revealCell(x + 1, y);
            revealSurroundingZero(x + 1, y);
        }
    }
    if (x > 0) {
        if (isZero(x - 1, y) && !isRevealed(x - 1, y)) {
            revealCell(x - 1, y);
            revealSurroundingZero(x - 1, y);
        }
    }
    if (y > 0) {
        if (isZero(x, y - 1) && !isRevealed(x, y - 1)) {
            revealCell(x, y - 1);
            revealSurroundingZero(x, y - 1);
        }
    }
    if ((x < width - 1) && (y < length - 1)) {
        if (isZero(x + 1, y + 1) && !isRevealed(x + 1, y + 1)) {
            revealCell(x + 1, y + 1);
            revealSurroundingZero(x + 1, y + 1);
        }
    }
    if ((x > 0) && (y < length - 1)) {
        if (isZero(x - 1, y + 1) && !isRevealed(x - 1, y + 1)) {
            revealCell(x - 1, y + 1);
            revealSurroundingZero(x - 1, y + 1);
        }
    }
    if ((y > 0) && (x < width - 1)) {
        if (isZero(x + 1, y - 1) && !isRevealed(x + 1, y - 1)) {
            revealCell(x + 1, y - 1);
            revealSurroundingZero(x + 1, y - 1);
        }
    }
    if ((y > 0) && (x > 0)) {
        if (isZero(x - 1, y - 1) && !isRevealed(x - 1, y - 1)) {
            revealCell(x - 1, y - 1);
            revealSurroundingZero(x - 1, y - 1);
        }
    }
}
void board::revealNearbyPositive(const int& x, const int& y) {
    if (y < length - 1) {
        if (isPositive(x, y + 1) && !isRevealed(x, y + 1)) {
            revealCell(x, y + 1);
        }
    }
    if (x < width - 1) {
        if (isPositive(x + 1, y) && !isRevealed(x + 1, y)) {
            revealCell(x + 1, y);
        }
    }
    if (x > 0) {
        if (isPositive(x - 1, y) && !isRevealed(x - 1, y)) {
            revealCell(x - 1, y);
        }
    }
    if (y > 0) {
        if (isPositive(x, y - 1) && !isRevealed(x, y - 1)) {
            revealCell(x, y - 1);
        }
    }
    if ((x < width - 1) && (y < length - 1)) {
        if (isPositive(x + 1, y + 1) && !isRevealed(x + 1, y + 1)) {
            revealCell(x + 1, y + 1);
        }
    }
    if ((x > 0) && (y < length - 1)) {
        if (!isMine(x - 1, y + 1) && !isRevealed(x - 1, y + 1)) {
            revealCell(x - 1, y + 1);
        }
    }
    if ((y > 0) && (x < width - 1)) {
        if (isPositive(x + 1, y - 1) && !isRevealed(x + 1, y - 1)) {
            revealCell(x + 1, y - 1);
        }
    }
    if ((y > 0) && (x > 0)) {
        if (isPositive(x - 1, y - 1) && !isRevealed(x - 1, y - 1)) {
            revealCell(x - 1, y - 1);
        }
    }
}
void board::revealCellZero(const int& x, const int& y) {
    revealSurroundingZero(x, y);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            if (isZero(a, b) && isRevealed(a, b)) {
                revealNearbyPositive(a, b);
            }
        }
    }
}
void board::flagCell(const int& x, const int& y) {
    if (!isRevealed(x, y)) {
        cell[x][y] = 11;
    }
}
bool board::isFlagged(const int& x, const int& y) {
    if (cell[x][y] == 11) {
        return true;
    }
    else {
        return false;
    }
}
void board::unflagCell(const int& x, const int& y) {
    if (isFlagged(x, y)) {
        cell[x][y] = 10;
    }
}
void board::swapMine(const int& x, const int& y) {
    int mx = rand() % width, my = rand() % length;
    if (isFirstLeftClick) {
        if (isMine(x, y)) {
            mem_cell[x][y] = 0;
            while ((mx == x) || (my == y) || isMine(mx, my)) {
                mx = rand() % width;
                my = rand() % length;
            }
            mem_cell[mx][my] = 9;
            resetCellNum();
        }
        isFirstLeftClick = false;
    }
}
bool board::endGame() {
    if ((isFailure) || (isVictory)) {
        return true;
    }
    return false;
}
void board::DEBUG_revealAll() {
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            cell[a][b] = mem_cell[a][b];
        }
    }
}

custom_value::custom_value() {
    customLength = 10;
    customWidth = 10;
    customMines = 10;
}

void custom_value::edit_custom_value(const int& value_type, const bool& isIncrease) {
    // reset customMines if customMines > customWidth * customLength
    if (customMines > customWidth * customLength) {
        customMines = customWidth * customLength;
    }
    if (isIncrease == false) {
        switch (value_type) {
            case 1:
                if (customWidth > 3) {
                    --customWidth;
                }
                break;
            case 2:
                if (customLength > 3) {
                    --customLength;
                }
                break;
            case 3:
                if (customMines > 1) {
                    --customMines;
                }
                break;
            default:
                break;
        }
    }
    else {
        switch (value_type) {
            case 1:
                if (customWidth < 32) {
                    ++customWidth;
                }
                break;
            case 2:
                if (customLength < 16) {
                    ++customLength;
                }
                break;
            case 3:
                if (customMines < customWidth * customLength) {
                    ++customMines;
                }
                break;
            default:
                break;
        }
    }
}