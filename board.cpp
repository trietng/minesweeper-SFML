#include "board.h"

board::board() {
    width = 0;
    length = 0;
}
board::board(int x, int y, int z) {
    width = x;
    length = y;
    mem_cell.assign(x, std::vector<int>(y, 0));
    cell.assign(x, std::vector<int>(y, 0));
    int count = 0;
    setMine(z, count);
    for (int a = 0; a < x; ++a) {
        for (int b = 0; b < y; ++b) {
            cell[a][b] = 10;
            if (!checkMine(a, b)) {
                setCellNum(a, b);
            }
        }
    }
}
void board::setMine(int mines, int &count) {
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            if ((count < mines) && !checkMine(a, b)) {
                if ((rand() % 10 + 1) == 1) {
                    mem_cell[a][b] = 9;
                    count++;
                }
            }
        }
    }
    if (count < mines) {
        setMine(mines, count);
    }
}
bool board::checkMine(int x, int y) {
    if (mem_cell[x][y] == 9) {
        return true;
    }
    else {
        return false;
    }
}
bool board::isZero(int x, int y) {
    if (mem_cell[x][y] == 0) {
        return true;
    }
    else {
        return false;
    }
}
bool board::isRevealed(int x, int y) {
    if (cell[x][y] != 10) {
        return true;
    }
    else {
        return false;
    }
}
bool board::isPositive(int x, int y) {
    if ((mem_cell[x][y] >= 1) && (mem_cell[x][y] <= 8)) {
        return true;
    }
    else {
        return false;
    }
}
void board::setCellNum(int x, int y) {
    int n = 0;
    if (y < length - 1) {
        if (checkMine(x, y + 1)) {
            ++n;
        }
    }
    if (x < width - 1) {
        if (checkMine(x + 1, y)) {
            ++n;
        }
    }
    if (x > 0) {
        if (checkMine(x - 1, y)) {
            ++n;
        }
    }
    if (y > 0) {
        if (checkMine(x, y - 1)) {
            ++n;
        }
    }
    if ((x < width - 1) && (y < length - 1)) {
        if (checkMine(x + 1, y + 1)) {
            ++n;
        }
    }
    if ((x > 0) && (y < length - 1)) {
        if (checkMine(x - 1, y + 1)) {
            ++n;
        }
    }
    if ((y > 0) && (x < width - 1)) {
        if (checkMine(x + 1, y - 1)) {
            ++n;
        }
    }
    if ((y > 0) && (x > 0)) {
        if (checkMine(x - 1, y - 1)) {
            ++n;
        }
    }
    mem_cell[x][y] = n;
}
void board::revealCell(int x, int y) {
    if ((x >= 0) && (y >= 0) && (x <= width - 1) && (y <= length - 1)) {
        cell[x][y] = mem_cell[x][y];
    }
}
void board::revealSurroundingZero(int x, int y) {
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
void board::revealNearbyPositive(int x, int y) {
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
        if (!checkMine(x - 1, y + 1) && !isRevealed(x - 1, y + 1)) {
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
void board::revealCellZero(int x, int y) {
    revealSurroundingZero(x, y);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            if (isZero(a, b) && isRevealed(a, b)) {
                revealNearbyPositive(a, b);
            }
        }
    }
}
void board::flagCell(int x, int y) {
    if (!isRevealed(x, y)) {
        cell[x][y] = 11;
    }
}
bool board::isFlagged(int x, int y) {
    if (cell[x][y] == 11) {
        return true;
    }
    else {
        return false;
    }
}
void board::unflagCell(int x, int y) {
    if (isFlagged(x, y)) {
        cell[x][y] = 10;
    }
}
void board::DEBUG_revealAll() {
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < length; ++b) {
            cell[a][b] = mem_cell[a][b];
        }
    }
}
